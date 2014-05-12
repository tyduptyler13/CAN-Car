chrome.app.runtime.onLaunched.addListener(function() {
	chrome.app.window.create("AllTest.html",
			{  
		frame: "none",
		id: "CANAppWindow",
		state: "fullscreen",
		alwaysOnTop: true
			}
	);
});

/*var io = require('socket.io')();
io.on('connection', function(socket){});
io.listen(8001);

var dataArray = ioserver.of('/dataArray');

dataArray.on('connection', function (socket) {
    console.log('dataArray connection');   
    socket.emit('callback', 'ok') 
    socket.on('message', function (msg) {
      console.log(status);
      chat.send(msg);
    });
}); */
