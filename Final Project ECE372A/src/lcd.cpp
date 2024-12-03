// Author: Simon Ngandu
// Net ID: 
// Date: 10/14/2024
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

/*
 * Initializes all pins related to the LCD to be outputs
 */
void LCD::initLCDPins(){
  DDRB |= ((1 << DDB6) | (1 << DDB4));

  DDRA |= ((1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3));
}

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void LCD::fourBitCommandWithDelay(unsigned char data, unsigned int delay){

  PORTA = ((PORTA & 0xF0) | (data & 0x0F));

  PORTB &= ~(1 << PORTB6);

  PORTB |= (1 << PORTB4);

  timerDummy.delayUs(1);

  PORTB &= ~(1 << PORTB4);

  timerDummy.delayUs(delay);
}

/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void LCD::eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  PORTA = ((PORTA & 0xF0) | ((command >> 4) & 0x0F));

  PORTB &= ~(1 << PORTB6);

  PORTB |= (1 << PORTB4);

  timerDummy.delayUs(1);

  PORTB &= ~(1 << PORTB4);

  PORTA = ((PORTA & 0xF0) | (command & 0x0F));

  PORTB |= (1 << PORTB4);

  timerDummy.delayUs(1);

  PORTB &= ~(1 << PORTB4);

  timerDummy.delayUs(delay);
}

/* Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void LCD::writeCharacter(unsigned char character){
  PORTA = ((PORTA & 0xF0) | ((character >> 4) & 0x0F));

  PORTB |= (1 << PORTB6);

  PORTB |= (1 << PORTB4);

  timerDummy.delayUs(1);

  PORTB &= ~(1 << PORTB4);

  PORTA = ((PORTA & 0xF0) | (character & 0x0F));

  PORTB |= (1 << PORTB4);

  timerDummy.delayUs(1);

  PORTB &= ~(1 << PORTB4);

  timerDummy.delayUs(46);
}

/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void LCD::writeString(const char *string){
  while(*string != '\0') {
    writeCharacter(*string);
    string++;
  }
}

/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void LCD::moveCursor(unsigned char x, unsigned char y){
	eightBitCommandWithDelay(((0x80) | (x <<6) | (y)), 46);
}

/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void LCD::initLCDProcedure(){
  // Delay 15 milliseconds
  timerDummy.delayMs(15);
  // Write 0b0011 to DB[7:4] and delay 4100 microseconds
  fourBitCommandWithDelay(0b0011, 4100);
  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0b0011, 100);
  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  // write 0b0011 to DB[7:4] and 100us delay
  fourBitCommandWithDelay(0b0011, 100);
  // write 0b0010 to DB[7:4] and 100us delay.
  fourBitCommandWithDelay(0b0010, 100);
  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0b00101000, 53);
  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0b00001000, 53);
  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0b00000001, 3000);
  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0b00000110, 53);
  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  eightBitCommandWithDelay(0b00001100, 53);
}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void LCD::initLCD(){
  initLCDPins();
  initLCDProcedure();
}

void LCD::setCGRAM(unsigned char x) {
  eightBitCommandWithDelay(x, 46);
}