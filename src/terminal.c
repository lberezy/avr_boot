#include "terminal.h"

#include "graphics.h"

#include <stdio.h>

int term_putchar_wrapper(char c, FILE* stream);

void term_redirect_putchar(terminal_t* term) {
  term_redirected = term;
  fdev_setup_stream(stdout, term_putchar_wrapper, NULL, _FDEV_SETUP_WRITE);
  //stdout = &mystdout;
}

int term_putchar_wrapper(char c, FILE* stream) {
  term_putchar(term_redirected, c);
  return 0;
}


void term_putchar(terminal_t* term, char c) {
  if (term->cursor_x > term->width || c == '\n') {
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

void term_puts_P(terminal_t* term, PGM_P str) {
  char c;
  while((c = pgm_read_byte(str++)) != '\0') {
    term_putchar(term, c);
  }
}

void term_draw(terminal_t* term) {
  // todo: handle \n
  uint8_t max_rows = term->rows;
  uint8_t cursor_current_col = term->cursor_y;
  for(uint8_t y = 0; y < max_rows;  y++) {
    uint8_t scrolling_row = ((( cursor_current_col - y ) % max_rows) + max_rows) % max_rows;
    for(uint8_t x = 0; x < term->width; x++) {
      gfx_draw_char(x * FONT_GLYPH_WIDTH, scrolling_row, term->buffer[(scrolling_row * (term->width)) + x ]);
    }
  }
}
