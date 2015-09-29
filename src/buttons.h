#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "HAL/board.h"

/* hardware abstractions */
#define BTN_DIR_MASK    (BTN_UP_PIN | BTN_DOWN_PIN | BTN_LEFT_PIN | BTN_RIGHT_PIN)
#define BTN_INPUT_MASK  (BTN_A_PIN | BTN_B_PIN)



/* software-only representation - matches with below struct */
typedef enum {
  BTN_A         = _BV(0),
  BTN_B         = _BV(1),
  BTN_UP        = _BV(2),
  BTN_DOWN      = _BV(3),
  BTN_LEFT      = _BV(4),
  BTN_RIGHT     = _BV(5),
  _UNUSED       = _BV(6),
  FLAG_POLLING  = _BV(7)
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



uint8_t buttons_isset(button_t button_mask);
void buttons_init(void);
void buttons_poll(void);
#endif
