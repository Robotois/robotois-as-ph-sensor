#include <node.h>
#include "PhWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PhWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  PhWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(PhSensor, InitAll)
