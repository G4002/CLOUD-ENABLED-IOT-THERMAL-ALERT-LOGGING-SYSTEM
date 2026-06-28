// FUNCTION DEFINITIONS OF THE RTC PERIPHERAL 

#include  <LPC21XX.H>      // For the SFR'S Usage Purposes.
#include  "rtc_defines.h"  // For the function RTC Initiliazation Purposes (PRENINT,CCR...).
#include  "lcd.h"          // Display function will use the 16 x 2 LCD_DRIVER.
#include  "lcd_defines.h"  // Command are as in the MACROS.
#include  "types.h"

// First Step---->  For Day of WEEK we need the Days Names ,So going to take an 2D-ARRAY.
// In LINITED LENGTH of String of 4 BYTES.

 char DayOfWeek[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

// Now Function Definitions 

//---------> Initilazing the RTC

void  Init_RTC(void)
{
	  // RESET THE RTC THROUGH CCR (CLOCK CONTROL REGISTER).
	  CCR = RTC_RESET;
	  // We are Doing this Project on Two Microcontroller's LPC2129 and the LP2148
	  // LPC2129 --> RTC runs ON-CHIP using PCLK (needs PREINT and PREFRAC Setup).
	  // LPC2148 --> RTC run uisng the External 32.768KHz Crystal (selected with CLKSRC).
	  // LPC2129 --> No Seprate VBAT Circuit.
	  // LPC2148 --> Has VBAT Circuit for Internal Registers Running Purpose even there is no power.
	
	  // so I am writing the program for to BOARD so using the Conditional Statements for this.
	  
	  #ifdef  LPC2148_MODE
	          // we need to select the CLOCK SOURCE and we need to ENABLE the RTC.
	          CCR = RTC_ENABLE | RTC_CLKSRC;
	  #else 
	          // For LPC2129 MODE or Controller.
	          PREINT  = PREINT_VAL;
	          PREFRAC = PREFRAC_VAL;
	          // Now need to Enable the RTC through CCR register.
	          CCR = RTC_ENABLE;
    #endif
}

void  GetRTCTimeInfo(s32 *Hour , s32 *Minute , s32 *Second)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Hour)   =  HOUR; 
	       (*Minute) =  MIN;
	       (*Second) =  SEC;
}

void  GetRTCDateInfo(s32 *Date , s32 *Month , s32 * Year)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Date)   =  DOM;
	       (*Month)  =  MONTH;
	       (*Year)   =  YEAR;
}

void  GetRTCDay(s32 *Day)
{
         // LOADING From SFR To the GLOBAL Variables.	
         (*Day)    =  DOW;
}

void  GetRTCHour(s32 *Hour)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Hour)   =  HOUR;
}

void  GetRTCMin(s32 *Minute)
{        
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Minute) =  MIN;
}

void  GetRTCSec(s32 *Second)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Second) =  SEC;
}

void  GetRTCDate(s32 *Date)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Date)   =  DOM;
}

void  GetRTCMonth(s32 *Month)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Month)  =  MONTH;
}

void  GetRTCYear(s32 *Year)
{
	       // LOADING From SFR To the GLOBAL Variables.
	       (*Year)   =  YEAR;
}

void  SetRTCTimeInfo(u32 Hour , u32 Minute ,u32 Second)
{
	      // Assigning Directing the value to the SFR'S.
	       HOUR      =  Hour;
	       MIN       =  Minute;
	       SEC       =  Second;
}

void  SetRTCDateInfo(u32 Date , u32 Month , u32 Year)
{
	       // Assigning Directing the value to the SFR'S.
	       DOM       =  Date;
	       MONTH     =  Month;
	       YEAR      =  Year;
}

void  SetRTCDay(u32 Day)
{
	       // Assigning Directing the value to the SFR'S.
	       DOW       =  Day;
}

void  SetRTCHour(u32 Hour)
{
	       // Assigning Directing the value to the SFR'S.
	       HOUR      =  Hour;
}

void  SetRTCMin(u32 Minute)
{
	       // Assigning Directing the value to the SFR'S.
	       MIN       =  Minute;
}

void  SetRTCSec(u32 Second)
{
	       // Assigning Directing the value to the SFR'S.
	       SEC       =  Second;
}

void  SetRTCDate(u32 Date)
{
	       // Assigning Directing the value to the SFR'S.
	       DOM       =  Date;
}

void  SetRTCMonth(u32 Month)
{
	       // Assigning Directing the value to the SFR'S.
	       MONTH     =  Month;
}

void  SetRTCYear(u32 Year)
{
	       // Assigning Directing the value to the SFR'S.
	       YEAR      =  Year;
}

void  DisplayRTCTime(u32 Hour , u32 Minute , u32 Second)
{
    // From the GLOBAL Variables I am going to Display through the LCD.
    // Yes, we can directly use the SFR'S for the Display Operation.
    // But while Displaying them on LCD, we are trying to display Character by character.
	  // Like  12:23:12 in 24 hours format means Doing the Digit Extraction Method.  	
	  // So if I perform Them on the SFR'S Means Every Time we are Trying For Accessing that Particular SFR.
	  // Which Increases Extra and UseLess Burden On the CPU or PROCCESSOR.
	  // So that's the main Reason of using GLOBAL Variables.
	  
	  /****** ON THIS FORMAT DISPLYING_____ HOUR:MIN:SEC_______******************************/
	 
	  Setcursor(1,0);
	  CharLCD(2);
	  Setcursor(1,4);          // ON 16 x 2 LCD (confusion on this line refer function  "setcursor()" defininton.
	  CharLCD((Hour/10)+48);   // +48 because of Hour is the Integer for LCD Displaying we need to give the ASCII charcter so that's the reason +48 (Integer to ASCII) conversion.
    CharLCD((Hour%10)+48);
	  CharLCD(':');
    CharLCD((Minute/10)+48);
    CharLCD((Minute%10)+48);
	  CharLCD(':');
    CharLCD((Second/10)+48);
    CharLCD((Second%10)+48);
}

void  DisplayRTCDate(u32 Date , u32 Month , u32 Year)
{
	  /****** ON THIS FORMAT DISPLYING_____ DATE/MONTH/YEAR_______******************************/
	  
	  Setcursor(2,0);          // ON 16 x 2 LCD (confusion on this line refer function  "setcursor()" defininton.
	  CharLCD((Date/10)+48);
	  CharLCD((Date%10)+48);
	  CharLCD('/');
	  CharLCD((Month/10)+48);
	  CharLCD((Month%10)+48);
	  CharLCD('/');
	  U32LCD(Year);            // Digit Extraction not preferable option.
}
void DisplayRTCDay(s8 dow)
{
	
	StrLCD(DayOfWeek[dow]);
}
