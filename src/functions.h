#ifndef function_h
#define function_h

#include <Arduino.h>

float readTemp(int var){
  return (float(analogRead(0)/1023.0)*5.0);
}

Message dummyRead(Message input=Message()){
  Message dummy_output = Message();
  Serial.print("Dummy function = ");
  Serial.println(input.getData(0xAA));
  return dummy_output;
}

Message dummyWrite(Message input=Message()){
  Serial.println("Dummy Write");
  Message out = Message();
  out.addData(0xAA, 300);
  return out;
}

#endif