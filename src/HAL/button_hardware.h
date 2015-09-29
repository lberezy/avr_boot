#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#define BTN_INPUT_PORT PORTD
#define BTN_INPUT_PORTIN PIND
#define BTN_INPUT_DDR DDRD

#define BTN_DIR_PORT PORTB
#define BTN_DIR_PORTIN PINB
#define BTN_DIR_DDR DDRB

#include <avr/io.h>

/* typesafe hardware pin mapping */
enum {
  BTN_A_PIN     = _BV(6),
  BTN_B_PIN     = _BV(5),
  BTN_UP_PIN    = _BV(1),
  BTN_DOWN_PIN  = _BV(2),
  BTN_LEFT_PIN  = _BV(0),
  BTN_RIGHT_PIN = _BV(3),
} button_pin;

#endif
