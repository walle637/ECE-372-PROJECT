#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

class Timer
{
public:
    Timer();
    void initTimer1();
    void initTimer0();
    void delayMs(unsigned int delay);
    void delaySec(unsigned int delay);

};

#endif