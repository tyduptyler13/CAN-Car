#include <node.h>
#include <v8.h>

#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <array>
#include <string>
#include "canlib.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>

#define byte unsigned char

using namespace std;
using namespace v8;
using namespace node;

namespace EcoCarUI{

class CANInterface{
private:
	double highBatTemp;
	double lowBatTemp;
	double HVvolt;
	double HVamp;
	double HVpercent;
	double twelvev;
	double tank1Temp;
	double tank2Temp;
	double tank3Temp;
	double tank1Pressure;
	double tank2Pressure;
	double tank3Pressure;

	//Factors and offsets to get real numbers in C and PSI
	const double temp_factor;
	const double temp_offset;
	const double pressure_factor;
	const double pressure_offset;

	//Thread variables
	volatile bool running;
	thread channel;
	mutex dataLock;

	//Core functions

	//Takes an array of bytes and returns a string of bits given a starting point and length
	static unsigned int parse(int start, int length, byte feed[]){
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

	//This function will reverse the bits in a single Byte of data!!!
	static byte reverseBits(byte msg){
		unsigned char result = msg;
		for (int j = sizeof(msg)* 8 - 1; j; --j){
			result <<= 1;
			msg >>= 1;
			result |= msg & 1;
		}
		return result;
	}


	static int openChannel(const int channel){
		return canOpenChannel(channel, 0); //ARGS: Channel, Flags
	}

	static int closeChannel(int handle){
		return canClose(handle);
	}

	//BCM_Data1 (0x430): Battery temp
	void batteryTemp(byte data[8]){
		byte reverseData[8]; //Holds data array with bits revrsed

		for (int i = 0; i < 8; i++){
			reverseData[i] = reverseBits(data[7 - i]);
		}

		dataLock.lock();
		highBatTemp = parse(32, 8, reverseData)*0.5 - 40; // high_bat_temp
		lowBatTemp = parse(40, 8, reverseData)*0.5 - 40; // low_bat_temp
		dataLock.unlock();

	}

	//BCM_status (0x410): High Voltage Stuff: CSU LAN
	void highVolt(byte data[8]){
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

	//12-Volt System (0x1D6) CSU LAN
	void twelveVolt(byte data[8]){

		byte reversedData[7];
		//message is 7 Bytes, Motorolla. Need bits in first byte reversed
		for (int i = 0; i < 7; i++){
			reversedData[i] = reverseBits(data[6 - i]);
		}
		dataLock.lock();
		twelvev = parse(16, 8, reversedData)*0.0784314; // twelve_volt
		dataLock.lock();
	}

	//for Hydrogen Tanks Status (0x102)
	void htank(byte data[8]){

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

	void CANRead(int handle){

		long int id; //Node ID
		byte data[8];
		unsigned int dlc, flags;
		unsigned long timeStamp;
		canStatus stat;
		stringstream sstm;

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

	void run(int c){

		channel = thread([=](){
			running = true;

			int handle = openChannel(c);

			CANRead(handle);

			closeChannel(handle);
		});

	}

public:

	CANInterface(int channel) : temp_factor(0.217325), temp_offset(-61.1482),
	pressure_factor(7.93457), pressure_offset(-812.486) {

		cout << "Debug: Creating CANInterface" << endl;

		canInitializeLibrary();

		run(channel);

	}

	~CANInterface(){
		if (!isStopped()){
			stop();
		}
	}

	void stop(){
		running = false;
	}

	bool isStopped(){
		return running;
	}

	double getHighBatTemp(){
		dataLock.lock();
		double val = highBatTemp;
		dataLock.unlock();
		return val;
	}

	double getLowBatTemp(){
		dataLock.lock();
		double val = lowBatTemp;
		dataLock.unlock();
		return val;
	}
	double getHVvolt(){
			dataLock.lock();
			double val = HVvolt;
			dataLock.unlock();
			return val;
		}
	double getHVamp(){
			dataLock.lock();
			double val = HVamp;
			dataLock.unlock();
			return val;
		}
	double getHVpercent(){
			dataLock.lock();
			double val = HVpercent;
			dataLock.unlock();
			return val;
		}
	double getTwelvev(){
			dataLock.lock();
			double val = twelvev;
			dataLock.unlock();
			return val;
		}
	double getTank1Temp(){
			dataLock.lock();
			double val = tank1Temp;
			dataLock.unlock();
			return val;
		}
	double getTank2Temp(){
				dataLock.lock();
				double val = tank2Temp;
				dataLock.unlock();
				return val;
			}
	double getTank3Temp(){
				dataLock.lock();
				double val = tank3Temp;
				dataLock.unlock();
				return val;
			}
	double getTank1Pressure(){
				dataLock.lock();
				double val = tank1Pressure;
				dataLock.unlock();
				return val;
			}
	double getTank2Pressure(){
					dataLock.lock();
					double val = tank2Pressure;
					dataLock.unlock();
					return val;
				}
	double getTank3Pressure(){
					dataLock.lock();
					double val = tank3Pressure;
					dataLock.unlock();
					return val;
				}
};

class CNI : public ObjectWrap{

private:

	CANInterface* target;

public:
	static Handle<Value> New(const Arguments &args){

		cout << "Debug: Creating new CNI" << endl;

		if (args.Length() != 1){
			cout << "Error: Invalid arguments length" << endl;
			return ThrowException(String::New("Expected one argument!"));
		}

		if (!args[0]->IsNumber()){
			return ThrowException(String::New("Expected one number as an argument."));
		}

		int channel = args[0]->ToInteger()->Value();

		CNI* wrapper = new CNI(channel);

		wrapper->Wrap(args.Holder());

		return args.Holder();

	}

	static Handle<Value> GetHighBatTemp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getHighBatTemp());

	}
	static Handle<Value> GetLowBatTemp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getLowBatTemp());

	}
	static Handle<Value> GetHVvolt(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getHVvolt());

	}
	static Handle<Value> GetHVamp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getHVamp());

	}
	static Handle<Value> GetHVpercent(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getHVpercent());

	}
	static Handle<Value> GetTwelvev(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTwelvev());

	}
	static Handle<Value> GetTank1Temp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank1Temp());

	}
	static Handle<Value> GetTank2Temp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank2Temp());

	}
	static Handle<Value> GetTank3Temp(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank3Temp());

	}
	static Handle<Value> GetTank1Pressure(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank1Pressure());

	}
	static Handle<Value> GetTank2Pressure(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank2Pressure());

	}
	static Handle<Value> GetTank3Pressure(const Arguments &args){

		if (args.Length() > 0){
			return ThrowException(String::New("Unexpected arguments"));
		}

		CNI* handle = Unwrap<CNI>(args.Holder());

		return Number::New(handle->target->getTank3Pressure());

	}

	CNI(int channel){
		target = new CANInterface(channel);
	}

	~CNI(){
		target->stop(); //Being nice and stopping first.
		delete target;
	}

};

static void Init(Handle<Object>& exports){

	HandleScope scope;

	cout << "Debug: Creating CNI" << endl;

	Handle<FunctionTemplate> it = FunctionTemplate::New(CNI::New);

	NODE_SET_PROTOTYPE_METHOD(it, "getHighBatTemp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHighLowTemp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVvolt", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVamp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVpercent", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTwelvev", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Temp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Temp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Temp", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Pressure", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Pressure", CNI::GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Pressure", CNI::GetHighBatTemp);

	exports->Set(String::NewSymbol("CANInterface"), it->GetFunction());

	cout << "Debug: Created symbol for CANInterface" << endl;

}

NODE_MODULE(CANInterface, Init)

}

