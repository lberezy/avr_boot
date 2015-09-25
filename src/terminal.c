#include "terminal.h"

static char tb[DISPLAY_HEIGHT / 8][DISPLAY_WIDTH / (5 + 1)];

void term_putchar(terminal_t* term, char c) {
  // todo: handle \n
  if (term->cursor_x > term->rows) {
    term->cursor_x = 0;
    term->cursor_y = (term->cursor_y + 1) % term->cols;
  }
  (term->buffer)[term->rows * term->cursor_y + term->cursor_x] = c;
  //tb[row][col] = c;
  //col++;
  (term->cursor_x)++;
}
