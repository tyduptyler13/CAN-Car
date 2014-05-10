#include <node.h>
#include "CNI.h"

using namespace v8;

void InitAll(Handle<Object> exports){
	CNI::Init(exports);
}

NODE_MODULE(CNI, InitAll)
