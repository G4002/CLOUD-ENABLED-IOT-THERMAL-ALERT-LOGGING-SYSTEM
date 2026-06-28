// adc_defines.h
#define FOSC 12000000     // Frequency Oscillator
#define CCLK (FOSC*5)     // C.P.U Clock
#define PCLK  (CCLK/4)    // Pheripheral Clock
#define ADCCLK  3000000   // ADC CLOCK UPTO 4.5MHz We can Give 
#define CLKDIV ((PCLK/ADCCLK)-1) // CLOCK DIVISION
// defining for ADCR Special Function Register (SFR)
#define CLKDIV_BITS 8 // To Load the CLKDIV value to the ADCR Register
#define PWDN_BIT 21 // Power Down Bit Whenever u want use the ADC pheriperal u need to set the powerdown bit
#define CONV_START_BIT 24 // Same here we need to set before starting the conversion
// Configure ADDR S.F.R Register
#define RESULT_BITS 6
#define DONE_BIT 31 // if the bit contains 1 Data Conversion is happen
