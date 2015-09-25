#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>

#include "lcd.h"
#include "buttons.h"
#include "buffer.h"
#include "sd.h"
#include "graphics.h"

#define RESET_VECTOR() ((void(const *)(void))0)()


__attribute__((section(".boot")))
void fill_page(uint8_t* buff) {

}

__attribute__((section(".boot")))
void boot_interactive() {
  DDRD = 0xff;
  DDRB = 0xff; // take care of PB2 for /CS
  for (int i = 10; i > 0; i--) {
    PORTD ^= 0x01;
    _delay_ms(50);
  }
  return;
}

__attribute__((section(".boot")))
int main(void)
{
  buttons_init();
  _delay_ms(200); // wait a while

  if(!buttons_isset(BTN_A)) {
    asm("ijmp" :: "z" (0x0));
  } else {
    boot_interactive();
  }

  // perform SD loader

  // wait for watchdog to time out and reset system
}
