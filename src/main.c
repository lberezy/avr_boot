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
#include <string.h>



/*FRESULT scan_files (char* path)
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
}*/

__attribute__((section(".boot"), used))
int main(void)
{
  /*FATFS fs;
  DSTATUS status;
  FRESULT result;
  char buff[512];


  uart_init();
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  stdout = &uart_output;
  stdin  = &uart_input;

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
  return 0;*/
  DDRD = 0xff;
  //disk_initialize();
  while(1) {
    PORTD ^= 0xff;
    _delay_ms(50);
  }
  return 0;
}
