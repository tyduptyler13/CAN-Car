
socket = io.connect('http://localhost:8001');

socket.on('data', function(data){

	console.log("Got data", data);
	
	HighVoltageCurrentData.push(data.HVamp);
	HighVoltageData.push(data.HVvolt);
	H2Pressure1.push(data.Tank1Pressure);
	H2Pressure2.push(data.Tank2Pressure);
	H2Pressure3.push(data.Tank3Pressure);
	BatteryVoltageData.push(data.Twelvev);
	BatteryTempData.push(data.highBatTemp)
	H2Temp1.push(data.Tank1Temp);
	H2Temp2.push(data.Tank2Temp);
	H2Temp3.push(data.Tank3Temp);
	batteryPercentage = data.HVpercent;
	// Do something with the data.
	//ex: ui.setBatTemp(data.highBatTemp)
});


