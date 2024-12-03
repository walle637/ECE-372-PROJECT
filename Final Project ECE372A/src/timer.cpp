#include "timer.h"

Timer::Timer() {};

void Timer :: initTimer1(){
//To set into CTC mode, we need WGM13 to be 0, WGM12 to be 1, WGM11 to 0, WGM10 to be 0
    TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}


void Timer :: delaySec(unsigned int delay) {
        unsigned int count = 0;

    //want a time delay of 1 s, so count = (Time delay * frequency of clock)/Prescalar
    //62500 = (1s * 16MHz)/256

    //Need to interface a 16 bit module, which means writing the high byte first, then the low byte
    //16 in hex is 00 10
    
    OCR1A = 62499;

    //try this if OCR1A doesn't work
    //OCR1AH = 0b11110100;
    //OCR1AL = 0b00100011;
    

    //Turn on timer with default clock source, no prescaler delay
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~((1 << CS11) | (1 << CS10)); //by setting CS12 CS11 CS10 to 100, turn on clock

    while(count < delay){ //while count is less than delay
        
        //Sets the timer flag to 1
        TIFR1 |= (1 << OCF1A); //logic 1 is flag down
        
        //Set the timer register to 0
        TCNT1 = 0;

        //while flag is down do not do anything
        while(!(TIFR1 & (1 << OCF1A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //1 second delay as been achieved, go to next second
    }

    //turn timer off
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}





void Timer:: initTimer0(){

    //Setting timer 0 into CTC mode 
    TCCR0A &= ~(1 << WGM00); //Sets WGM00 bit to 0
    TCCR0A |= (1 << WGM01); //Sets WGM01 bit to 1
    TCCR0B &= ~(1 << WGM02); //sets WGM02 bit to 0

    //By setting WGM00 WGM01 WGM02 bits to 010 (respectively), we've now set timer0 into CTC mode!

}

void Timer:: delayMs(unsigned int delay){
   unsigned int count = 0;
    //delay will be measured in milliseconds, and with a prescalar of 64 so OCR0A will count to 1 ms every 250 counts

    OCR0A = 250; //this will make sure each time the flag goes down, it has delayed by 1 ms
    //OCROA = (Time delay * frequency of clock)/Prescalar

    //Normal clock frequency of 16MHz
    //These statements starts the timer with the prescalar set to 64
    TCCR0B &= ~(1 << CS02);
    TCCR0B |= ((1 << CS01) | (1 << CS00));

    while(count < delay){ //if we still need to delay by more miliseconds
       
        TIFR0 |= (1 << OCF0A); //this sets the CTC flag down, so that we can start a new clock delay (flag down is logic 1)
        TCNT0 = 0; //clears the timer      
       
        //while flag is down do not do anything
        while(!(TIFR0 & (1 << OCF0A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //increment counter
    }
    

    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); //turns timer off
}

void Timer::delayUs(unsigned int delay){
    unsigned int count = 0;

    //want a time delay of 1 us, so count = (Time delay * frequency of clock)/Prescalar
    //16 = (1us * 16MHz)/1

    //Need to interface a 16 bit module, which means writing the high byte first, then the low byte
    //16 in hex is 00 10
    OCR1A = 16;
    

    //Turn on timer with default clock source, no prescaler delay
    TCCR1B &= ~((1 << CS12) | (1 << CS11));
    TCCR1B |= (1 << CS10); //by setting CS12 CS11 CS10 to 001, turn on clock

    while(count < delay){ //while count is less than delay
        
        //Sets the timer flag to 1
        TIFR1 |= (1 << OCF1A); //logic 1 is flag down
        
        //Set the timer register to 0
        TCNT1 = 0;

        //while flag is down do not do anything
        while(!(TIFR1 & (1 << OCF1A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        count++; //1 microsecond delay as been achieved, go to next microsecond
    }

    //turn timer off
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

}
