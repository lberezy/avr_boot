#include "terminal.h"

#include "graphics.h"


void term_putchar(terminal_t* term, char c) {
  // todo: handle \n
  if (term->cursor_x > term->width) {
    term->cursor_x = 0;
    term->cursor_y = (term->cursor_y + 1) % term->width;
  }
  (term->buffer)[term->rows * term->cursor_y + term->cursor_x] = c;

  (term->cursor_x)++;
}

void term_puts(terminal_t* term, const char* str) {
  while(*str) {
    term_putchar(term, *str++);
  }
}

void term_draw(terminal_t* term) {
  // todo: handle \n
  uint8_t max_rows = term->rows;
  uint8_t cursor_current_col = term->cursor_y;
  for(uint8_t y = 0; y < term->rows; y++) {
    for(uint8_t x = 0; x < term->width; x++) {
      gfx_draw_char(x * FONT_GLYPH_WIDTH, y, term->buffer[(y * (term->width)) + x ]);
    }
    //gfx_draw_string(0,y,&(term->buffer)[((( cursor_current_col - y ) % max_rows) + max_rows) % max_rows]);
    //gfx_draw_string(0,y, term->buffer + (y * (term->width)));
  }
}
