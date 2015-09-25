#ifndef _UC1701_H
#define _UC1701_H

#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define _LCD_CONTROLLER UC1701
#endif

#define UC1701

/* control registers */

#define UC1701_SL
#define UC1701_STATUS_BZ _BV(7)
#define UC1701_STATUS_MX _BV(6)
#define UC1701_STATUS_DE _BV(5)
#define UC1701_STATUS_RST _BV(4)

#define UC1701_SET_COL_ADDR_LSB   (0b00000000)
#define UC1701_SET_COL_ADDR_MSB   (0b00010000)
#define UC1701_SET_COL_MASK       (0b00001111)

#define UC1701_SET_POWER_CTRL     (0b00101000)
#define UC1701_SET_POWER_MASK     (0b00000111)

#define UC1701_SET_SCROLL_LINE    (0b01000000)
#define UC1701_SET_SCROLL_MASK    (0b00111111)

#define UC1701_SET_PAGE_ADDR      (0b10110000)
#define UV1701_SET_PAGE_MASK      (0b00001111)

#define UC1701_SET_VLCD_RATIO     (0b00100000)
#define UC1701_SET_VLCD_MASK      (0b00000111)

/* two byte command */
/* default value: 32 */
#define UC1701_SET_EL_VOL_1       (0b10000001)
#define UC1701_SET_EL_VOL_2       (0b00000000)
#define UC1701_SET_EL_VOL_MASK    (0b00111111)

#define UC1701_SET_ALL_ON         (0b10100100)
#define UC1701_SET_ALL_MASK       (0b00000001)

#define UC1701_SET_INV_DISP       (0b10100110)
#define UC1701_SET_INV_MASK       (0b00000001)

#define UC1701_SET_DISP_EN        (0b10101110)
#define UC1701_SET_DISP_MASK      (0b00000001)

#define UC1701_SET_SREG_DIR       (0b10100000)
#define UC1701_SET_SREG_MASK      (0b00000001)

#define UC1701_SET_COM_DIR        (0b11000000)
#define UC1701_SET_COM_MASK       (0b00001000)

#define UC1701_SYS_RESET          (0b11100010)

#define UC1701_NOP                (0b11100011)

/* varies according to duty */
/*
Default: 0
DUTY | BR = 0 | BR = 1
----------------------
1/65 |   1/9  |  1/7
1/49 |   1/8  |  1/6
1/33 |   1/6  |  1/5
1/55 |   1/8  |  1/6
*/
#define UC1701_SET_BIAS           (0b10100010)
#define UC1701_SET_BIAS_MASK      (0b00000001)

#define UC1701_SET_CUR_MODE       (0b11100000)
#define UC1701_RESE_CUR_MODE      (0b11101110)

#define UC1701_SET_STAT_IND_OFF   (0b10101100)

/* two byte command, 2nd byte is don't-care */
#define UC1701_SET_STAT_IND_OFF   (0b10101101)

#define UC1701_SET_BOOST_1        (0b11111000)
#define UC1701_SET_BOOST_2        (0b00000000)

/* compound command */
#define UC1701_SET_POWER_SAVE     (0b00000000)


#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT 64
#endif
