
socket = io.connect('http://localhost:8001');

socket.on('data', function(data){

	console.log("Got data", data);
	
	if (data.HVamp < 0.001){
		HighVoltageCurrentData.push(0);
	}
	else HighVoltageCurrentData.push(data.HVamp.toFixed(2));
	
	if (data.HVvolt < 0.001) {
		HighVoltageData.push(0);
	}
	else HighVoltageData.push(data.HVvolt.toFixed(2));
	
	if(data.Tank1Pressure<0.001){
		H2Pressure1.push(0);
	}
	else H2Pressure2.push(data.Tank2Pressure.toFixed(2));
	
	if(data.Tank2Pressure<0.001){
		H2Pressure2.push(0);
	}
	else H2Pressure3.push(data.Tank3Pressure.toFixed(2));
	
	if(data.Tank3Pressure<0.001){
		H2Pressure3.push(0);
	}
	else H2Pressure3.push(data.Tank3Pressure.toFixed(2));
	
	if(data.Twelvev<0.001){
		BatteryVoltage.push(0);
	}
	else BatteryVoltageData.push(data.Twelvev.toFixed(2));
	
	if(data.highBatTemp<0.001){
		BatteryTempData.push(0);
	}
	else BatteryTempData.push(data.highBatTemp.toFixed(2));
	
	if(data.Tank1Temp<0.001){
		H2Temp1.push(0);
	}
	else H2Temp1.push(data.Tank1Temp.toFixed(2));
	
	if(data.Tank2Temp<0.001){
		H2Temp2.push(0);
	}
	else H2Temp2.push(data.Tank2Temp.toFixed(2));
	
	if(data.Tank3Temp<0.001){
		H2Temp3.push(0);
	}
	else H2Temp3.push(data.Tank3Temp.toFixed(2));
	
	if(batteryPercentage < 1 ){
		batteryPercentage = 0;
	}
	else batteryPercentage = data.HVpercent.toFixed(0);
	
	// Do something with the data.
	//ex: ui.setBatTemp(data.highBatTemp)
});

