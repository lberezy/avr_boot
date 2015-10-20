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
#include "config.h"

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdio.h>

#define DRAW_LOCAL_TERM() do{  term_draw(term_redirected);lcd_fill();lcd_clear_buffer();} while(0)
#define MOVE_INT_VECT() do {  cli(); GICR = _BV(IVCE); GICR = _BV(IVSEL); sei();} while(0)

__attribute__((section(".boot")))
int main(void)
{
  MOVE_INT_VECT();
  DDRB |= _BV(PB4); // set CS to output
  // Initialise modules
  led_init();
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

  puts_P(PSTR("Bootloader"));
  puts_P(PSTR("A: Flash"));
  puts_P(PSTR("B: Boot"));
  DRAW_LOCAL_TERM();
  do {
    buttons_poll();
    if (buttons_isset(BTN_A)) {
      goto do_flash;
    }
    if(buttons_isset(BTN_B)) {
      goto do_boot;
    }
  } while(1);

do_flash:
  // init SD card
  if(sd_init() != SD_INIT_SUCCESS) {
    goto error;
  }
  // open app file to flash
  if (pf_open(APP_FILENAME) != FR_OK) {
    goto error;
  }
  // flash application
  puts_P(PSTR("Flashing:"));
  puts_P(PSTR(APP_FILENAME));
  DRAW_LOCAL_TERM();
  flash_app(APP_FILENAME);

do_boot:
  puts_P(PSTR("Booting!"));
  DRAW_LOCAL_TERM();
  _delay_ms(500);
  cli(); // disable interrupts
  //((void(*)(void))0)(); // boot application
  asm("ijmp" :: "z" (0x0));

error:
  puts_P(PSTR("BOOT ERROR"));
  while(1) {
    DRAW_LOCAL_TERM();
  }
}
