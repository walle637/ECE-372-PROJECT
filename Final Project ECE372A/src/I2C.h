#ifndef I2C_H
#define I2C_H
#include "avr/io.h"

class I2C
{
public:
    void InitI2C();
    void StartI2C_Trans(unsigned char SLA);
    void StopI2C_Trans();
    void Send(unsigned char data);
    unsigned char Read_data();
    unsigned char Read_from(unsigned char SLA, unsigned char MEMADDRESS);
    int test = 0;
};

#endif