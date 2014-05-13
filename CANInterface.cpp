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

byte CANInterface::reverseBits(byte msg){
	unsigned char result = msg;
	for (int j = sizeof(msg)* 8 - 1; j; --j){
		result <<= 1;
		msg >>= 1;
		result |= msg & 1;
	}
	return result;
}

void CANInterface::batteryTemp(byte data[8]){
	byte reverseData[8]; //Holds data array with bits revrsed

	//Motorola Convention: 8-bytes
	//need to reverse bit order in array!
	for (int i = 0; i < 8; i++){
		reverseData[i] = reverseBits(data[7 - i]);
	}

	dataLock.lock();
	highBatTemp = parse(32, 8, reverseData)*0.5 - 40; // high_bat_temp
	lowBatTemp = parse(40, 8, reverseData)*0.5 - 40; // low_bat_temp
	dataLock.unlock();
	
	dataArray[6] =  highBatTemp;
	dataArray[7] = lowBatTemp;
}
/*
 inline int CANInterface::openChannel(const int channel){
	int handle;
	int stat;

	canInitializeLibrary();
	handle = canOpenChannel(channel, 0); //ARGS: Channel, Flags
	printf("handle is: %i", handle);
	canSetBusOutputControl(handle, canDRIVER_NORMAL);
	stat = canSetBusParams(handle, canBITRATE_500K, 0, 0, 0, 0, 0);
	canBusOn(handle);

	if (stat < 0){
		printf("canBusOn failed, status = %d\n", stat);
		exit(1);
	}
	return handle;
}*/

void CANInterface::highVolt(byte data[8]){
	byte reverseData[8]; //Holds data array with bits reversed

	//Motorola Convention: 8-bytes
	//need to reverse bit order in array!
	for (int i = 0; i < 8; i++){
		reverseData[7 - i] = reverseBits(data[i]);
	}
	//parse out the data we need from the message
	dataLock.lock();
	HVvolt = parse(56, 12, reverseData)*0.25; // HV_volt
	HVamp  = parse(40, 16, reverseData)*0.025 - 1000; // HV_amp
	HVpercent = parse(24, 8, reverseData)*0.5; // HV_percent
	dataLock.unlock();
	
	dataArray[1] = HVvolt;
	dataArray[0] = HVamp;
	dataArray[11] = HVpercent;
}

void CANInterface::twelveVolt(byte data[8]){
	byte reversedData[7];
	//message is 7 Bytes, Motorola. Need bits in first byte reversed
	for (int i = 0; i < 7; i++){
		reversedData[i] = reverseBits(data[6 - i]);
	}
	dataLock.lock();
	twelvev = parse(16, 8, reversedData)*0.0784314; // twelve_volt
	dataLock.lock();
	
	dataArray[5] = twelvev;
}

void CANInterface::htank(byte data[8]){
	//perform necessary math corrections to "raw" data
	dataLock.lock();
	tank1Temp = (parse(0, 10, data) * temp_factor) + temp_offset; // tank1_temp
	tank2Temp = (parse(10, 10, data) * temp_factor) + temp_offset; // tank2_temp
	tank3Temp = (parse(20, 10, data) * temp_factor) + temp_offset; // tank3_temp

	tank1Pressure = (parse(30, 10, data) * pressure_factor) + pressure_offset; // tank1_pressure
	tank2Pressure = (parse(40, 10, data) * pressure_factor) + pressure_offset; // tank2_pressure
	tank3Pressure = (parse(50, 10, data) * pressure_factor) + pressure_offset; // tank3_pressure
	dataLock.unlock();
	
	dataArray[8] = tank1Temp;
	dataArray[9] = tank2Temp;
	dataArray[10] = tank3Temp;

	dataArray[2] = tank1Pressure;
	dataArray[3] = tank2Pressure;
	dataArray[4] = tank3Pressure;
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
			cout<<endl<<stat<<endl;
			/*Scan CAN IDs and call appropriate functions
			switch (id){
			case 258: htank(data); break;
			case 776: batteryTemp(data); break; // IDs are Motorola Adjusted
			case 520: highVolt(data); break; // IDs are Motorola Adjusted
			case 430: twelveVolt(data); break; // IDs are Motorola Adjusted
			}*/
			if(id==258){
				htank(data);
				}
			else if(id==776){
				batteryTemp(data);
			}
			else if(id==520){
				highVolt(data);
			}
			else if(id==430){
				twelveVolt(data);
			}

			//Temporary code to print data pulled in dataArray (Also temporary for debugging)
			for(int i=0;i<14;i++){
				cout<< dataArray[i] << ", ";
			}
			cout<< endl;
		} while (stat == canOK);
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}

void CANInterface::run(int c){

	thrd = thread([=](){
		running = true;
		canInitializeLibrary();
		int handle = canOpenChannel(0, 0); //ARGS: Channel, Flags
		printf("handle is: %i", handle);
		
		long int id; //Node ID
	byte data[8];
	unsigned int dlc, flags;
	unsigned long timeStamp;
	canStatus stat;
		
		//debugging here to see if CAN functions will work
		canRead(handle, &id, &data, &dlc, &flags, &timeStamp);
		canSetBusOutputControl(handle, canDRIVER_NORMAL);
		stat = canSetBusParams(handle, canBITRATE_500K, 0, 0, 0, 0, 0);
		cout<<endl<<"STAT IS: "<<stat<<endl;
		stat = canRead(handle, &id, &data, &dlc, &flags, &timeStamp);
		cout<<endl<<"STAT IS: "<<stat<<endl;
		stat = canRead(handle, &id, &data, &dlc, &flags, &timeStamp);
		cout<<endl<<"STAT IS: "<<stat<<endl;
		
		
		//canInitializeLibrary();
		//int handle = openChannel(c);
		//cout<<endl<< handle<<endl<<endl;
		CANRead(handle);

		closeChannel(handle);
	});

}
