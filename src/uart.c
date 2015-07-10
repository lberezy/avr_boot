#include "uart.h"


/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void) {
      UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
      UBRRL = BAUDRATE;                           // set baud rate
      UCSRB|= (1<<TXEN)|(1<<RXEN);                // enable receiver and transmitter
      UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
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
