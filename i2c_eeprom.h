#ifndef  I2C_EEPROM_H
#define  I2C_EEPROM_H

#include  "TYPES.H"
// Function Declerations or Prototypes.

// writing a byte into the EEPROM.
void I2C_EEPROM_BYTEWRITE(u8 SlaveAddr , u16 BuffAddr , u8 Data);

// Reading Byte from the EEPROM.
u8 I2C_EEPROM_RANDOMREAD(u8 SlaveAddr , u16 BuffAddr);

// Writing the Page (8 bytes = 1 page in 24C01 MODEL) into the EEPROM.
void  I2C_EEPROM_PAGEWRITE(u8 SlaveAddr ,u16 BuffStartAddr ,s8 *p , u8 Nbytes);

// Contiously Reading from the SLAVE.
void  I2C_EEPROM_SEQREAD(u8 SlaveAddr , u16 BuffStartAddr, s8 *p , u8 Nbytes);

#endif
