#include "terminal.h"

#include "graphics.h"

#include <stdio.h>

static inline int term_putchar_wrapper(char c, FILE* stream);

void term_redirect_putchar(terminal_t* term) {
  term_redirected = term;
  fdev_setup_stream(stdout, term_putchar_wrapper, NULL, _FDEV_SETUP_WRITE);
  //stdout = &mystdout;
}

static inline int term_putchar_wrapper(char c, FILE* stream) {
  term_putchar(term_redirected, c);
  return 0;
}


void term_putchar(terminal_t* term, char c) {
  // handle explicit new line early
  if (((term->cursor_x) >= term->width) || c == '\n') {
    term->cursor_y = (term->cursor_y + 1) % term->rows;
    term->cursor_x = 0;
    if(term->cursor_x == 0) {
      for(uint8_t x = 0; x < term->width; x++) {
        (term->buffer)[(term->width * term->cursor_y) + x] = ' ';
      }
    }
    if (c == '\n') {
      return;
    }
  }
  // blank out new line


  // check if character in font
  if (c > FONT_LAST_ASCII || c < FONT_FIRST_ASCII) {
    c = '?';
  }
  // write character
  (term->buffer)[(term->width * term->cursor_y) + term->cursor_x] = c;
  // adjust cursor position
  (term->cursor_x)++;
  ///if ((term->cursor_x) > term->width) {
  //  term->cursor_x = 0;
  //  term->cursor_y = (term->cursor_y + 1) % term->rows;
  //}
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
    //uint8_t scrolling_row = ((( cursor_current_col - y ) % max_rows) + max_rows) % max_rows;
    //uint8_t scrolling_row = ((( cursor_current_col + y ) % max_rows) + max_rows) % max_rows;
    uint8_t scrolling_row = ( cursor_current_col + y  + 1) % (max_rows);

    for(uint8_t x = 0; x < term->width; x++) {
      gfx_draw_char(x * FONT_GLYPH_WIDTH, y, term->buffer[(scrolling_row * (term->width)) + x ]);
      //gfx_draw_char(x*FONT_GLYPH_WIDTH, y, term->buffer[(y * term->width) + x]);
    }
  }
}

void term_set_cursor(terminal_t* term, uint8_t cur_x, uint8_t cur_y) {
  term->cursor_y = cur_y;
  term->cursor_x = cur_x;
}

void term_clear(terminal_t* term) {
  /*uint8_t max_rows = term->rows;
  for(uint8_t y = 0; y < max_rows; y++) {
    for(uint8_t x = 0; x < term->width; x++) {
      (term->buffer)[(y * max_rows) + x] = ' ';
    }
  }*/
  for (uint8_t i = 0; i < (term->rows * term->width); i++) {
    (term->buffer)[i] = ' ';
  }
}
