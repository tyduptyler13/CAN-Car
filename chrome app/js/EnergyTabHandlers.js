
 //Create a new energy chart class to help us
//Turn the different graphs on and off

//var energyChart = new EnergyChart("energy_canvas0");
//var energyChart1 = new EnergyChart("energy_canvas1");

var plot0;
var plot1;
//Storing the Data from Can C++
var HighVoltageCurrentData = new Array();
var HighVoltageData = new Array();
var H2Pressure1 = new Array();
var H2Pressure2 = new Array();
var H2Pressure3 = new Array();
var BatteryVoltageData = new Array();
var BatteryTempData = new Array();
var H2Temp1 = new Array();
var H2Temp2 = new Array();
var H2Temp3 = new Array();
var newData = new Array();
var FuelCellCurrent1;
var FuelCellCurrent2;
var FuelCellTemp1;
var FuelCellTemp2;
var FuelCellVoltage1;
var FuelCellVoltage2;

//Check if CLicked
var BatteryClicked;
var H2Clicked;
var EcoCarClicked;

HighVoltageData = [0];
HighVoltageCurrentData = [0];
H2Pressure1 = [0];
H2Temp1 = [0];
BatteryVoltageData = [0];
BatteryTempData = [0];


$(function(){

//if(HighVoltageData.length > 0){
	//plot0 = new RGraph.Line('energy_canvas0', HighVoltageData).draw();
	plot0 = new RGraph.Line('energy_canvas0', HighVoltageData).draw();
//};
//if(HighVoltageCurrentData.length > 0){
	plot1 = new RGraph.Line('energy_canvas1', HighVoltageCurrentData).draw();
//};

//Right here we need to send NewData to the C++ function put the values in it then read it back this is initial values on start up
newData = [10, 360, 35, 30, 32, 12, 50, 45, 48, 43, 98, 5];

// HighVoltageCurrentData.push(newData[0]);
// HighVoltageCurrentData[0] = hope;
// HighVoltageData.push(newData[1]);
// H2Pressure1.push(newData[2]);
// H2Pressure2.push(newData[3]);
// H2Pressure3.push(newData[4]);
// BatteryVoltageData.push(newData[5]);
// BatteryTempData.push(newData[6]);
// H2Temp1.push(newData[7]);
// H2Temp2.push(newData[8]);
// H2Temp3.push(newData[9]);
// batteryPercentage = newData[10];
    FuelCellCurrent1 = newData[11];
    FuelCellCurrent2 = newData[12];
    FuelCellTemp1 = newData[13];
    FuelCellTemp2 = newData[14];
    FuelCellVoltage1 = newData[15];
    FuelCellVoltage2 = newData[16];


//Add new values to arrays from C++ array
    setInterval(function () {
        
        if (HighVoltageData.length > 10) {
            HighVoltageData.splice(0,1)
        }
        if (HighVoltageCurrentData.length > 10) {
            HighVoltageCurrentData.splice(0, 1)
        }
        if (H2Pressure1.length > 10) {
            H2Pressure1.splice(0, 1)
        }
        if (H2Temp1.length > 10) {
            H2Temp1.splice(0, 1)
        }
        if (BatteryVoltageData.length > 10) {
            BatteryVoltageData.splice(0, 1)
        }
        if (BatteryTempData.length > 10) {
            BatteryTempData.splice(0, 1)
        }

        //We need to once again send NewData to C++ function to put values in this will do it every couple of seconds

   
    if (BatteryClicked == true) {
    //    energyChart.toggleLine(batteryVoltageSettings);
    //    energyChart1.toggleLine(batteryTempSettings);
        document.getElementById("data0").innerHTML = ("Battery Voltage: " + BatteryVoltageData[BatteryVoltageData.length - 1] + " V");
        document.getElementById("data1").innerHTML = ("Battery Temperature: " + BatteryTempData[BatteryTempData.length - 1] + " C");
		//if(BatteryVoltageData.length > 0){
			//RGraph.ObjectRegistry.Remove(plot0);
			RGraph.clear(document.getElementById('energy_canvas0'));
			//plot0 = new RGraph.Line('energy_canvas0', [6,7,8,9]).draw();
			plot0 = new RGraph.Line('energy_canvas0', BatteryVoltageData).draw();
		//};
		//if(BatteryTempData.length > 0){
			//RGraph.ObjectRegistry.Remove(plot1);
			RGraph.clear(document.getElementById('energy_canvas1'));
			//plot1 = new RGraph.Line('energy_canvas1', [6,7,8,9]).draw();
			plot1 = new RGraph.Line('energy_canvas1', BatteryTempData).draw();
		//};
    }
   else if (H2Clicked == true) {
    //    energyChart.toggleLine(hydrogenTempSettings);
    //    energyChart1.toggleLine(hydrogenPressureSettings);
        document.getElementById("data0").innerHTML = ("Hydrogen Temperature: " + H2Temp1[H2Temp1.length - 1] + " C");
        document.getElementById("data1").innerHTML = ("Hydrogen Pressure: " + H2Pressure1[H2Pressure1.length - 1] + " psi");
		//if(H2Temp.length > 0){
			//plot0 = RGraph.Line('energy_canvas0', H2Temp1).draw();
		RGraph.clear(document.getElementById('energy_canvas0'));
		plot0 = new RGraph.Line('energy_canvas0', H2Temp1).draw();		
		//};
		//if(H2Pressure.length > 0){
          //  plot1 = RGraph.Line('energy_canvas1',H2Pressure1).draw();
			//plot1 = RGraph.Gauge('energy_canvas1', H2Pressure1).draw();
			RGraph.clear(document.getElementById('energy_canvas1'));
			plot1 = new RGraph.Line('energy_canvas1', H2Pressure1).draw();			
		//};
    }
    else if (EcoCarClicked == true) {
        document.getElementById("data0").innerHTML = ("H2 Pressure Tank1: " + H2Pressure1[H2Pressure1.length - 1] + " psi");
        document.getElementById("data2").innerHTML = ("H2 Pressure Tank2: " + H2Pressure2[H2Pressure2.length - 1] + " psi");
        document.getElementById("data3").innerHTML = ("H2 Pressure Tank3: " + H2Pressure3[H2Pressure3.length - 1] + " psi");
        document.getElementById("data4").innerHTML = ("H2 Temp Tank1: " + H2Temp1[H2Temp1.length - 1] + " C");
        document.getElementById("data5").innerHTML = ("H2 Temp Tank2: " + H2Temp2[H2Temp2.length - 1] + " C");
        document.getElementById("data1").innerHTML = ("H2 Temp Tank3: " + H2Temp3[H2Temp2.length - 1] + " C");
        document.getElementById("data6").innerHTML = ("Fuel Cell Current: " + FuelCellCurrent + " A");
		
    }
    else {
    //    energyChart.toggleLine(highVoltageSettings);
    //    energyChart1.toggleLine(highVoltageCurrentSettings);
        document.getElementById("data0").innerHTML = ("High Voltage: " + HighVoltageData[HighVoltageData.length - 1] + " V");
        document.getElementById("data1").innerHTML = ("High Voltage Current: " + HighVoltageCurrentData[HighVoltageCurrentData.length - 1] + " A");
		//if(HighVoltageData.length > 0){
			RGraph.clear(document.getElementById('energy_canvas0'));
			plot0 = new RGraph.Line('energy_canvas0', HighVoltageData).draw();
			//plot0 = new RGraph.Line('energy_canvas0', HighVoltageData).draw();

		//};
		//if(HighVoltageCurrentData.length > 0){
			RGraph.clear(document.getElementById('energy_canvas1'));
			plot1 = new RGraph.Line('energy_canvas1', HighVoltageCurrentData).draw();
			//plot1 = new RGraph.Line('energy_canvas1', HighVoltageCurrentData).draw();

		//};
    }
},2000);

//Create the different chart colors and data

//energyChart.toggleLine(highVoltageSettings);
//energyChart1.toggleLine(highVoltageCurrentSettings);
document.getElementById("data0").innerHTML = ("High Voltage: " + HighVoltageData[HighVoltageData.length - 1] + " V");
document.getElementById("data1").innerHTML = ("High Voltage Current: " + HighVoltageCurrentData[HighVoltageCurrentData.length - 1]+" A");

//Click handlers for each of the UI buttons
//They just turn the graphing for that dataset on and off
    $("#High_Voltage").click(function (e) {
        document.getElementById("graph0").style.opacity = 1;
        document.getElementById("graph1").style.opacity = 1;
        document.getElementById("data1").style.top = '50%';
        document.getElementById("data2").style.opacity = 0;
        document.getElementById("data3").style.opacity = 0;
        document.getElementById("data4").style.opacity = 0;
        document.getElementById("data5").style.opacity = 0;
        document.getElementById("data6").style.opacity = 0;

        BatteryClicked = false;
        H2Clicked = false;
        EcoCarClicked = false;

    //    energyChart.toggleLine(highVoltageSettings);
    //    energyChart1.toggleLine(highVoltageCurrentSettings);
		RGraph.clear(document.getElementById('energy_canvas0'));
		plot0 = new RGraph.Line('energy_canvas0', HighVoltageData).draw();
		RGraph.clear(document.getElementById('energy_canvas1'));
		plot1 = new RGraph.Line('energy_canvas1', HighVoltageCurrentData).draw();
        document.getElementById("data0").innerHTML = ("High Voltage: " + HighVoltageData[HighVoltageData.length - 1] + " V");
        document.getElementById("data1").innerHTML = ("High Voltage Current: " + HighVoltageCurrentData[HighVoltageCurrentData.length - 1] + " A");

    });

    $("#12V_Battery").click(function (e) {
        document.getElementById("graph0").style.opacity = 1;
        document.getElementById("graph1").style.opacity = 1;
        document.getElementById("data1").style.top = '50%';
        document.getElementById("data2").style.opacity = 0;
        document.getElementById("data3").style.opacity = 0;
        document.getElementById("data4").style.opacity = 0;
        document.getElementById("data5").style.opacity = 0;
        document.getElementById("data6").style.opacity = 0;

        BatteryClicked = true;
        H2Clicked = false;
        EcoCarClicked = false;

    //    energyChart.toggleLine(batteryVoltageSettings);
    //    energyChart1.toggleLine(batteryTempSettings);
		//plot0.original_data = [1,2,3,4];
		//plot0.draw();
		//plot1.original_data = [1,2,3,4];
		//plot1.draw();
		RGraph.clear(document.getElementById('energy_canvas0'));
		plot0 = new RGraph.Line('energy_canvas0', BatteryVoltageData).draw();
		RGraph.clear(document.getElementById('energy_canvas1'));
		plot1 = new RGraph.Line('energy_canvas1', BatteryTempData).draw();
        document.getElementById("data0").innerHTML = ("Battery Voltage: " + BatteryVoltageData[BatteryVoltageData.length - 1] + " V");
        document.getElementById("data1").innerHTML = ("Battery Temperature: " + BatteryTempData[BatteryTempData.length - 1] + " C");
    });

    $("#Hydrogen").click(function (e) {
        document.getElementById("graph0").style.opacity = 1;
        document.getElementById("graph1").style.opacity = 1;
        document.getElementById("data1").style.top = '50%';
        document.getElementById("data2").style.opacity = 0;
        document.getElementById("data3").style.opacity = 0;
        document.getElementById("data4").style.opacity = 0;
        document.getElementById("data5").style.opacity = 0;
        document.getElementById("data6").style.opacity = 0;

        BatteryClicked = false;
        H2Clicked = true;
        EcoCarClicked = false;

    //    energyChart.toggleLine(hydrogenTempSettings);
    //    energyChart1.toggleLine(hydrogenPressureSettings);
	
		RGraph.clear(document.getElementById('energy_canvas0'));
		plot0 = new RGraph.Line('energy_canvas0', H2Temp1).draw();
		RGraph.clear(document.getElementById('energy_canvas1'));
		plot1 = new RGraph.Line('energy_canvas1', H2Pressure1).draw();
        document.getElementById("data0").innerHTML = ("Hydrogen Temperature: " + H2Temp1[H2Temp1.length - 1] + " C");
        document.getElementById("data1").innerHTML = ("Hydrogen Pressure: " + H2Pressure1[H2Pressure1.length - 1] + " psi");
    });

    $("#EcoCAR").click(function (e) {
        document.getElementById("graph0").style.opacity = 0;
        document.getElementById("graph1").style.opacity = 0;
        document.getElementById("data1").style.top = '55%' ;
        document.getElementById("data2").style.opacity = 1;
        document.getElementById("data3").style.opacity = 1;
        document.getElementById("data4").style.opacity = 1;
        document.getElementById("data5").style.opacity = 1;
        document.getElementById("data6").style.opacity = 1;

        BatteryClicked = false;
        H2Clicked = false;
        EcoCarClicked = true;

        document.getElementById("data0").innerHTML = ("H2 Pressure Tank1: " + H2Pressure1[H2Pressure1.length - 1] + " psi");
        document.getElementById("data2").innerHTML = ("H2 Pressure Tank2: " + H2Pressure2[H2Pressure2.length - 1] + " psi");
        document.getElementById("data3").innerHTML = ("H2 Pressure Tank3: " + H2Pressure3[H2Pressure3.length - 1] + " psi");
        document.getElementById("data4").innerHTML = ("H2 Temp Tank1: " + H2Temp1[H2Temp1.length - 1] + " C");
        document.getElementById("data5").innerHTML = ("H2 Temp Tank2: " + H2Temp2[H2Temp2.length - 1] + " C");
        document.getElementById("data1").innerHTML = ("H2 Temp Tank3: " + H2Temp3[H2Temp2.length - 1] + " C");
        document.getElementById("data6").innerHTML = ("Fuel Cell Current: " + FuelCellCurrent + " A");
    });
});