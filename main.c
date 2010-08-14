#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <math.h>
#include "uart.h"

/* Max value = 62500 */
#define LOOP_HZ 100

/* Main Loop Timer Stuff */
volatile int count = 0;
ISR (TIMER0_OVF_vect) {--count;}
/*
 * Run Timer 0 (8 bit) at F_CPU (no prescale).
 * Input: desired loop frequency [Hz]
 * Output: counter value for top of while loop
 */
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

int main(void)
{
    initUart();
    char name [80];
    //printf("What is your name?\n");
    //scanf("%s", name);  // this is blocking
    //printf("Hey %s--it looks like the UART is working!\n", name);
    long loop_count = timerInit(LOOP_HZ);

    /* main loop */
    while(1) {
        count = loop_count;

        PORTC ^= _BV(5);

        /* sleep until time expires */
        if( count <= 0 ){printf("WARN:\t loop running slowly\n");}
        while(count > 0) {sleep_mode();}
    }
    return(0);
}

