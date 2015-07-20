#ifndef _uart_h
#define _uart_h

#ifndef BAUD
#define BAUD 9600
#endif

#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#include <avr/io.h>
#include <util/setbaud.h>
#include <stdio.h>

void uart_init(void)
__attribute__((section(".library"), used));
void uart_putchar(char c, FILE *stream)
__attribute__((section(".library"), used));
char uart_getchar(FILE *stream)
__attribute__((section(".library"), used));

void redirect_io(void)
__attribute__((section(".library"), used));

#endif
