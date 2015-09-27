#ifndef _FONT_5X7_H
#define _FONT_5X7_H

#include "../font.h"
#include <avr/pgmspace.h>
#include <stdint.h>

#define FONT_FIRST_ASCII  ' '   // first ASCII point
#define FONT_LAST_ASCII   '}'   // number of ASCII characters covered from point
#define FONT_GLYPH_WIDTH  5     // glyph width in px
#define FONT_GLYPH_HEIGHT 7     // glyph height in px
#endif
