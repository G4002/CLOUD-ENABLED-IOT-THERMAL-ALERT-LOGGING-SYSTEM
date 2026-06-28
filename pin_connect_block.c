#include "types.h"  // For the u32,s8 etc..
#include <LPC21XX.h> // Controllers files
#include "pin_function_defines.h" // For Pin Fnctions F1,F2,F3,F4 like that

void CfgPortPinFunc(u32 portNo,u32 pinNo,u32 pinFunc)
{
	if(portNo==0)
	{
		if(pinNo<=15)
		{
			PINSEL0=((PINSEL0 &~(3<<((pinNo)*2)))|(((pinFunc)<<(pinNo*2))));
		}
		else if(pinNo>=16 && pinNo<=31)
		{
			PINSEL1=((PINSEL1 &~(3<<((pinNo-16)*2)))|(((pinFunc)<<((pinNo-16)*2))));
		}
	}
		else if(portNo==1)
		{
			if(pinNo>=16 &&pinNo<=31)
			{
				PINSEL2=((PINSEL2 &~(3<<((pinNo-16)*2)))|(((pinFunc)<<((pinNo-16)*2))));
			}
		}
	}
