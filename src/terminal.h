#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdint.h"

#include "buffer.h"
#include "font.h"
typedef struct {
  uint8_t scroll_x;
  uint8_t rows;
  uint8_t width;
  uint8_t cursor_x;
  uint8_t cursor_y;
  char* buffer;
} terminal_t;


terminal_t term_init(uint8_t width, uint8_t height);

void term_putchar(terminal_t* term, char c);
void term_puts(terminal_t* term, const char* str);
void term_draw(terminal_t* term);
#endif
