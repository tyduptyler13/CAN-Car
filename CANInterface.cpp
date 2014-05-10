#include <chrono>
#include <iostream>

#include "CANInterface.h"

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

	for (int i = 0; i < 8; i++){
		reverseData[i] = reverseBits(data[7 - i]);
	}

	dataLock.lock();
	highBatTemp = parse(32, 8, reverseData)*0.5 - 40; // high_bat_temp
	lowBatTemp = parse(40, 8, reverseData)*0.5 - 40; // low_bat_temp
	dataLock.unlock();
}

void CANInterface::highVolt(byte data[8]){
	byte reverseData[8]; //Holds data array with bits reversed

	//Moterolla Convention: 8-bytes
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
}

void CANInterface::twelveVolt(byte data[8]){
	byte reversedData[7];
	//message is 7 Bytes, Motorolla. Need bits in first byte reversed
	for (int i = 0; i < 7; i++){
		reversedData[i] = reverseBits(data[6 - i]);
	}
	dataLock.lock();
	twelvev = parse(16, 8, reversedData)*0.0784314; // twelve_volt
	dataLock.lock();
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
			printf("\nI found a generic signal!!!\n");
			printf("and here is the message: ");

			//print the H2 tank message
			for (int i = 0; i < 8; i++){
				printf("%3u, ", data[i]);
				//			fprintf(f, "%3u, ", data[i]);
			}
			//		fprintf(f, "Id: %3x\n", id);

			switch (id){
			case 258: htank(data); break;
			case 1072: batteryTemp(data); break;
			case 1040: highVolt(data); break;
			case 470: twelveVolt(data); break;
			}

		} while (stat == canOK);
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}

void CANInterface::run(int c){

	thrd = thread([=](){
		running = true;

		int handle = openChannel(c);

		CANRead(handle);

		closeChannel(handle);
	});

}
