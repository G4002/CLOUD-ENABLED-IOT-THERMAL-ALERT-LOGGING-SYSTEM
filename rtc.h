#ifndef  RTC_H
#define  RTC_H

#include "types.h"

// RTC_INITIALIAZATION

void Init_RTC(void);  // Initiliazation of the RTC with Help of SFR'S (CCR).

// Reading From the SFR'S data and copying to GLOBAL VARIABLE in the program for the Application.
void  GetRTCTimeInfo(s32 *,s32 *,s32*);
void  GetRTCDateInfo(s32 *,s32 *,s32 *);
void  GetRTCDay(s32 *);
void  GetRTCHour(s32 *);
void  GetRTCMin(s32 *);
void  GetRTCSec(s32 *);
void  GetRTCDate(s32*);
void  GetRTCMonth(s32*);
void  GetRTCYear(s32*);
void  GetDay(s32*);

// Displaying them on the LCD Display through the functions.
// Displaying from the GLOBAL Varaibles.
void  DisplayRTCTime(u32 ,u32,u32);
void  DisplayRTCDate(u32,u32,u32);
void  DisplayRTCDay(u32);

// Setting the TIME , DATE , DAY , HOUR , MIN , SEC , DATE , MONTH , YEAR Directly into SFR'S
void  SetRTCTimeInfo(u32,u32,u32);
void  SetRTCDateInfo(u32,u32,u32);
void  SetRTCDay(u32);
void  SetRTCMonth(u32);
void  SetRTCYear(u32);
void  SetRTCDate(u32);
void  SetRTCHour(u32);
void  SetRTCMin(u32);
void  SetRTCSec(u32);

/*************** THIS FUNCTIONS DEFINITION USES THE RTC SFR'S like
           HOUR , MIN ,SEC , MONTH , YEAR , DOW(Day of week) , DOM(date of month) and all....
					 ***/
#endif
