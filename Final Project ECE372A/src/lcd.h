// Author:
// Net ID:
// Date:
// Assignment:     Lab 3
//----------------------------------------------------------------------//

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include "timer.h"
class LCD
{
public:
    void initLCD();
    void fourBitCommandWithDelay(unsigned char data, unsigned int delay);
    void eightBitCommandWithDelay(unsigned char command, unsigned int delay);
    void writeCharacter(unsigned char character);
    void writeString(const char *string);
    void moveCursor(unsigned char x, unsigned char y);
    void initLCDPins();
    void initLCDProcedure();
    void setCGRAM(unsigned char x);
private:
    Timer timerDummy;
};

#endif
