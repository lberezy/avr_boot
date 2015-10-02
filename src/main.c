#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>

#include "led.h"
#include "lcd.h"
#include "buttons.h"
#include "buffer.h"
#include "sd.h"
#include "graphics.h"
#include "systick.h"
#include <avr/interrupt.h>

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
  USER_LED_INIT();
  BACKLIGHT_LED_INIT();
  buttons_init();
  //systick_init();
  lcd_init();
  while(1) {
    lcd_draw_line(32,32,64,60);
    lcd_fill();
  }
  /*uint32_t curr_tick = global_tick;
  while(1) {
    buttons_poll();

  }*/
  /*uint32_t curr_tick = global_tick;
  while(1) {
    if(global_tick > curr_tick + 2) {
      lcd_draw_line(8,8,32,32);
      lcd_fill();
      curr_tick = global_tick;
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
*/
  //}
  /*if(!buttons_isset(BTN_A)) {
    while(1);
    //asm("ijmp" :: "z" (0x0));
  } else {
    boot_interactive();
  }*/


  // perform SD loader

  // wait for watchdog to time out and reset system
}
