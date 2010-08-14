#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
//-----------------------------------------------------------------------------
void initAdc(void)
{
  ADMUX = 0x00; // Vcc as ref, right adjusted
  ADCSRA = 0x84;  // enable ADC with prescaler 1/128
}
//-----------------------------------------------------------------------------
unsigned short adcRead(unsigned char channel)
{
  ADMUX = channel;                      // select analog channel
  ADCSRA |= 0x40;                       // start conversion
  loop_until_bit_is_set(ADCSRA, ADIF);

  return (ADCL | ADCH<<8);   // read ADC (full 10 bits);

}
//-----------------------------------------------------------------------------
