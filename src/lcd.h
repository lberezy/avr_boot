#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "spi.h"
#include "HAL/board.h"
#include "buffer.h"

#define LCD_CONTRAST 16
/* standard interface that all LCD controllers must implement */
void lcd_init(void);
void lcd_fill(void);
void lcd_clear_buffer(void);
#endif
