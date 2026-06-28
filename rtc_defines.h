// RTC (REAL TIME CONNECTION RELATED MACROS)
// rtc_defines.h
#ifndef RTC_DEFINES_H
#define RTC_DEFINES_H

// System Clock and Peripheral Clock Genration.

#define  FOSC         12000000     // Frequency Oscillator. FOSC - 12MHz.
#define  CCLK         (FOSC*5)     // CPU Clock is 60MHz.
#define  PCLK         (CCLK/4)     // Peripheral CLOCK 15MHz.

// RTC PREINT and PREFRAC Registers Data Loading.
// Formula's are Taken from the Data Sheet Only.
// RTC Crystal required frequecny is 32.768KHz.

#define  PREINT_VAL   ((PCLK/32768)-1) 
#define  PREFRAC_VAL  (PCLK-(PREINT_VAL+1)*32768)

// RTC Peripheral Registers Configuring the Register through the MACROS For more READABILITIY purpose.
// Clock Control Register.(CCR).

#define  RTC_ENABLE   (1<<0)       // ENABLING the BIT 0 of CCR Register.(RTC) Time Counters are Enabled.
#define  RTC_RESET    (1<<1)       // RESETING the Time Counters to Zero, means it again start from Begining.

// For LPC2148 We have two RTC'S ON Chip and the External RTC.
// To configure the  PRESCALER Register we have to set the single bit only.

#define  RTC_CLKSRC   (1<<4)
//#define LPC2148_MODE
#endif
