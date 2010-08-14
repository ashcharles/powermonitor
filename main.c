#include "defines.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <math.h>

#include "uart.h"
#include "adc.h"
#include "timer.h"

const int LOOP_HZ = 100; // Max: 62500

// Vref ~ 5.0[V]; R1 ~ 20[kOhm]; R1 ~ 5[kOhm]
// SCALE = Vref * (R1 + R2) / (1024 * R1)
const double VIN_SCALE = 0.0244;
const double VOUT_SCALE = 0.0244;

const double R_POWER = 0.5;

//-----------------------------------------------------------------------------
int main(void)
{
  initUart();
  initAdc();
  //char name [80];
  //printf("What is your name?\n");
  //scanf("%s", name);  // this is blocking
  //printf("Hey %s--it looks like the UART is working!\n", name);
  long loop_count = timerInit(LOOP_HZ);
  double vin, vout, current;

  /* main loop */
  while(1) {
    count = loop_count;

    PORTC ^= _BV(5);
    vin = VIN_SCALE * adcRead(6);
    vout = VOUT_SCALE * adcRead(0);
    current = (vin - vout) / R_POWER;
    printf("Vin=%3.3f\tVout=%3.3f\tVCurrent=%3.3f\tPower=%5.5f\n", vin, vout, current, vin * current);

    /* sleep until time expires */
    if( count <= 0 ){printf("WARN:\t loop running slowly\n");}
    while(count > 0) {sleep_mode();}
  }
  return(0);
}
//-----------------------------------------------------------------------------

