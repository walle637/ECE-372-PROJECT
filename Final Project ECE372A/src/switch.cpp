#include <avr/io.h>
#include "switch.h"

Switch::Switch() {};

/*Initializes pull-up resistor on PB3 and sets it into input mode*/
void Switch::initSwitchPB5()
{
    DDRB &= ~(1 << DDB5);
    PORTB |= (1 << PORTB5);

    // Turn on pin-change interrupts for PB5
    PCICR |= (1 << PCIE0);   // Enable pin change interrupt for pins 0-7 PCINT[7:0]
    PCMSK0 |= (1 << PCINT5); // Enable interrupt for specifically pin 3 PB5 (PCINT5)
}