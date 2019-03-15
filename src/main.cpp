#include <Arduino.h>

#include <peripheal.h>
#include <task.h>
#include <message.h>
#include <universal.h>

#include <com.h>

#include "functions.h"

Com uart = Com(0x7E);

void setup() {
  pinMode(3, INPUT);
  Serial.begin(115200);
}

void loop() {
  if(uart.available(Serial)){
    Message input = uart.readQueue();
    uart.send(Serial, input);
  }
  if(digitalRead(3)){
    while(digitalRead(3)){}
    Message dummy = Message();
    dummy.addData(0x10, 0x0A64);
    uart.send(Serial, dummy);
  }
}

