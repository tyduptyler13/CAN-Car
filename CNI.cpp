
#include "CNI.h"

#include <iostream>

using namespace std;
using namespace v8;

Persistent<Function> CNI::constructor;

void CNI::Init(Handle<Object>& exports){

	cout << "Debug: CNI Init Start" << endl;

	Local<FunctionTemplate> it = FunctionTemplate::New(New);

	it->SetClassName(String::NewSymbol("CNI"));
	it->InstanceTemplate()->SetInternalFieldCount(12);
	NODE_SET_PROTOTYPE_METHOD(it, "getHighBatTemp", GetHighBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getLowBatTemp", GetLowBatTemp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVvolt", GetHVvolt);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVamp", GetHVamp);
	NODE_SET_PROTOTYPE_METHOD(it, "getHVpercent", GetHVpercent);
	NODE_SET_PROTOTYPE_METHOD(it, "getTwelvev", GetTwelvev);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Temp", GetTank1Temp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Temp", GetTank2Temp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Temp", GetTank3Temp);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank1Pressure", GetTank1Pressure);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank2Pressure", GetTank2Pressure);
	NODE_SET_PROTOTYPE_METHOD(it, "getTank3Pressure", GetTank3Pressure);
	NODE_SET_PROTOTYPE_METHOD(it, "setAC", SetAC); //set HVAC on/off


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

	return scope.Close(Number::New(handle->target->GetHighBatTemp()));

}

Handle<Value> CNI::GetLowBatTemp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetLowBatTemp()));

}

Handle<Value> CNI::GetHVvolt(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetHVvolt()));

}

Handle<Value> CNI::GetHVamp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetHVamp()));

}

Handle<Value> CNI::GetHVpercent(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetHVpercent()));

}

Handle<Value> CNI::GetTwelvev(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTwelvev()));

}

Handle<Value> CNI::GetTank1Temp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank1Temp()));

}

Handle<Value> CNI::GetTank2Temp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank2Temp()));

}

Handle<Value> CNI::GetTank3Temp(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank3Temp()));

}

Handle<Value> CNI::GetTank1Pressure(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank1Pressure()));

}

Handle<Value> CNI::GetTank2Pressure(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank2Pressure()));

}

Handle<Value> CNI::GetTank3Pressure(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(handle->target->GetTank3Pressure()));

}
// HVAC call
Handle<Value> CNI::SetAC(const Arguments &args){

	HandleScope scope;

	if (args.Length() > 0){
		ThrowException(Exception::TypeError(String::New("Unexpected arguments")));
		return scope.Close(Undefined());
	}

	CNI* handle = Unwrap<CNI>(args.Holder());

	return scope.Close(Number::New(SetAC()->target->handle));

}
