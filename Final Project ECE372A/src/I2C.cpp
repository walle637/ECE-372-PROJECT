#include "I2C.h"
#include "Arduino.h"
#define wait_for_completion        \
    while (!(TWCR & (1 << TWINT))) \
        ;

void I2C::InitI2C()
{

    PRR0 &= ~(1 << PRTWI);

    TWSR &= ~((1 << TWPS1) | (1 << TWPS0)); // set the prescalar to 1

    TWBR = 0x12; // TWBR = (CPU_Freq / (2 * SCL_Freq * 4^TWPS)) - 2; Used SCL_Freq = 100 kHz since it is the standard freq to use on most microcontroller

    TWCR = (1 << TWEN); // TWEN enables the I2C interface

    this->StartI2C_Trans(0x68);
    this->Send(0x6B); // Power management register
    this->Send(0x00); // Wake up
    this->StopI2C_Trans();

}

void I2C::StartI2C_Trans(unsigned char SLA)
{
    TWCR = ((1 << TWEN) | (1 << TWSTA) | (1 << TWINT)); // Initiate start condition

    wait_for_completion; // Wait for start condition completion

    TWDR = (SLA << 1); // Shift address and set R/W bit based on operation

    TWCR = ((1 << TWEN) | (1 << TWINT)); // Trigger action: Clear TWINT and enable TWI

    wait_for_completion; // Wait for SLA transmission completion
}

void I2C::StopI2C_Trans()
{

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Trigger action + stop condition (TWSTO)
}

void I2C::Send(unsigned char data)
{
    TWDR = data;                       // Load the data to the TWDR register
    TWCR = (1 << TWINT) | (1 << TWEN); // Clear the TWINT flag to start transmission and enable TWI
    wait_for_completion;               // Wait for the transmission to complete

    // Check for acknowledgment (ACK) from the slave
    if ((TWSR & 0xF8) != 0x28) // 0x28 = Data transmitted, ACK received
    {
        // Handle error: No ACK received
    }
}



unsigned char I2C::Read_from(unsigned char SLA, unsigned char MEMADDRESS){
 // this function sets up reading from SLA at the SLA MEMADDRESS
    StartI2C_Trans(SLA);
    Send(MEMADDRESS);
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restart to switch to read mode
    wait_for_completion;
    TWDR = ((SLA << 1) | 0x01); // 7 bit address for slave plus read bit
    TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);// trigger with master sending ack
    wait_for_completion;
    TWCR = (1<< TWINT) | (1 << TWEN); // master can send a nack now
    wait_for_completion;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop condition
    // after this function is executed the TWDR register has the data from SLA that Master wants to read
    return TWDR;
}