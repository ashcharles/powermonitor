#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>

#include "timer.h"

//-----------------------------------------------------------------------------
ISR (TIMER0_OVF_vect) {--count;}
//-----------------------------------------------------------------------------
long timerInit(double loop_freq)
{
    /* run Timer 0 (8 bit) at F_CPU (no prescale) */
    double loop_period = 1000.0 / loop_freq; // in [ms]
    printf("Running main loop with period %4.2f[ms]\n", loop_period);
    double loop_count = loop_period * 62.5; // 16[MHz] / 256[8 bits]
    if( loop_count <= 0.0 ) {
        loop_count = 1.0;
        printf("WARN: loop_count was <= 0.0\n");
    }

    TCCR0 |= 0x01;
    TIMSK |= 0x01;
    sei();
    return lrint(loop_count);
}
//-----------------------------------------------------------------------------
