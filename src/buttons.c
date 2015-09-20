#include "buttons.h"


static void _buttons_scan();


btn_state_t buttons;  // global button state

uint8_t buttons_isset(button_t button) {
  return buttons.intRep & _BV(button);
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
}

ISR(INT0_vect) {
  _buttons_scan();
}

static void _buttons_scan() {
  // scan buttons
  buttons.up =    ((BTN_DIR_PORTIN >> BTN_UP_PIN) & 1);
  buttons.down =  ((BTN_DIR_PORTIN >> BTN_DOWN_PIN) & 1);
  buttons.left =  ((BTN_DIR_PORTIN >> BTN_LEFT_PIN) & 1);
  buttons.right = ((BTN_DIR_PORTIN >> BTN_RIGHT_PIN) & 1);
  buttons.a =     ((BTN_DIR_PORTIN >> BTN_A_PIN) & 1);
  buttons.b =     ((BTN_DIR_PORTIN >> BTN_B_PIN) & 1);
  // poll for more simultaneous presses if any were detected
  buttons.polling = !!(buttons.intRep);
}

uint8_t buttons_poll(void) {

  buttons.polling = false;
  return 0;
}
