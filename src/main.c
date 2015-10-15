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
#include "bootloader.h"
#include "terminal.h"

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdio.h>


#define RESET_VECTOR() ((void(const *)(void))0)()


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
  BACKLIGHT_LED_PWM_INIT();
  //BACKLIGHT_LED_ON();
  buttons_init();
  /* peripheral init functions have side effects - SPI config */
  lcd_init();
  fram_init();
  //systick_init();


  terminal_t term;
  term.width = 17;
  term.rows = 8;
  term.cursor_x = 0;
  term.cursor_y = 0;
  char buff[term.rows * term.width];
  term.buffer = buff;

  term_clear(&term);
  term_redirect_putchar(&term);

  fputs_P(PSTR("Bootloader"), stdout);
  fputs_P(PSTR("File: test.bin"), stdout);
  fputs_P(PSTR("Loading..."), stdout);
  term_draw(term_redirected);
  lcd_fill();
  lcd_clear_buffer();
  sd_init();

  flash_app("TEST.BIN");
  fputs_P(PSTR("Done"), stdout);
  term_draw(term_redirected);
  lcd_fill();
  lcd_clear_buffer();

  while(1) {
    if(buttons_isset(BTN_B | BTN_A)) {
      USER_LED_ON();
      OCR2++;
      //fputs_P(PSTR("blah"), stdout);
      //term_puts_P(&term, PSTR("abcd"));
    } else if (buttons_isset(BTN_UP)) {
      USER_LED_OFF();
    }
    if(buttons_isset(BTN_UP)) {
      USER_LED_OFF();
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
