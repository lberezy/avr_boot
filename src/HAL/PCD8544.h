#ifndef PCD8544_H
#define PCD8544_H


/*#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define _LCD_CONTROLLER PCD8544
#endif*/

#define PCD8544

#define PCD8544_NOP 0
#define PCD8544_FUNCTION_SET          (1<<5)
#define PCD8544_POWER_DOWN            (1<<2)
#define PCD8544_HORIZONTAL_ADDRESSING 0
#define PCD8544_VERTICAL_ADDRESSING   (1<<1)
#define PCD8544_EXTENDED_INSTRUCTION  (1<<0)
/**@}*/

/**
 * \name Basic instruction set (H=0)
 * @{
 */
#define PCD8544_DISPLAY_CONTROL  (1<<3)
#define PCD8544_DISPLAY_BLANK    0x0
#define PCD8544_DISPLAY_NORMAL   (1<<2)
#define PCD8544_DISPLAY_ALL_ON   (1<<0)
#define PCD8544_DISPLAY_INVERTED (1<<2|1<<0)
#define PCD8544_SET_Y_ADDRESS       0x40
#define PCD8544_SET_X_ADDRESS       0x80
/**@}*/

/**
 * \name Extended instruction set (H=1)
 * @{
 */
#define PCD8544_SET_TEMP (1<<2)
#define PCD8544_TEMPCO_0 0b00
#define PCD8544_TEMPCO_1 0b01
#define PCD8544_TEMPCO_2 0b10
#define PCD8544_TEMPCO_3 0b11

/** \todo Check if these instructions are from this group */
#define PCD8544_SET_BIAS (1<<4)
#define PCD8544_SET_VOP  (1<<7)
/**@}*/

#define PCD8544_MAX_BANKS 6
#define PCD8544_MAX_COLS  84

#define DISPLAY_WIDTH PCD8544_MAX_COLS
#define DISPLAY_HEIGHT (PCD8544_MAX_BANKS * 8)

#endif
