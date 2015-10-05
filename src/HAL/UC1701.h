#ifndef UC1701_H
#define UC1701_H

#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define LCD_CONTROLLER UC1701
#endif

/* control registers */

#define UC1701_SL
#define UC1701_STATUS_BZ            _BV(7)
#define UC1701_STATUS_MX            _BV(6)
#define UC1701_STATUS_DE            _BV(5)
#define UC1701_STATUS_RST           _BV(4)

#define UC1701_SET_COL_ADDR_LSB     (0b00000000)
#define UC1701_SET_COL_ADDR_MSB     (0b00010000)
#define UC1701_SET_COL_MASK         (0b00001111)

#define UC1701_SET_POWER_CTRL       (0b00101000)
#define UC1701_SET_POWER_BOOST_ON   (0b00000001)
#define UC1701_SET_POWER_BOOST_OFF  (0b00000000)
#define UC1701_SET_POWER_REG_ON     (0b00000010)
#define UC1701_SET_POWER_REG_OFF    (0b00000000)
#define UC1701_SET_POWER_FOLL_ON    (0b00000100)
#define UC1701_SET_POWER_FOLL_OFF   (0b00000000)

#define UC1701_SET_SCROLL_LINE      (0b01000000)
#define UC1701_SET_SCROLL_MASK      (0b00111111)

#define UC1701_SET_PAGE_ADDR        (0b10110000)
#define UV1701_SET_PAGE_MASK        (0b00001111)

#define UC1701_SET_VLCD_RATIO       (0b00100000)
#define UC1701_SET_VLCD_DEFAULT     (0b00000111)
#define UC1701_SET_VLCD_MASK        (0b00000111)

/* two byte command */
/* default value: 32 */
#define UC1701_SET_EL_VOL_1         (0b10000001)
#define UC1701_SET_EL_VOL_2         (0b00000000)
#define UC1701_SET_EL_VOL_MASK      (0b00111111)

#define UC1701_SET_ALL_PX           (0b10100100)
#define UC1701_SET_ALL_ON           (0b00000001)
#define UC1701_SET_ALL_OFF          (0b00000000)

#define UC1701_SET_INV_DISP         (0b10100110)
#define UC1701_SET_INV_DISP_ON      (0b00000001)
#define UC1701_SET_INV_DISP_OFF     (0b00000000)

#define UC1701_SET_DISP_EN          (0b10101110)
#define UC1701_SET_DISP_EN_ON       (0b00000001)
#define UC1701_SET_DISP_EN_OFF      (0b00000000)

#define UC1701_SET_SEG_DIR          (0b10100000)
#define UC1701_SET_SEG_DIR_NORM     (0b00000000)
#define UC1701_SET_SEG_DIR_MIRROR   (0b00000001)

#define UC1701_SET_COM_DIR          (0b11000000)
#define UC1701_SET_COM_DIR_NORM     (0b00000000)
#define UC1701_SET_COM_DIR_MIRROR   (0b00001000)

#define UC1701_SYS_RESET            (0b11100010)

/* varies according to duty */
/*
Default: 0
DUTY | BR = 0 | BR = 1
----------------------
1/65*|   1/9  |  1/7
1/49 |   1/8  |  1/6
1/33 |   1/6  |  1/5
1/55 |   1/8  |  1/6
*/

#define UC1701_SET_BIAS_RATIO       (0b10100010)
#define UC1701_SET_BIAS_1_7         (0b00000001)
#define UC1701_SET_BIAS_1_9         (0b00000000)

#define UC1701_NOP                  (0b11100011)

#define UC1701_SET_CUR_MODE         (0b11100000)
#define UC1701_RESET_CUR_MODE       (0b11101110)

#define UC1701_SET_STAT_IND_OFF     (0b10101100)
/* two byte command, 2nd byte is don't-care */
#define UC1701_SET_STAT_IND_OFF_2   (0b10101101)

#define UC1701_SET_BOOST_1          (0b11111000)
#define UC1701_SET_BOOST_2          (0b00000000)

/* two byte command */

#define UC1701_SET_ADV_PROG_1       (0b11111010)
#define UC1701_SET_ADV_PROG_2       (0b00010000)
#define UC1701_ADV_PROG_WRAP_COL    (0b00000010)
#define UC1701_ADV_PROG_WRAP_ROW    (0b00000001)
#define UC1701_ADV_PROG_TEMPCO_0    (0b00000000)
#define UC1701_ADV_PROG_TEMPCO_1    (0b10000000)

/* compound command */
#define UC1701_SET_POWER_SAVE       (0b00000000)

#define UC1701_NUM_PAGES 8
#define UC1701_PAGE_BIT_SIZE 8

#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT UC1701_NUM_PAGES * UC1701_PAGE_BIT_SIZE




#endif
