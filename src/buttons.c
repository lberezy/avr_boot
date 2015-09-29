#include "buttons.h"

#include "led.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

static void _buttons_scan();


static volatile btn_state_t buttons;  // global button state

uint8_t buttons_isset(button_t button_mask) {
  return buttons.intRep & button_mask;
}

void buttons_init(void) {
  // set inputs
  BTN_INPUT_DDR &= !BTN_INPUT_MASK;
  BTN_DIR_DDR &= !BTN_DIR_MASK;
  // enable internal pull-up resistors
  BTN_INPUT_PORT |= BTN_INPUT_MASK;
  BTN_DIR_PORT |= BTN_DIR_MASK;

  // enable pin-change interrupt (INT0, PD2)
  //SREG |= ; // enable global interrupts
  MCUCR |= _BV(ISC00); // interrupt on changing level
  GICR |= _BV(INT0);  // enable INT0
  buttons.polling = 1; // allow polling
  sei();

}

ISR(INT0_vect) {
  _buttons_scan();
}

static void _buttons_scan() {
  // scan buttons
  buttons.up    = (BTN_DIR_PORTIN & BTN_UP_PIN);
  buttons.down  = (BTN_DIR_PORTIN & BTN_DOWN_PIN);
  buttons.left  = (BTN_DIR_PORTIN & BTN_LEFT_PIN);
  buttons.right = (BTN_DIR_PORTIN & BTN_RIGHT_PIN);
  buttons.a     = (BTN_DIR_PORTIN & BTN_A_PIN);
  buttons.b     = (BTN_DIR_PORTIN & BTN_B_PIN);
  // poll for more simultaneous presses if any were detected
  buttons.polling = !!(buttons.intRep);
}

void buttons_poll(void) {
  if(buttons.polling) {
    _buttons_scan();
  }
}
