#include <node.h>
#include <v8.h>

#include "canlib.h"

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
