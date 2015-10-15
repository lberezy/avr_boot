# avr_boot
---
## Description
This is an interactive bootloader that provides an interface for loading program
code into an AVR via an SD card.
It provides a graphical user interface via an LCD for the user to select a
program on the SD card to load into user program space on the AVR.
Due to the size of the LCD and FAT libraries involved in providing the user
interface as well as the maximum boot-loader size specified by the AVR, a
section of flash space just before the boot section is given as a general
library for SD, FAT, LCD, graphics, etc. libraries that the device may use.
To make optimal use of code space, the user applications may be linked against
this included library section.

## Hardware
* ATMega16
* MicroSD
* SPI LCD (DOGS6-102)
* 16 Kb FRAM
