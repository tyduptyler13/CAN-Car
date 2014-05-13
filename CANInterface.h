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
		//return stat;//canOpenChannel(channel, 0); //ARGS: Channel, Flags
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

#endif
