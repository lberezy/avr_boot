#include "bootloader.h"

#include <stdint.h>

#include <avr/boot.h>
#include <util/atomic.h>
#include "buffer.h"
#include "pfatfs/pff.h"
#include "led.h"
#include <stdio.h>
#include "terminal.h"
#include "sd.h"

#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define LED_DELAY 10
void boot_program_page (uint32_t page, uint8_t *buf) {
  uint16_t i;
  uint8_t sreg;
  // Disable interrupts.
  sreg = SREG;
  cli();
  eeprom_busy_wait ();
  boot_page_erase (page);
  boot_spm_busy_wait (); // Wait until the memory is erased.
  for (i=0; i<SPM_PAGESIZE; i+=2)
  {
    // Set up little-endian word.
    uint16_t w = *buf++;
    w += (*buf++) << 8;
      boot_page_fill (page + i, w);
    }
  boot_page_write (page); // Store buffer in flash page.
  boot_spm_busy_wait(); // Wait until the memory is written.
  // Reenable RWW-section again. We need this if we want to jump back
  // to the application after bootloading.
  boot_rww_enable ();
  // Re-enable interrupts (if they were ever enabled).
  SREG = sreg;
}

void flash_app(char* path) {
  //ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    uint8_t pagebuffer[SPM_PAGESIZE];
    UINT bytes_read = 0;
    FRESULT result = pf_open(path);
    if(result != FR_OK) {
      return;
    }
    for(uint16_t addr = APP_START_ADDR; addr < APP_END_ADDR; addr += SPM_PAGESIZE) {
      for(uint8_t i = 0; i < SPM_PAGESIZE; i++) { // clear buffer
        pagebuffer[i] = 0xFF;
      }
      // read in page of app File
      pf_read(pagebuffer, SPM_PAGESIZE, &bytes_read);
      //putchar((char)pagebuffer[0]);

      if(bytes_read) {
        boot_program_page(addr, pagebuffer);
      }
      USER_LED_TOGGLE();
      _delay_ms(LED_DELAY);
  }
}
