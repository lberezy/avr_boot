/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <stdint.h>
#include "pfatfs/pff.h"
//#include <avr/signature.h>
#include <util/delay.h>
#include "uart.h"
#include "pfatfs/pff.h"
#include "pfatfs/diskio.h"
#include "lcd.h"
//#include <string.h>
//#include <stdlib.h>


/*__attribute__((section(".boot")))
FRESULT scan_files (char* path)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int i, j;
    char c;


    res = pf_opendir(&dir, path);
    if (res == FR_OK) {
        i = strlen(path);
        for (;;) {
            res = pf_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            putchar((fno.fattrib & AM_DIR) ? 'D' : 'F');
            putchar(' ');
            j = 0;
            while ((path[j++]) != NULL) {
              putchar(path[j]);
            }
            putchar('/');
            while ((fno.fname[j++]) != NULL) {
              putchar(fno.fname[j]);
            }
            putchar('\n');
            //printf("[%c]%s/%s\n", (fno.fattrib & AM_DIR) ? 'D' : 'F', path, fno.fname);
        }
    }
    return res;
} */

__attribute__((section(".boot")))
void fill_page() {

}

#define RESET_VECTOR() ((void(const *)(void))0)()
FATFS* fs;
DSTATUS status;
FRESULT result;
volatile uint8_t buff[512];


__attribute__((section(".boot"), used))
int main(void)
{
  DDRD = 0xff;
  for (int i = 10; i > 0; i--) {
    PORTD ^= 0x01;
    _delay_ms(50);
  }

  spi_init(0, 1, 3, 0, 1);
  lcd_init();
  lcd_draw_string(1,1, "LCD Initialised.");
  lcd_fill();
  lcd_draw_string(1,1, "Initialising SD card");
  lcd_fill();
  status = disk_initialize();
  switch(status) {
    case STA_NODISK:
      lcd_draw_string(1,1, "No disk");
      break;
    case STA_NOINIT:
      lcd_draw_string(1,1, "Not initialised");
      break;
    default:
      lcd_draw_string(1,1, "Initialisation failed");
      break;
  }
  lcd_fill();



  // jump to application
  //asm("ijmp" :: "z" (0x0));
  /*FATFS fs;
  DSTATUS status;
  FRESULT result;
  volatile char buff[512];


  uart_init();
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  stdout = &uart_output;
  stdin  = &uart_input;
  puts("Test");
  status = disk_initialize();
  if (status == NULL) {
    //puts("SD card initialialised correctly.");
  }
  result = pf_mount(&fs);
  if (result == NULL) {
    //puts("Mounted SD card successfully.");
  }
  int br_total = 0;
  int br = 0;
  //puts("Scanning files");
  scan_files("");
  //puts("Finished scanning files");
  //puts("opening test.txt");

  result = pf_open("TES.TXT");
  //puts("opened test.txt");
  int total_b = 0;
  do {
    pf_read(NULL, 512, &br);
    //printf("read %d bytes\n", br);
    int i = br;
    total_b += br;
    while (i > 0) {
      putchar(buff[i--]);
    }
  } while (br > 0);
  putchar('\n');
  //printf("Read total: %d\n", total_b);
  return 0;
  /*DDRD = 0xff;
  //disk_initialize();

  return 0;*/
  //set_led();


}
