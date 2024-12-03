#include <Arduino.h>
#include "I2C.h"
#include <avr/io.h>
#include <Wire.h>

I2C i2c;

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



  //Serial.print(":");
  //Serial.println(min);
  Serial.flush();
  
  }
  return 0;
}


/////////////////////////////////////////////////////////////////////////
/*
#include <Wire.h>
#include <Arduino.h>
#include "I2C.h"
#include <avr/io.h>
#include <Wire.h>
#define DS1307_ADDRESS 0x68

int decToBcd(int val) {
  return ((val / 10 * 16) + (val % 10));
}

void setDS1307Time(int seconds, int minutes, int hours, int dayOfWeek, int day, int month, int year) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // Set register pointer to 0x00 (seconds register)

  Wire.write(decToBcd(seconds));     // Seconds (bit 7 is CH, set to 0 to enable oscillator)
  Wire.write(decToBcd(minutes));     // Minutes
  Wire.write(decToBcd(hours));       // Hours (24-hour format)
  Wire.write(decToBcd(dayOfWeek));   // Day of the week
  Wire.write(decToBcd(day));         // Day of the month
  Wire.write(decToBcd(month));       // Month
  Wire.write(decToBcd(year));        // Year

  Wire.endTransmission();
}
void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Set the current time and date
  // Replace these with the current time and date
  int seconds = 0;    // 0-59
  int minutes = 36;   // 0-59
  int hours = 9;     // 0-23 (24-hour format)
  int dayOfWeek = 3;  // 1=Sunday, 2=Monday, ..., 7=Saturday
  int day = 3;        // Day of the month (1-31)
  int month = 12;     // Month (1-12)
  int year = 24;      // Last two digits of the year (e.g., 24 for 2024)

  setDS1307Time(seconds, minutes, hours, dayOfWeek, day, month, year);

  Serial.println("Time and date have been set on the DS1307.");
}

void loop() {
  // Nothing to do here
}

*/