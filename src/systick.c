#include "systick.h"

#include "HAL/board.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "led.h"
/* Initialise the system tick.
The system tick takes control of timer/counter0.
*/
void systick_init() {
  // set timer0 clock divisor
  TCCR0 |= (_BV(CS02) | _BV(CS00));
  // enable overflow interrupt
  TIMSK |= _BV(TOIE0);
  sei();
  global_tick = 0;
}

ISR(TIMER0_OVF_vect) {
  //BACKLIGHT_LED_TOGGLE();
  global_tick++;
}
