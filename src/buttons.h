#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "HAL/board.h"

/* hardware abstractions */
#define BTN_DIR_MASK    (BTN_UP_PIN | BTN_DOWN_PIN | BTN_LEFT_PIN | BTN_RIGHT_PIN)
#define BTN_INPUT_MASK  (BTN_A_PIN | BTN_B_PIN)


#define BTN_FLAG_BITPOS 7
/* software-only representation - matches with hardware*/
typedef enum {
  BTN_A             = BTN_A_PIN,
  BTN_B             = BTN_B_PIN,
  BTN_UP            = BTN_UP_PIN,
  BTN_DOWN          = BTN_UP_PIN,
  BTN_LEFT          = BTN_LEFT_PIN,
  BTN_RIGHT         = BTN_RIGHT_PIN,
  BTN_FLAG_POLLING  = _BV(BTN_FLAG_BITPOS)
} button_t;

#define BTN_ALL_MASK (BTN_A | BTN_B | BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)
typedef uint8_t btn_state_t;


uint8_t buttons_isset(button_t button_mask);
void buttons_init(void);
void buttons_poll(void);
#endif
