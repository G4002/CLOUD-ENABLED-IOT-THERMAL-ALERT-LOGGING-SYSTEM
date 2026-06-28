// NOW HERE I AM USING THIS FILE AS THE DELAY 
// MEANS ITS AN PERMENANET ONE I CANT WANT TO CHNAGE 
// THIS DELAY FILE I WILL USE EVERY TIME I WANT IN MY TASK

#include "types.h"
// No need of function declerations and prototypes because we will declare it in the seperate header file

/* >>Microsecond << */
void delay_Us(u32 dlyUs) 
{
	for(dlyUs*=12;dlyUs>0;dlyUs--); // I prefering the for loop which less instructtion while converting it in Aessembly compare to while loop
}
/* >> Milli second <<*/
void delay_Ms(u32 dlyMs)
{

	for(dlyMs*=12000;dlyMs>0;dlyMs--);
}
/* >> For generating the second directly <<*/
void delay_s(u32 dlys)
{
	for(dlys*=12000000;dlys>0;dlys--);
}









	
