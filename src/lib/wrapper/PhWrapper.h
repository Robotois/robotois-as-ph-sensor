#ifndef PHWRAPPER_H
#define PHWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../PhSensor/PhSensor.h"

class PhWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit PhWrapper(uint8_t _addr = 0x00);
  ~PhWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void reading(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void tempCompensation(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void calibrate(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  PhSensor *sensor;
};

#endif
