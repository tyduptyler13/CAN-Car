
#include "CNI.h"

#include <iostream>

using namespace std;
using namespace v8;

Persistent<Function> CNI::constructor;

void CNI::Init(Handle<Object>& exports){

	cout << "Debug: CNI Init Start" << endl;

	Local<FunctionTemplate> it = FunctionTemplate::New(New);

	it->SetClassName(String::NewSymbol("CNI"));
	it->InstanceTemplate()->SetInternalFieldCount(1); //TODO add the rest.
	NODE_SET_PROTOTYPE_METHOD(it, "getHighBatTemp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHighLowTemp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVvolt", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVamp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVpercent", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTwelvev", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Temp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Temp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Temp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Pressure", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Pressure", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Pressure", GetHighBatTemp);


	constructor = Persistent<Function>::New(it->GetFunction());

	exports->Set(String::NewSymbol("CNI"), constructor);

	cout << "Debug: CNI Init End" << endl;
}

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

Handle<Value> CNI::GetLowBatTemp(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getLowBatTemp());

}

Handle<Value> CNI::GetHVvolt(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getHVvolt());

}

Handle<Value> CNI::GetHVamp(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getHVamp());

}

Handle<Value> CNI::GetHVpercent(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getHVpercent());

}

Handle<Value> CNI::GetTwelvev(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTwelvev());

}

Handle<Value> CNI::GetTank1Temp(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank1Temp());

}

Handle<Value> CNI::GetTank2Temp(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank2Temp());

}

Handle<Value> CNI::GetTank3Temp(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank3Temp());

}

Handle<Value> CNI::GetTank1Pressure(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank1Pressure());

}

Handle<Value> CNI::GetTank2Pressure(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank2Pressure());

}

Handle<Value> CNI::GetTank3Pressure(const Arguments &args){

	if (args.Length() > 0){
		return ThrowException(String::New("Unexpected arguments"));
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return Number::New(handle->target->getTank3Pressure());

}
