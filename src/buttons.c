#include "buttons.h"

#include "led.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

static void _buttons_scan();


static volatile btn_state_t buttons;  // global button state

uint8_t buttons_isset(button_t button_mask) {
  return buttons & button_mask;
}

void buttons_init(void) {
  // set inputs
  BTN_INPUT_DDR &= ~BTN_INPUT_MASK;
  BTN_DIR_DDR &= ~BTN_DIR_MASK;
  // enable internal pull-up resistors
  BTN_INPUT_PORT |= BTN_INPUT_MASK;
  BTN_DIR_PORT |= BTN_DIR_MASK;

  // enable pin-change interrupt (INT0, PD2)
  //SREG |= ; // enable global interrupts
  MCUCR |= _BV(ISC00); // interrupt on changing level
  GICR |= _BV(INT0);  // enable INT0
  // allow polling
  buttons |= BTN_FLAG_POLLING;
  sei();

}

ISR(INT0_vect) {
  _buttons_scan();
}

inline static void _buttons_scan() {
  // perform fresh scan
  buttons = 0;
  // scan buttons
  buttons |= (BTN_DIR_MASK & ~BTN_DIR_PORTIN);
  buttons |= (BTN_INPUT_MASK & ~BTN_INPUT_PORTIN);
  // set polling flag if any button presses detected
  // remove polling flag if no button presses detected
  if (!!(buttons & BTN_ALL_MASK)) {
    buttons |= BTN_FLAG_POLLING;
  } else {
    buttons &= ~ BTN_FLAG_POLLING;
  }
}

void buttons_poll(void) {
  if(buttons & BTN_FLAG_POLLING) {
    _buttons_scan();
  }
}
