#include <Arduino.h>

#include <peripheal.h>
#include <task.h>
#include <message.h>
#include <universal.h>

#include <com.h>

#include "functions.h"

Com uart = Com(0x7E);
Universal screen = Universal();
Universal joystick = Universal();

void setup() {
  pinMode(2, INPUT);
  Serial.begin(115200);
  functionsConfig();

  screen.attach(0, showStatus);
  screen.attach(1, showInput);
  screen.attach(2, sending);

  joystick.attach(0, readJoystick);
}

void loop() {
  if(uart.available(Serial)){
    Message input = uart.readQueue();
    screen.run(1, input);
    uart.send(Serial, input);
  }
  if(digitalRead(2)){
    while(digitalRead(2)){}
    Message dummy = Message();
    dummy.addData(0x10, 0x0A64);
    screen.run(2, dummy);
    uart.send(Serial, dummy);
  }
  Message read = joystick.run(0, Message());
  screen.run(0, read);
}

