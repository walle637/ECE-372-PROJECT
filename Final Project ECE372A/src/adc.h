#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
class _ADC
{
public:
    // Function declarations
    void initADC0();
    unsigned int readADC();
};

#endif // ADC_H
