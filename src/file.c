#include "file.h"

#include "terminal.h"

uint8_t dir_list(char* path) {
  return 0;
}


FRESULT sd_scan_files (char* path) {
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int j;
    res = pf_opendir(&dir, path);
    if (res == FR_OK) {

        for (;;) {
            res = pf_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            //lcd_putchar((fno.fattrib & AM_DIR) ? 'D' : 'F');
            //lcd_putchar(' ');
            j = 0;
            while ((path[j++]) != '\0') {
              //lcd_putchar(path[j]);
            }
            //lcd_putchar('/');
            //gfx_draw_string(1,1,fno.fname);
            while ((fno.fname[j++]) != '\0') {
            //  lcd_putchar(fno.fname[j]);
            }
            //lcd_fill();
            //putchar('\n');
            //printf("[%c]%s/%s\n", (fno.fattrib & AM_DIR) ? 'D' : 'F', path, fno.fname);
        }
    }
    return res;
}
