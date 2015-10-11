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
#include <stdio.h>


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
  term.width = 17;
  term.rows = 8;
  term.cursor_x = 0;
  term.cursor_y = 0;
  char buff[term.rows * term.width];
  term.buffer = buff;

  term_clear(&term);
  char test_char = FONT_FIRST_ASCII;
  char test_result = test_char;
  uint8_t test_addr = 0;

  term_redirect_putchar(&term);
  //sd_init();
  uint32_t curr_tick = global_tick;
  while(1) {
    if(global_tick > curr_tick) {
      ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        fputs_P(PSTR("Test\n FRAM\n"), stdout);
        fputs_P(PSTR("Tx:"), stdout); putchar(test_char); putchar('\n');
        fram_write_byte(test_addr, test_char);
        fputs_P(PSTR("Rx:"), stdout); putchar(test_result = (char)fram_read_byte(test_addr++)); putchar('\n');
        if (test_char == FONT_LAST_ASCII) {
          test_char = FONT_FIRST_ASCII;
        }

        term_draw(term_redirected);
        term_set_cursor(term_redirected, 0, 0);
        term_clear(term_redirected);
        lcd_fill();
        lcd_clear_buffer();

        curr_tick = global_tick;

        buttons_poll();
        if(!!buttons_isset(BTN_B | BTN_A) || (test_result == test_char)) {
          USER_LED_ON();
          fputs_P(PSTR("blah"), stdout);
          //term_puts_P(&term, PSTR("abcd"));
        } else {
          USER_LED_OFF();
        }
        if(buttons_isset(BTN_UP)) {
          USER_LED_OFF();
        }
        test_char++;
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
