#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "HAL/board.h"

/* hardware abstractions */
#define BTN_DIR_MASK ( _BV(BTN_UP_PIN) |_BV(BTN_DOWN_PIN) | _BV(BTN_LEFT_PIN) | _BV(BTN_RIGHT_PIN))
#define BTN_INPUT_MASK (_BV(BTN_A_PIN) | _BV(BTN_B_PIN))



/* software-only representation - matches with below struct */
typedef enum {
  BTN_A,
  BTN_B,
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_RIGHT,
  _UNUSED,
  FLAG_POLLING
} button_t;

typedef union {
  struct  __attribute__ ((packed)) {
    uint8_t a : 1;
    uint8_t b : 1;
    uint8_t up : 1;
    uint8_t down : 1;
    uint8_t left : 1;
    uint8_t right : 1;
    uint8_t unused : 1;
    uint8_t polling : 1;
  };
  uint8_t intRep; /* integer representation of bit-field */
} btn_state_t;



uint8_t buttons_isset(button_t button);
void buttons_init(void);
void buttons_poll(void);
#endif
