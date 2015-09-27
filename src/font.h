#ifndef _FONT_H
#define _FONT_H

/* typedef struct {
  const char first_ascii;
  const uint8_t num_glyphs;
  const uint8_t width_px;
  const uint8_t height_px;
  const uint8_t font_data[];
} font_t; */
#include <stdint.h>
/* defines global "font" variable */
#include "fonts/font_5x7.h"
const uint8_t* font_data;

#endif
