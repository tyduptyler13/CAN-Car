#include <node.h>
#include <v8.h>

#include <iostream>
#include <stdio.h>
#include <array>
#include <fstream>
#include <string>
#include "canlib.h"
#include <sstream>

using namespace System;
double dataArray[14] = { 0.0 };
using namespace std;
using namespace v8;



Handle<Value> Method(const Arguments& args){
	HandleScope scope;

	canInitializeLibrary();

	int handle = canOpenChannel(0, 0);

	return scope.Close(Integer::New(handle));
}

void init(Handle<Object> exports){
	exports->Set(String::NewSymbol("testChannel"),
			FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(CANInterface, init)
