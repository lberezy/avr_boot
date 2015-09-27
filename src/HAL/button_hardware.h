#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#define BTN_INPUT_PORT PORTD
#define BTN_INPUT_PORTIN PIND
#define BTN_INPUT_DDR DDRD

#define BTN_DIR_PORT PORTB
#define BTN_DIR_PORTIN PINB
#define BTN_DIR_DDR DDRB


/* typesafe hardware pin mapping */
enum {
  BTN_A_PIN = 6,
  BTN_B_PIN = 5,
  BTN_UP_PIN = 1,
  BTN_DOWN_PIN = 2,
  BTN_LEFT_PIN = 0,
  BTN_RIGHT_PIN = 3,
} button_pin;

#endif
