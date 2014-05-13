
var AC_On = false;
var Pannel_On = false;
var Floor_On = false;
var PannelFloor_On = false;
var Defrost_On = false;
var FanLevel = 0;
var HVACArray = [0, 0, 0, 0, 0, 0];
//var  http;
//var server;
//var io;
//var socket;

$(function(){


	$("#AC_Button").click(function (e) {
		if (AC_On == false) {
			AC_On = true;
			HVACArray[0] = 1;
		}
		else {
			AC_On = false;
			HVACArray[0] = 0;
		}
	});
	$("#Pannel_Button").click(function (e) {
		if (Pannel_On == false) {
			Pannel_On = true;
			HVACArray[1] = 1;
		}
		else {
			Pannel_On = false;
			HVACArray[1] = 0;
		}
	});
	$("#Floor_Button").click(function (e) {
		if (Floor_On == false) {
			Floor_On = true;
			HVACArray[2] = 1;
		}
		else {
			Floor_On = false;
			HVACArray[2] = 0;
		}
	});
	$("#PannelFloor_Button").click(function (e) {
		if (PannelFloor_On == false) {
			PannelFloor_On = true;
			HVACArray[3] = 1;
		}
		else {
			PannelFloor_On = false;
			HVACArray[3] = 0;
		}
	});
	$("#Defrost_Button").click(function (e) {
		if (Defrost_On == false) {
			Defrost_On = true;
			HVACArray[4] = 1;
		}
		else {
			Defrost_On = false;
			HVACArray[4] = 0;
		}
	});


	$("#FanUp").click(function (e) {
		if (FanLevel <= 7) {
			FanLevel++;
		}
		HVACArray[5] = FanLevel * 35;
		switch (FanLevel) {
		case 1: {
			document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'white';
			//document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';
		}
		break;
		case 2: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 3: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 4: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 5: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			document.getElementById("Fan4").style.backgroundColor = 'black';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 6: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			document.getElementById("Fan5").style.backgroundColor = 'black';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 7: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			//document.getElementById("Fan5").style.backgroundColor = 'black';
			document.getElementById("Fan6").style.backgroundColor = 'black';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 8: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			//document.getElementById("Fan5").style.backgroundColor = 'black';
			//document.getElementById("Fan6").style.backgroundColor = 'black';
			document.getElementById("Fan7").style.backgroundColor = 'black';

		}
		break;
		default: {
			document.getElementById("Fan0").style.backgroundColor = 'white';
			//document.getElementById("Fan1").style.backgroundColor = 'white';
			//document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		}
	});
	$("#FanDown").click(function (e) {
		if (FanLevel > 0) {
			FanLevel--;
		}
		HVACArray[5] = FanLevel * 35;
		switch (FanLevel) {
		case 1: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			document.getElementById("Fan1").style.backgroundColor = 'white';
			//document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 2: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 3: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 4: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 5: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 6: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			//document.getElementById("Fan5").style.backgroundColor = 'black';
			document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		case 7: {
			//document.getElementById("Fan0").style.backgroundColor = 'black';
			//document.getElementById("Fan1").style.backgroundColor = 'black';
			//document.getElementById("Fan2").style.backgroundColor = 'black';
			//document.getElementById("Fan3").style.backgroundColor = 'black';
			//document.getElementById("Fan4").style.backgroundColor = 'black';
			//document.getElementById("Fan5").style.backgroundColor = 'black';
			//document.getElementById("Fan6").style.backgroundColor = 'black';
			document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		default: {
			document.getElementById("Fan0").style.backgroundColor = 'white';
			//document.getElementById("Fan1").style.backgroundColor = 'white';
			//document.getElementById("Fan2").style.backgroundColor = 'white';
			//document.getElementById("Fan3").style.backgroundColor = 'white';
			//document.getElementById("Fan4").style.backgroundColor = 'white';
			//document.getElementById("Fan5").style.backgroundColor = 'white';
			//document.getElementById("Fan6").style.backgroundColor = 'white';
			//document.getElementById("Fan7").style.backgroundColor = 'white';

		}
		break;
		}
	});

	//Socket handlers

	var socket = io.connect("http://localhost:8001");

	socket.on('data', function(data){
		// Do something with the data.
		//ex: ui.setBatTemp(data.highBatTemp)
	});

});