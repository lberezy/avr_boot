#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "spi.h"
#include "HAL/lcd_hardware.h"
#include "buffer.h"
/*#ifndef _LCD_CONTROLLER
#error No LCD controller selected.`2`
#endif*/

void lcd_command(char c);
void lcd_data(char c);
void lcd_init(void);
void lcd_fill(void);
void set_led();


#endif
