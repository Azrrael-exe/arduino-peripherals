#ifndef function_h
#define function_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_MAX_CHARACTERS 16
#define LCD_LINES 2

#define CMD_STATUS  0xA0
#define DATA_JOY    0xD0

LiquidCrystal_I2C lcd(0x27, LCD_MAX_CHARACTERS, LCD_LINES);

void functionsConfig(){
  lcd.init();
  lcd.backlight();
}

Message showStatus(Message input){
  if(input.hasKey(CMD_STATUS)){
    uint8_t status = input.getData(CMD_STATUS, 0);
    uint16_t data = input.getData(DATA_JOY);
    uint8_t x = byte(data >> 8);
    uint8_t y = byte(data);
    char buffer[LCD_MAX_CHARACTERS];
    sprintf(buffer, "x: %03u", x);
    lcd.setCursor(0,0);
    lcd.print(buffer);
    lcd.setCursor(0,1);
    sprintf(buffer, "y: %03u", y);
    lcd.print(buffer);

    lcd.setCursor(13,0);
    switch (status)
    {
      case 0:
        lcd.print(" Ok");
        break;
      case 1:
        lcd.print("Err");
        break;
      default:
        lcd.print("Unk");
        break;
    }
  }
  return Message();
}
Message showInput(Message input){
  char buffer[LCD_MAX_CHARACTERS];
  sprintf(buffer, "New Message! %u", input.dataLength());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(buffer);
  return Message();
}
Message sending(Message input){
  char buffer[LCD_MAX_CHARACTERS];
  sprintf(buffer, "Sending! %u", input.dataLength());
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(buffer);
  return Message();
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