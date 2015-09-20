#ifndef _UC1701_H
#define _UC1701_H

#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define _LCD_CONTROLLER UC1701
#endif

#define UC1701


#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT 64
#endif
