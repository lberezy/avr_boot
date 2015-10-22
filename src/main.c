#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

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
#define RESTORE_IN_VECT() do {cli(); GICR = }
#define PROTECT_CS()   (DDRB |= _BV(PB4)) // set CS to output

__attribute__((section(".boot")))
int main(void)
{
  MOVE_INT_VECT();
  PROTECT_CS();
  // Initialise modules
  led_init();
  buttons_init();
  /* peripheral init functions have side effects - SPI config */
  lcd_init();
  fram_init();
  //systick_init();

  terminal_t term;
  // local terminal configuration
  term.width = 17;
  term.rows = 8;
  term.cursor_x = 0;
  term.cursor_y = 0;

  char buff[term.rows * term.width];
  term.buffer = buff;
  lcd_clear_buffer(); // clear persistance in framebuffer
  lcd_fill();         // write clear framebuffer to lcd
  term_clear(&term);    // clear text terminal buffer
  term_redirect_putchar(&term); // connect terminal to stdout
  led_user_on();  // enable LED when in bootloader mode
  // print user info to LCD
  puts_P(PSTR("Bootloader"));
  puts_P(PSTR("A: Flash"));
  puts_P(PSTR("B: Boot"));
  DRAW_LOCAL_TERM();
  // take user selection
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
  // browse for file

  DIR dir;
  FILINFO fno;
  puts_P(PSTR("Select file:"));
  puts_P(PSTR("Down: Scroll"));
  puts_P(PSTR("A: Select"));
  DRAW_LOCAL_TERM();

do_browse: ;
// open root directory
  if(pf_opendir(&dir, "/") != FR_OK) {
    goto error;
  }
  do {
    buttons_poll();
    if(buttons_isset(BTN_DOWN)) {
      //puts_P(PSTR("Search"));
      //DRAW_LOCAL_TERM();
    // print file name
      while(pf_readdir(&dir, &fno) == FR_OK) {
        // if end of all files, start browsing again
        if(fno.fname[0] == 0) {
          puts_P(PSTR("End of list."));
          DRAW_LOCAL_TERM();
          goto do_browse;
        }
        // make sure file ends in .BIN
        if(strstr(fno.fname, ".BIN") != NULL) {
          puts(fno.fname);
          DRAW_LOCAL_TERM();
          _delay_ms(200); // allow user time to scroll
          break;
        }
      }
    }
    if(buttons_isset(BTN_A)) {
      // file selected to write to flash
      goto do_flash_write;
    }
  } while(1);

do_flash_write:
  // open file to flash
  if (pf_open(fno.fname) != FR_OK) {
    goto error;
  }
  // flash application
  puts_P(PSTR("Flashing:"));
  puts(fno.fname);
  DRAW_LOCAL_TERM();
  flash_app(fno.fname);

do_boot:
  puts_P(PSTR("Booting!"));
  DRAW_LOCAL_TERM();
  led_user_off(); // turn off led to indicate end of bootloader
  _delay_ms(500); // wait 500 ms
  cli(); // disable interrupts
  //((void(*)(void))0)(); // boot application
  asm("ijmp" :: "z" (0x0));

// program jumps here on error and waits
error:
  puts_P(PSTR("BOOT ERROR"));
  while(1) {
    led_user_toggle();
    DRAW_LOCAL_TERM();
  }
}
