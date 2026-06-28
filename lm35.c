#include   "types.h"
#include   "adc.h"

void Read_Temperature(s8 TempType ,f32 *temp)
{

        u32 adcDVal;
        f32 adcAVal;
        f32 degC,degF;

        Read_ADC(1,&adcDVal,&adcAVal);

        degC = adcAVal*100;
        degF = (degC *1.8) + 32;

        if(TempType == 'c')
        {
             *temp = degC;
    }
        else if(TempType == 'F')
        {
            *temp = degF;
        }
}
