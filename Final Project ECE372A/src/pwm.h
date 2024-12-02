#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

class PWM
{
public:
    PWM();
    void initPWM_Pins();
    void SetFrequency(unsigned int frequency);
    void PWM::playChirpAlarm();
};

#endif