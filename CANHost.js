/**
 * NODE STUFF
 * All your server stuff goes here.
 * Client is anything inside chrome app folder.
 */

var addons = require('bindings')('CNI');
var io = require('socket.io').listen(8001);

var cni = new addons.CNI(0);

io.sockets.on('connection', function(socket){
	console.log("Connection from app! Woo.");
	
	//Send stuff every 2 seconds.
	setTimeout(function(){
		//How to send messages
		var obj = {
				highBatTemp : cni.getHighBatTemp(),
				lowBatTemp : cni.getLowBatTemp(),
				HVvolt : cni.getHVvolt(),
				HVamp : cni.getHVamp(),
				HVpercent : cni.getHVpercent(),
				Twelvev : cni.getTwelvev(),
				Tank1Temp : cni.getTank1Temp(),
				Tank2Temp : cni.getTank2Temp(),
				Tank3Temp : cni.getTank3Temp(),
				Tank1Pressure : cni.getTank1Pressure(),
				Tank2Pressure : cni.getTank2Pressure(),
				Tank3Pressure : cni.getTank3Pressure(),

		};
		
		
		socket.emit('data', obj);
	}, 2000);
	
	//How to recieve messages
	/*socket.on('getData', function(from, msg){
	});*/
	
	socket.on('disconnect', function(){
		console.log("App disconnected.");
	});
	
});

