#include "terminal.h"


static char tb[DISPLAY_HEIGHT / 8][DISPLAY_WIDTH / (5 + 1)];

void term_putchar(term_t* term, char c) {
  if (col > ((term_width_px - char_width)/ char_width)) {
    col = 0;
    row = (row + 1) % term_rows;
  }
  tb[row][col] = c;
  col++;
}
