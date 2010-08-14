#ifndef _UART_H_
#define _UART_H_

/*
 * Based on code from
 * http://www.nongnu.org/avr-libc/user-manual/group__stdiodemo.html
 */

/* Open UART on PB0, PB1 at ${BAUD} 8N1. Redirect to stdio & stdout. */
void initUart(void);

#endif //_UART_H_
