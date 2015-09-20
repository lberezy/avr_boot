#ifndef _LCD_H
#define _LCD_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "buffer.h"
#include "spi.h"

/* select appropriate LCD controller */
#include "HAL/PCD8544.h"
//#include "HAL/UC1701.h"

/*#ifndef _LCD_CONTROLLER
#error No LCD controller selected.
#endif*/

void lcd_command(char c);
void lcd_data(char c);
void lcd_init(void);
void lcd_fill(void);
void set_led();


#endif
