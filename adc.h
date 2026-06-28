#ifndef  ADC_H
#define  ADC_H

#include "types.h"
void Init_ADC(void);
void Read_ADC(u32 chNo,u32 *adcDval,f32 *adcAval);

#endif
