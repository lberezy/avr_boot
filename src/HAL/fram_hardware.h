#ifndef FRAM_HARDWARE_H
#define FRAM_HARDWARE_H

#define FRAM_PORT PORTB
#define FRAM_DDR  DDRB

#define FRAM_CS_PIN PB4

#define FRAM_SIZE_BYTES 2048

#define FRAM_PORT_INIT()          (FRAM_DDR |= _BV(FRAM_CS_PIN))
#define FRAM_CS_DEACTIVATE()      (FRAM_PORT |= _BV(FRAM_CS_PIN))
#define FRAM_CS_ACTIVATE()        (FRAM_PORT &= ~(_BV(FRAM_CS_PIN)))

// opcodes
#define FRAM_WRITE_ENABLE   (0b00000110)
#define FRAM_WRITE_DISABLE  (0b00000100)
#define FRAM_READ_STATUS    (0b00000101)
#define FRAM_WRITE_STATUS   (0b00000001)
#define FRAM_READ_MEMORY    (0b00000011)
#define FRAM_WRITE_MEMORY   (0b00000010)

// status register bits
#define FRAM_STATUS_WEL   _BV(1)
#define FRAM_STATUS_BP0   _BV(2)
#define FRAM_STATUS_BP1   _BV(3)
#define FRAM_STATUS_WPEN  _BV(7)


#define FRAM_MSB_MASK       (0b00011111)

#define FRAM_DUMMY_PACKET   0xff

#endif
