#ifndef   I2C_PERIPHERAL_H
#define   I2C_PERIPHERAL_H

// Function Declerations.

#include  "TYPES.H"

// Initialzing the I2C.
   void  Init_I2C(void);        

// I2C Start.
   void  I2C_START(void);
	
// I2C Stop.
   void  I2C_STOP(void);
	
// I2C RESTART.(Reading from the SLVAE Purposes).
   void  I2C_RESTART(void);
	 
// I2C WRITE
   void  I2C_WRITE(u8);
	 
// I2C NACK
   u8  I2C_NACK(void);
	
// I2C MACK    (MASTER ACK While Reading from the SLAVE).
   u8  I2C_MACK(void);

#endif
