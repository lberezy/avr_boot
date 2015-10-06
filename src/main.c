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

  uint32_t curr_tick = global_tick;
  char test_char = FONT_FIRST_ASCII;
  uint8_t fram_result;
  uint8_t test_addr = 0;
  while(1) {
    if(global_tick > curr_tick + 2) {
      gfx_draw_string(test_addr % 3,7,"((VIBRATE))");
      gfx_draw_string(0,6,"(0v0')");

      gfx_draw_string(0,0,"Test FRAM");
      gfx_draw_char(0,1,test_char);
      fram_write_byte(test_addr, test_char);
      fram_result = fram_read_byte(test_addr);
      gfx_draw_char(0,2, (char)fram_result);
      gfx_draw_string(0,4, ((char)fram_result == test_char) ? "PASS" : "FAIL");
      test_char++;
      test_addr++;
      if (test_char > FONT_LAST_ASCII) {
        test_char =  FONT_FIRST_ASCII;
        test_addr = 0;
      }
      lcd_fill();
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
