#ifndef __CANInterface_H_
#define __CANInterface_H_

#include <thread>
#include <mutex>

#include "canlib.h"

#define byte unsigned char

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
	std::thread thrd;
	std::mutex dataLock;

	//Core functions

	//Takes an array of bytes and returns a string of bits given a starting point and length
	static unsigned int parse(int start, int length, byte feed[]);

	//This function will reverse the bits in a single Byte of data!!!
	static byte reverseBits(byte msg);


	static inline int openChannel(const int channel){
		return canOpenChannel(channel, 0); //ARGS: Channel, Flags
	}

	static inline int closeChannel(int handle){
		return canClose(handle);
	}

	//BCM_Data1 (0x430): Battery temp
	void batteryTemp(byte data[8]);

	//BCM_status (0x410): High Voltage Stuff: CSU LAN
	void highVolt(byte data[8]);

	//12-Volt System (0x1D6) CSU LAN
	void twelveVolt(byte data[8]);

	//for Hydrogen Tanks Status (0x102)
	void htank(byte data[8]);

	void CANRead(int handle);

	void run(int channel);

public:

	CANInterface(int channel);

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

};

#endif
