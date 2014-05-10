
#include "CNI.h"

#include <iostream>

using namespace std;
using namespace v8;

Persistent<Function> CNI::constructor;

CNI::CNI(int channel = 0){
	target = new CANInterface(channel);
}

CNI::~CNI(){
	target->stop(); //Being nice and stopping first.
	delete target;
}

Handle<Value> CNI::New(const Arguments &args){

	cout << "Debug: CNI::New start" << endl;

	HandleScope scope;

	if (args.IsConstructCall()) {

		if (args[0]->IsUndefined() || !args[0]->IsNumber()){
			ThrowException(Exception::TypeError(String::New("Expected one number as an argument.")));
			return scope.Close(Undefined());
		}

		int channel = args[0]->ToInteger()->Value();

		CNI* wrapper = new CNI(channel);
		wrapper->Wrap(args.This());

		cout << "Debug: CNI::New end" << endl;

		return args.This();

	} else {
		//Invoked as a function. Convert to constructor call.
		const int argc = 1;
		Local<Value> argv[argc] = {args[0]};
		return scope.Close(constructor->NewInstance(argc, argv));
	}

}

Handle<Value> CNI::GetHighBatTemp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.This());

	return scope.Close(Number::New(handle->target->getHighBatTemp()));

}

void CNI::Init(Handle<Object>& exports){

	cout << "Debug: CNI Init Start" << endl;

	Local<FunctionTemplate> it = FunctionTemplate::New(New);

	it->SetClassName(String::NewSymbol("CNI"));
	it->InstanceTemplate()->SetInternalFieldCount(1); //TODO add the rest.
	it->PrototypeTemplate()->Set(String::NewSymbol("getHighBatTemp"),
			FunctionTemplate::New(GetHighBatTemp)->GetFunction());

	constructor = Persistent<Function>::New(it->GetFunction());

	exports->Set(String::NewSymbol("CNI"), constructor);

	cout << "Debug: CNI Init End" << endl;
}
