// Function Definitons are Here.
// Including the Required Header files.

#include   "LPC21XX.H"
#include   "delay.h"
#include   "pin_connect_block.h"
#include   "pin_function_defines.h"
#include   "i2c_defines.h"

void   Init_I2C(void)
{
	    // Configure p0.3 pin as the SDA Line.
	    CfgPortPinFunc(0 ,3 , SDA_PORT0_PIN3);
	    // Configure p0.4 pin as the SCK Line.
	    CfgPortPinFunc(0 ,2 , SCK_PORT0_PIN4);
	  
	    // Confugure the Speed for the I2C Serial Communication.
	    I2SCLL = I2C_DIVIDER;  // LOWR PART.
	    I2SCLH = I2C_DIVIDER;  // HIGHER PART.
	
	    // To enable the I2C Communication we need to set the I2CENABLE Bit using I2CONSET Register.
  	    I2CONSET = 1 << I2CENABLE;
}

void  I2C_START(void)
{
	    // START CONDITION.
	    I2CONSET = 1 << STA_BIT;
	    // Wait for the Event is Success or not.
	    while(((I2CONSET >> SI_BIT)&1)==0);        // Until SI_BIT - 1 PC  stay here only.
	    // The Start Conditon Does the CLOCK Geration as HIGH to LOW from the SDA pin so Communication Begins.
	    // After that we need to stop the HIGH to LOW Pulse Generation.
      	    // Because we need to start real Communication Such as DATA.

      	    // Clear STOP Condition.
            I2CONCLR = 1 << STAC_BIT;      // you can use Same Bit Also STA_BIT Both Bit Postions are same.
}	

void  I2C_RESTART(void)
{
	    // It is same as the I2C_START Only.
	    // We just Want the SI_BIT because in some where function the SI_BIT is 1 means successfull Event.
	    // so here we are performing the another event right.
	    // previous 1 we are trying to start another event so we need to clear the bit and start the eevent and  succesfull status will be there as 1.
	    // otherwise if the event is not done also it will shows it done.
	    
	    // Start Condition.
	    I2CONSET = 1 << STA_BIT;
	    // Clear the Previous Event success status bit the SI_BIT.
	    I2CONCLR = 1 << SIC_BIT;
	    // Wait for the Event is Success or not.
	    while(((I2CONSET >> SI_BIT)&1)==0);        // Until SI_BIT - 1 PC  stay here only.
	    // Clear STOP Condition.
      	    I2CONCLR = 1 << STAC_BIT;
}

void  I2C_WRITE(u8 Data)
{
	   // We are Writing into the EEPROM.
	   // We have the Register to hold our Data.
	    
	   I2DAT = Data;
	   // Remember every time we need to clear the SI_BIT if any event you are performing.
	   // so clear the SI_BIT;
	   I2CONCLR = 1 << SIC_BIT;
	   // Now wait for the status of the SI_BIT because in above 2 lines you are writing the data right we need to confirm right whether the event is success or not.
	   while(((I2CONSET >> SI_BIT)&1)==0);
}

unsigned char  I2C_NACK(void)
{
	   // NOACK  Stop Reading after 1 byte of Data.
	   // By default in the I2CONSET Register AA_BIT is 0.
	   // So no need to write the any to it.
	   
	   // Clear the previous event.
	   I2CONCLR = 1 << SIC_BIT; 
	   // Now wait for the data to collect from the I2DAT Register.
	   while(((I2CONSET >> SI_BIT)&1)==0);
     // Now return the data.
     return I2DAT;
}

unsigned char  I2C_MACK(void)
{
	  // While it is the READ mode.
	  // Master ACK.
	  // Whether the Master need the More Bytes or not.
	  // By setting AA_BIT 1 we can read the byte continously. util AA_BIT is set to 0.
	  
    /* In the MASTER Reciver Mode.
	     
	       Master must give the Acknowledgment whether he want to read another byte or not.
	      
	       ->  Yes , He want's Another Byte.
	 
	           SDA      -  LOW
	           AA_BIT   -  1
	           at the 9th Clock Pulse.
	 
         -> No , he Doesn't need.
	 
	           SDA      -  HIGH
	           AA_BIT   -  0
	           at the 9th Clock Pulse.
	  */
		// Assert ACK.
		I2CONSET = 1 << AA_BIT;   
		// Clear the Previous event status.
		I2CONCLR = 1 << SIC_BIT;
		// Wait for your event.
		while(((I2CONSET >> SI_BIT)&1)==0);
		// Clear the Assert Acknowledgment Bit (AAC_BIT) In I2CONCLR Register.
		I2CONCLR = 1 << AAC_BIT;
		// return the DATA That avaialbe in the I2DAT Register(internally in Controller it will Happens).
		return I2DAT;
	}

void  I2C_STOP(void)
{
	  // I2C STOP Conditon.(LOW To HIGH CLOCK PULSE GENERATION).
	  I2CONSET = 1 << STO_BIT;
	  // Clear the Previous Event (if any).
	  I2CONCLR = 1 << SIC_BIT;
    // STOP Will Be cleared Automatically.
}
