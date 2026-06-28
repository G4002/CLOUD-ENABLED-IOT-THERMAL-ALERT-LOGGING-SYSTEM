#include "pin_connect_block.h"
#include "types.h"
#include "delay.h"
#include <LPC21XX.h>
#include "adc_defines.h"
#include "pin_function_defines.h"
void Init_ADC(void)
{
	// Configure ADCR
	CfgPortPinFunc(0,28,PIN_FUNC2);
	ADCR|=((1<<PWDN_BIT)|(CLKDIV<<CLKDIV_BITS));
}

void Read_ADC(u32 chNo,u32 *adcDval,f32 *adcAval)
{
	// intially clear the channel
	ADCR=(ADCR&(0xFFFFFF00));
	ADCR|=((1<<CONV_START_BIT)|(1<<chNo));
	delay_Us(3);
	// check until the conversion is success
	 ADCR &= ~(1 << CONV_START_BIT);
	while(((ADDR>>DONE_BIT)&1)==0);
	*adcDval=((ADDR>>RESULT_BITS)&0x3FF);
	*adcAval=(*adcDval*(3.3/1024));
}
