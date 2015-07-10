/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <stdint.h>
#include "pfatfs/pff.h"
#include <avr/signature.h>
#include <util/delay.h>
#include "uart.h"
#include "pfatfs/pff.h"
#include "pfatfs/diskio.h"


int main(void)
{
  void uart_init(void);
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  stdout = &uart_output;
  stdin  = &uart_input;

  DDRD = 0b11111100;
  DSTATUS status = STA_NOINIT;
  status = disk_initialize();
  char c = NULL;
  c = (status & STA_NOINIT) ? 'n' : 'y';
  while(1) {
    PORTD ^= 0b11111100;
    puts("test");
    _delay_ms(500);
    uart_putchar(c, NULL);
    uart_putchar('g', NULL);
  }

  return 0;
}
