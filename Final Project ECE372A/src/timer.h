#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

class Timer
{
public:
    Timer();
    void initTimer1();
    void delayMs(unsigned int delay);
};

#endif