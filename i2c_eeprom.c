// Function Definitions.

#include   "TYPES.H"
#include   "DELAY.H"
#include   "I2C_PERIPHERAL.H"
void I2C_EEPROM_BYTEWRITE(u8 SlaveAddr , u16 BuffAddr , u8 Data)
{
	  // Initiate the Start Conditon.
	  I2C_START();
	
	  // Slave Address + R/W(BIT) and Take ACK
	  I2C_WRITE(SlaveAddr << 1);               // WRITE = 0 
	
	  // BuffAdrress & Take ACK.
	  I2C_WRITE(BuffAddr>>8);
	  I2C_WRITE(BuffAddr);
	  // Data and Take ACK.
	  I2C_WRITE(Data);
	 
	  // Stop the Communication by issuing the stop() function.
	  I2C_STOP();
	
	  // Cycle Delay.
	  delay_Ms(10);
}

u8 I2C_EEPROM_RANDOMREAD(u8 SlaveAddr , u16 BuffAddr)
{
	  u8 Data;
	  // Start Condition
	  I2C_START();
	  
	  // Slave Address + Write and Take ACK.
	  I2C_WRITE(SlaveAddr << 1);
	  
    // Buffer Address & Take ACK.
	  I2C_WRITE(BuffAddr>>8);
	  I2C_WRITE(BuffAddr);

	  
	  // Restart the coomunication while in the Reading Stage Only.
	  I2C_RESTART();
	 
	  // Slave address + read and Take ACK.
	  I2C_WRITE(SlaveAddr << 1 | 1);             // READ = 1
	 
	  // Read Byte From the Slave and Give NACK From the MASTER.
	  // Which means enough no of bytes.
	  Data = I2C_NACK();
	  
	  // Stop Condition.
		I2C_STOP();
		
		// Return the Data Content.
		return Data;
}
	
void  I2C_EEPROM_PAGEWRITE(u8 SlaveAddr ,u16 BuffStartAddr ,s8 *p , u8 Nbytes)
{
	  u8 i;
	  // Start Condition.
	  I2C_START();
	 
	  // Slave Address + w.
	  I2C_WRITE(SlaveAddr << 1);
	 
	  // BuffSatrt & take ACK
	  I2C_WRITE(BuffStartAddr>>8);
	  I2C_WRITE(BuffStartAddr);
	  
	  // Write n bytes , For Each Byte take the ACK.
	  
	  for(i=0; i<Nbytes ; i++)
	  {
			 // Write Data and Take ACK.
			 I2C_WRITE(p[i]);
		}
		
		// Stop Condition.
		I2C_STOP();
		
		// Write Cycle Delay.
		delay_Ms(10);
}

void  I2C_EEPROM_SEQREAD(u8 SlaveAddr , u16 BuffStartAddr, s8 *p , u8 Nbytes)
{
	 u8 i;
	 // Start Condition.
	 I2C_START();
	
	 // Slave Address + w and Take ACK.
	 I2C_WRITE(SlaveAddr << 1);
	
	 // Buffer Start Address and take ACK.
	 I2C_WRITE(BuffStartAddr>>8);
     I2C_WRITE(BuffStartAddr);	
	 // Restart the Communication.
	 I2C_RESTART();
	 
	 // Slave Address + READ
	 I2C_WRITE(SlaveAddr << 1 | 1);
	
	 // Read only N Bytes minus one.
	 for(i=0 ;i <Nbytes-1; i++)
	 {
		 p[i] = I2C_MACK();
	 }
	 
	 // Read the Last Byte and give NACK.
	 p[i] = I2C_NACK();
	 
	 // Stop Condition.
	 I2C_STOP();
 }
