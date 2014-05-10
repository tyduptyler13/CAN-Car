#ifndef __CNI_H_
#define __CNI_H_

#include <node.h>
#include <v8.h>

#include "CANInterface.h"

class CNI : public node::ObjectWrap{

private:

	CANInterface* target;
	static v8::Persistent<v8::Function> constructor;

	CNI(int channel);

	~CNI();

	static v8::Handle<v8::Value> New(const v8::Arguments &args);
	static v8::Handle<v8::Value> GetHighBatTemp(const v8::Arguments &args);

public:

	static void Init(v8::Handle<v8::Object>& exports);

};

#endif
