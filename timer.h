#ifndef _TIMER_H_
#define _TIMER_H_

// global decrementing counter for main loop speed
volatile int count;
/*
 * Run Timer 0 (8 bit) at F_CPU (no prescale).
 * Input: desired loop frequency [Hz]
 * Output: counter value for top of while loop
 */
long timerInit(double loop_freq);

#endif //_TIMER_H_
