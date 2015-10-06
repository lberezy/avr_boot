#ifndef SD_HARDWARE_H
#define SD_HARDWARE_H

#define SD_PORT PORTA
#define SD_DDR  DDRA

#define SD_CS_PIN PA0


#define SD_PORT_INIT()          (SD_DDR |= _BV(SD_CS_PIN))
#define SD_CS_DEACTIVATE()      (SD_PORT |= _BV(SD_CS_PIN))
#define SD_CS_ACTIVATE()        (SD_PORT &= ~(_BV(SD_CS_PIN)))

#endif
