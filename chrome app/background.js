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
