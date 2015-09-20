#include "graphics.h"


void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

void lcd_draw_term(term_t* term) {
  for(uint8_t y = 0; y < term->rows; i++) {
      for (uint8_t x = 0; x < (term_width_px / char_width); x++) {
        lcd_draw_char(x * char_width, (col + y) % term_rows, term->buffer[(col + y) % term_rows][x]);
      }
  }
}

void lcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	uint8_t dx, dy;
	int8_t err;
	int8_t ystep;

	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}

	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}


	dx = x1 - x0;
	dy = abs(y1 - y0);

	err = dx / 2;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			lcd_draw_point(y0, x0);
		} else {
			lcd_draw_point(x0, y0);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void lcd_draw_char(uint8_t x, uint8_t line, char c)
{
	uint8_t i;

	/* Only works for fonts < 8 bits in height */
  const uint8_t font_width = 5;
  const uint8_t font_length = 96;
	for ( i = 0; i < font_width; i++ ) {
    fb[x + (line * PCD8544_MAX_COLS)] = Font5x7[ (((c - 32) % font_length) * (font_width)) + i  ];
    x++;
	}
}

void lcd_draw_string(uint8_t x, uint8_t line, char *str) {
	while (*str) {
		lcd_draw_char(x, line, *str++);
		x += (5 + 1);
		if ((x + 5 + 1) >= 84) {
			x = 0; /* Ran out of this line */
			line++;
		}
		if (line >= (48/(7 + 1)))
			return; /* Ran out of space :( */
	}
}

void lcd_draw_point(uint8_t x, uint8_t y) {
  buffer.fb[x + (y/8) * PCD8544_MAX_COLS] |= ( 1 << (y%8));
}
