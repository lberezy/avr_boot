#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdint.h"

#include "buffer.h"
#include "font.h"

#include <avr/pgmspace.h>

// todo: add function pointer to read and write characters to term (for FRAM)
typedef struct {
  uint8_t scroll_x;   // scroll windows top position (in rows)
  uint8_t rows;       // maximum number of character rows
  uint8_t width;      // maximum characters per row
  uint8_t view_rows;  // number of rows to render from scroll position
  uint8_t cursor_x;   // character cursor position in current row
  uint8_t cursor_y;   // current row of character cursor
  char* buffer;       // storage space for term buffer
} terminal_t;

terminal_t* term_redirected;

terminal_t term_init(uint8_t width, uint8_t height);

void term_putchar(terminal_t* term, char c);
void term_redirect_putchar(terminal_t* term);
void term_puts(terminal_t* term, const char* str);
void term_puts_P(terminal_t* term, PGM_P str);
void term_draw(terminal_t* term);
void term_set_cursor(terminal_t* term, uint8_t cur_x, uint8_t cur_y);
#endif
