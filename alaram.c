// Function defintions.
#include <LPC21XX.H>
#include "defines.h"
void  Init_alaram(void)
{
	 // BUZZER.  
	 IODIR0 |= 1<< 13;
	
	 // LED'S.
   WRITEBYTE(IODIR1 , 24 , 0xFF);
	   
}

void ON(void)
{
	    IOSET0 = 1<< 13;
	  
}
void OFF(void)
{
	  IOCLR0 = 1<< 13;
	  
}
