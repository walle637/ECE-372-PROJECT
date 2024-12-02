#include "timer.h"

Timer::Timer() {};

void Timer::initTimer1()
{
    // To set into CTC mode, we need WGM13 to be 0, WGM12 to be 1, WGM11 to 0, WGM10 to be 0
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}

/* This delays the program an amount of milliseconds specified by unsigned int delay.
 */
void Timer::delayMs(unsigned int delay)
{
    unsigned int count = 0;

    // want a time delay of 1 us, so count = (Time delay * frequency of clock)/Prescalar
    // 16000 = (1ms * 16MHz)/1

    // Need to interface a 16 bit module, which means writing the high byte first, then the low byte
    // 16 in hex is 00 10
    OCR1A = 15999;

    // Turn on timer with default clock source, no prescaler delay
    TCCR1B &= ~((1 << CS12) | (1 << CS11));
    TCCR1B |= (1 << CS10); // by setting CS12 CS11 CS10 to 001, turn on clock

    while (count < delay)
    { // while count is less than delay

        // Sets the timer flag to 1
        TIFR1 |= (1 << OCF1A); // logic 1 is flag down

        // Set the timer register to 0
        TCNT1 = 0;

        // while flag is down do not do anything
        while (!(TIFR1 & (1 << OCF1A)))
            ; //! number is equivalent to number != 0
        // when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; // 1 microsecond delay as been achieved, go to next microsecond
    }

    // turn timer off
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}
