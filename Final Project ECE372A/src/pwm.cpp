#include "pwm.h"
#include <avr/io.h>
#include <util/delay.h> // For delays

PWM::PWM() {};

void PWM::initPWM_Pins()
{
  // Configure Timer4 for Fast PWM mode with TOP at OCR4A
  TCCR4A |= (1 << WGM40) | (1 << WGM41);
  TCCR4B |= (1 << WGM42) | (1 << WGM43);

  // Non-inverting mode for OC4C (Pin 8)
  TCCR4A &= ~(1 << COM4C0);
  TCCR4A |= (1 << COM4C1);

  // Set prescaler to 1
  TCCR4B |= (1 << CS40);

  this->playChirpAlarm();

}

void PWM::SetFrequency(unsigned int frequency)
{
  // Set the PWM frequency
  OCR4A = 16000000 / frequency; // Calculate TOP value
  OCR4C = OCR4A / 50;
}

// Function to play a chirping sound
void PWM::playChirpAlarm()
{
  // Define the chirp range and timing
  for (int i = 1000; i < 4000; i++)
  {
    this->SetFrequency(i);
  }
}
