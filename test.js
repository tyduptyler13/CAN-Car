var io = require('socket.io').listen(8001);

io.sockets.on('connection', function(socket){
	var obj = {
			highBatTemp : Math.random(),
			lowBatTemp : Math.random(),
			HVvolt : Math.random(),
			HVamp : Math.random(),
			HVpercent : Math.random(),
			Twelvev : Math.random(),
			Tank1Temp : Math.random(),
			Tank2Temp : Math.random(),
			Tank3Temp : Math.random(),
			Tank1Pressure : Math.random(),
			Tank2Pressure : Math.random(),
			Tank3Pressure : Math.random(),

	};
	socket.emit('data', obj);
	
	socket.on('data', function(data){
		
		console.log("Recieved", data);
	});
});

exports = io;
