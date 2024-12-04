#include <Arduino.h>
#include "I2C.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include <avr/io.h>
#include <Wire.h>

I2C i2c;
Timer timer;
_ADC adc;
LCD lcd;

uint8_t readOneRegister(unsigned char SLA, unsigned char regAddr)
{
  
  // Start I2C in write mode
  uint8_t data = i2c.Read_from(SLA, regAddr); // Read with NACK to end communication
  i2c.StopI2C_Trans();                        // Stop I2C

  return data;
}

byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

// put function definitions here:
int main() {
  i2c.InitI2C();
  lcd.initLCD();
  
  while(1) {
  uint8_t sec = readOneRegister(0x68,0x00); //second
  uint8_t min = readOneRegister(0x68,0x01); //minute
  uint8_t hr = readOneRegister(0x68,0x02);  //hours
   uint8_t d_ay = readOneRegister(0x68,0x04);  //day
  uint8_t mo_nth = readOneRegister(0x68,0x05);  //month
  uint8_t yr = readOneRegister(0x68,0x06);  //year

  sec = bcdToDec(sec);
  min = bcdToDec(min);
  hr = bcdToDec(hr);
  mo_nth = bcdToDec(mo_nth);
  yr = bcdToDec(yr);
  d_ay = bcdToDec(d_ay);

  char stringHr[4];
  sprintf(stringHr, "%02d", hr);
  char stringMin[4];
  sprintf(stringMin, "%02d", min);
  char stringDay[4];
  sprintf(stringDay, "%02d", d_ay);
  char stringMonth[4];
  sprintf(stringMonth, "%02d", mo_nth);
  char stringYr[4];
  sprintf(stringYr, "%d", yr);

  
  Serial.begin(9600);
  
  Serial.print("Time:");
  Serial.print(hr);
  Serial.print(":");
  Serial.print(min);
  Serial.print(":");
  Serial.print(sec);
  
  Serial.print(", Date: ");
  Serial.print(mo_nth);
  Serial.print("/");
  Serial.print(d_ay);
  Serial.print("/20");
  Serial.println(yr);

  lcd.moveCursor(0,0);
  lcd.writeString(stringHr);
  lcd.writeString(":");
  lcd.writeString(stringMin);
  lcd.writeString(" ");
  lcd.writeString(stringMonth);
  lcd.writeString("/");
  lcd.writeString(stringDay);
  lcd.writeString("/20");
  lcd.writeString(stringYr);
  //lcd.writeString("Simon");
  lcd.moveCursor(1,0);
  lcd.writeString("CO2 Level: ");
  //Serial.print(":");
  //Serial.println(min);
  Serial.flush();
  
  }
  return 0;
}
