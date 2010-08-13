//#include <ctypes.h>
//#include "defines.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600

#include <stdio.h>
#include <util/setbaud.h>
//#include <util/delay.h>
//#include "avrlibdefs.h"
//#include "avrlibtypes.h"
//#include "adc.h"

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
    return 0;
}

int main(void)
{
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    UCSRA &= ~(1 << U2X);
    UCSRB = _BV(TXEN) | _BV(RXEN);

    stdout = &mystdout;
    while(1)
        printf("Hello, World!\n");
    
    return(0);
}

