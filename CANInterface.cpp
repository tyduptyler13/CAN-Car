#include <chrono>
#include <iostream>

#include "CANInterface.h"

//dataArray is a temporary structure to hold out CAN data for debugging. WIll be deleted later
double dataArray[14] = { 0.0 };
using namespace std;

CANInterface::CANInterface(int channel) : temp_factor(0.217325), temp_offset(-61.1482),
		pressure_factor(7.93457), pressure_offset(-812.486) {

	cout << "Debug: Creating CANInterface" << endl;

	canInitializeLibrary();

	run(channel);

}

unsigned int CANInterface::parse(int start, int length, byte feed[]){
	start = (64 - start - length);// Calculates new start point in array
	int arrayStart = (start / 8);//Keeps track of which byte in the array we are on
	unsigned int output = 0;

	while (length > 0){
		//Check first to see if we are at the end of a byte
		if ((start % 8) == 7){
			output = (output << 1) | (feed[arrayStart] & 1);
			arrayStart++;//move on to the next byte in the array after this
			start++;
			length--;
		} //if we are not at the end of the byte
		else{
			output = (output << 1) | (feed[arrayStart] >> (7 - (start % 8)) & 1);
			start++;
			length--;
		}
	}
	return output;
}

// BCM_Data1 (0x430): Battery temp
void CANInterface::batteryTemp(byte data[8]){
	
	dataLock.lock();
	highBatTemp = parse(32, 8, data)*0.5 - 40; // high_bat_temp
	lowBatTemp = parse(40, 8, data)*0.5 - 40; // low_bat_temp
	dataLock.unlock();
	
	cout<<"BatteryTemp data:"<<endl; // DELETE: for debugging
	cout<< "\tBattery Temp High: " << highBatTemp << endl; // DELETE: for debugging
	cout<< "\tBattery Temp Low: " <<lowBatTemp << endl << endl; // DELETE: for debugging
}

 inline int CANInterface::openChannel(const int channel){
	int handle;
	int stat;

	canInitializeLibrary();
	handle = canOpenChannel(channel, 0); //ARGS: Channel, Flags
	printf("handle is: %i\n", handle); // DELETE: FOR DEBUGGING ONLY
	canSetBusOutputControl(handle, canDRIVER_NORMAL);
	stat = canSetBusParams(handle, canBITRATE_500K, 0, 0, 0, 0, 0);
	canBusOn(handle);

	if (stat < 0){
		printf("canBusOn failed, status = %d\n", stat);
		exit(1);
	}
	return handle;
}

// BCM_status (0x410): High Voltage Stuff: CSU LAN
void CANInterface::highVolt(byte data[8]){

	//parse out the data we need from the message
	dataLock.lock();
	HVvolt = parse(56, 12, data)*0.25; // HV_volt
	HVamp  = parse(40, 16, data)*0.025 - 1000; // HV_amp
	HVpercent = parse(24, 8, data)*0.5; // HV_percent
	dataLock.unlock();
	
	cout<<"HighVolt data:"<<endl; // DELETE: for debugging
	cout<< "\tHighVoltage Voltage: " <<HVvolt << endl; // DELETE: for debugging
	cout<< "\tHighVoltage Current: " << HVamp << endl; // DELETE: for debugging
	cout<< "\tHighVoltage Percent: " <<HVpercent << endl << endl; // DELETE: for debugging
}

// 12-Volt System (0x1D6) CSU LAN
void CANInterface::twelveVolt(byte data[8]){
	
	dataLock.lock();
	twelvev = parse((16+8), 8, data)*0.0784314; // twelve_volt, + 8 for 7-byte array correction
	dataLock.unlock();
	
	cout<<"TwelveVolt data:"<<endl; // DELETE: for debugging	
	cout<< "\tTwelve Volt Voltage: "<< twelvev << endl << endl; // DELETE: for debugging
}

// For Hydrogen Tanks Status (0x102)
void CANInterface::htank(byte data[8]){

	//Intel Byte order. Need to reverse
	byte newData[8];
	for(int i = 0; i < 8; i++){
		newData[7-i] = data[i];
	}

	//perform necessary math corrections to "raw" data
	dataLock.lock();
	tank1Temp = (parse(0, 10, newData) * temp_factor) + temp_offset; // tank1_temp
	tank2Temp = (parse(10, 10, newData) * temp_factor) + temp_offset; // tank2_temp
	tank3Temp = (parse(20, 10, newData) * temp_factor) + temp_offset; // tank3_temp

	tank1Pressure = (parse(30, 10, newData) * pressure_factor) + pressure_offset; // tank1_pressure
	tank2Pressure = (parse(40, 10, newData) * pressure_factor) + pressure_offset; // tank2_pressure
	tank3Pressure = (parse(50, 10, newData) * pressure_factor) + pressure_offset; // tank3_pressure
	dataLock.unlock();
	
	cout<<"Htank data:"<<endl; // DELETE: for debugging
	cout<< "\tTank 1 Temp: " <<tank1Temp << endl; // DELETE: for debugging
	cout<< "\tTank 2 Temp: " << tank2Temp << endl; // DELETE: for debugging
	cout<< "\tTank 3 Temp: " << tank3Temp << endl; // DELETE: for debugging

	cout<< "\tTank 1 Pressure: " << tank1Pressure << endl; // DELETE: for debugging
	cout<< "\tTank 2 Pressure: " << tank2Pressure << endl; // DELETE: for debugging
	cout<< "\tTank 3 Pressure: " << tank3Pressure << endl << endl; // DELETE: for debugging
}

void CANInterface::CANRead(int handle){

	long int id; //Node ID
	byte data[8];
	unsigned int dlc, flags;
	unsigned long timeStamp;
	canStatus stat;

	while (running){
		//while loop that reads from Kvaser CAN buffer
		do {
			stat = canRead(handle, &id, &data, &dlc, &flags, &timeStamp);
		
			if(id==258){
				htank(data); //For Hydrogen Tanks Status (0x102)
				}
			else if(id==1072) {
				batteryTemp(data); //BCM_Data1 (0x430): Battery temp
			}
			else if(id==1040) {
				highVolt(data); //BCM_status (0x410): High Voltage Stuff: CSU LAN
			}
			else if(id==470) {
				twelveVolt(data); //12-Volt System (0x1D6): CSU LAN
			}

		} while (stat == canOK);
			//Temporary code to print data pulled in dataArray (Also temporary for debugging)
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void CANInterface::run(int c){

	thrd = thread([=](){
		running = true;
		
		/*Following data was taken on March 15, 2014
		byte htank1Array[8] = { 105, 145, 117,  86,  39, 152, 152, 2 };
		//Following data was taken on May 19, 2014
		byte htank2Array[8] = { 126, 217, 149, 215, 147,  67, 106, 9 };
		byte batTempArray[8] = { 31, 254, 63, 254, 254, 254, 0, 119 };
		byte highVoltArray[8] = { 2, 207, 254, 74, 156, 47, 15, 254 };
		byte twelveVoltArray[8] = { 0, 48, 0, 62, 63, 16, 42 };
		
		htank(htank1Array);//TEST CODE: DELETE
		htank(htank2Array);//TEST CODE: DELETE
		batteryTemp(batTempArray);//TEST CODE: DELETE
		highVolt(highVoltArray);//TEST CODE: DELETE
		twelveVolt(twelveVoltArray);//TEST CODE: DELETE*/

		
		// UNDELETE THIS BLOCK OF CODE FOR NORMAL FUNCTION WITH CANBUS
		int handle = openChannel(c); // Get handle for available CANbus port
		CANRead(handle); // Read data from CANbus
		closeChannel(handle); // Clean up
		//UNDELETE THIS BLOCK OF CODE FOR NORMAL FUNCTION WITH CANBUS */
	});

}
