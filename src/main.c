#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "led.h"
#include "lcd.h"
#include "buttons.h"
#include "buffer.h"
#include "sd.h"
#include "graphics.h"
#include "systick.h"
#include "fram.h"

#include "terminal.h"

#include <avr/interrupt.h>
#include <util/atomic.h>


#define RESET_VECTOR() ((void(const *)(void))0)()


__attribute__((section(".boot")))
void fill_page(uint8_t* buff) {

}

__attribute__((section(".boot")))
void boot_interactive() {
  USER_LED_INIT();
  while(1) {
    USER_LED_TOGGLE();
    _delay_ms(100);
  }
}

__attribute__((section(".boot")))
int main(void)
{
  cli();
  GICR = 1 << IVCE;
  GICR = 1 << IVSEL;
  sei();
  DDRB |= _BV(PB4); // set CS to output
  // Initialise modules
  USER_LED_INIT();
  BACKLIGHT_LED_INIT();
  BACKLIGHT_LED_OFF();
  buttons_init();
  /* peripheral init functions have side effects - SPI config */
  lcd_init();
  fram_init();
  systick_init();


  terminal_t term;
  term.width = 8;
  term.rows = 5;
  term.cursor_x = 0;
  term.cursor_y = 0;
  term.buffer = calloc((term.rows) * (term.width / (FONT_GLYPH_WIDTH + 1)), sizeof(char));

  term_puts(&term, "test");
  term_draw(&term);
  lcd_fill();
  uint32_t curr_tick = global_tick;
  while(1) {
    if(global_tick > curr_tick + 2) {
      term_puts(&term, "0123456789");
      term_draw(&term);
      lcd_fill();
      lcd_clear_buffer();
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        curr_tick = global_tick;
      }
      buttons_poll();
      if(!!buttons_isset(BTN_B | BTN_A)) {
        USER_LED_ON();
      } else {
        USER_LED_OFF();
      }
      if(buttons_isset(BTN_UP)) {
        USER_LED_OFF();
      }
    }
  }



  /*if(!buttons_isset(BTN_A)) {
    while(1);
    //asm("ijmp" :: "z" (0x0));
  } else {
    boot_interactive();
  }*/
  // perform SD loader

  // wait for watchdog to time out and reset system
}
