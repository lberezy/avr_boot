#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//#include "lcd.h"
#include "font.h"
#include "buffer.h"
/*FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
stdout = &uart_output;
stdin  = &uart_input;*/
#define TERM_WIDTH_PX   DISPLAY_WIDTH
#define TERM_HEIGHT_PX  DISPLAY_HEIGHT
#define TERM_ROWS       (TERM_HEIGHT_PX / FONT_HEIGHT)
#define TERM_COLS       (TERM_WIDTH_PX /  (FONT_WIDTH + 1))



void lcd_draw_point(uint8_t x, uint8_t y);
void lcd_draw_char(uint8_t x, uint8_t line, char c);
void lcd_draw_string(uint8_t x, uint8_t line, char *str);
void lcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void lcd_putchar(char c);
void lcd_draw_term(void);

#endif
