#ifndef   EEPROM_DEVICE_ADDRESS_H
#define   EEPROM_DEVICE_ADDRESS_H

// 24C01 EEPROM DEVICE ADDRESSES.
/* In the EEPROM IC We have the 3 pins for this address selection,
   NOTE: Some EEPROMS only.
   so we can use multiple SLAVES with  the Single EEPROM/.
   multiple SLAVES means 2^3= 8 SLAVES Can we Use.
   It Depends Upon the EEPOMS Type and the company some may give more than 3 and less than 3
*/   
   // And here in 3 pins mode they give the 5 BIT Device ADDERSS as same.
   // Based on that we can connect the hardware.

#define  ADDR1     0x50    // 0101 0000      actually 1010 real address part.
#define  ADDR2     0x51    // 0101 0001
#define  ADDR3     0x52    // 0101 0010
#define  ADDR4     0x53    // 0101 0011
#define  ADDR5     0x54    // 0101 0100
#define  ADDR6     0x55    // 0101 0101
#define  ADDR7     0x56    // 0101 0110
#define  ADDR8     0x57    // 0101 0111

#define  EEPROM_SENSOR   ADDR1 // (Testing Purpose).

#endif
