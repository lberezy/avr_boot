#include "uart.h"


/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

#if USE_2X
    UCSRA |= _BV(U2X);
#else
    UCSRA &= ~(_BV(U2X));
#endif

    UCSRC = _BV(UCSZ1) | _BV(UCSZ0) | _BV(URSEL); /* 8-bit data */
    UCSRB = _BV(RXEN) | _BV(TXEN);   /* Enable RX and TX */
}

void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
}

char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSRA, RXC);
    return UDR;
}

void redirect_io(void) {
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  stdout = &uart_output;
  stdin  = &uart_input;
}
