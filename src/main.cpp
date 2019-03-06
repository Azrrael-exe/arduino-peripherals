#include <Arduino.h>

#include <peripheal.h>
#include <task.h>
#include <message.h>
#include <universal.h>

#include "functions.h"

Universal principal = Universal();
Universal secundario = Universal();

void setup() {
  Serial.begin(115200);
}

void loop() {
  principal.attach(0, dummyRead);
  secundario.attach(0, dummyWrite);

  principal.run(0, secundario.readResult(0, Message(), true));

  while(1){
    /* code */
  }
  
}

