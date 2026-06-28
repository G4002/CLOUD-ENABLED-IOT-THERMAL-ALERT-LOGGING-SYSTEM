// Function definitions
#include <LPC21XX.H>
#include "defines.h"
#include "delay.h"        // Delay function Inclusion.
#include "types.h"        // Typedef.
#include "lcd.h"          
#include "lcd_defines.h"  // LCD commands as in the file of MACROS.

//>>> pin number Descrption
#define LCD_DATA  5
#define LCD_RS    19 // REGISTER SELECT PIN EITHER COMMAND -'0' OR "DATA - '1'.
#define LCD_RW    18    // READ - '1' and WRITE -'0'.
#define LCD_EN    20// FOR HIGH TO LOW PULSE GERNERATION WAITING PERIOD CAN WE SAY.

extern float temperature;
// Intialization function
// CGRAM CREATION.

unsigned char  CGRAM[64]=
{
	    0x1F,0x11,0x11,0x17,0x17,0x17,0x1F,0x1F,
	    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,
	    0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	    0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	    0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1F,
	    0x1F,0x11,0x1B,0x1B,0x1B,0x1B,0x1F,0x1F,
	    0x1F,0x11,0x17,0x11,0x17,0x11,0x1F,0x1F,
      0x1F,0X11,0X11,0X15,0x15,0x15,0x1F,0x1F
	    
};

void Display_temperature_on_LCD(void)
{
	 Setcursor(2,0);
     CharLCD(1);
     Setcursor(2,2);	
	 CharLCD(5);
	 CharLCD(6);
	 CharLCD(7);
	 CharLCD(0);
	 CharLCD(0x3A);
   
	 F32LCD(temperature,1);
	 CharLCD(0xDF);
	 CharLCD('c');
	 Setcursor(1,15);
	 CharLCD(3);
	 Setcursor(2,15);
	 CharLCD(4);
	
}

void Init_LCD(void)
{
	// DIRECTION SETTING
	WRITEBYTE(IODIR0,LCD_DATA,0xFF);
	SETBIT(IODIR0,LCD_RS);           // REGISTER SELECT PIN
	SETBIT(IODIR0,LCD_RW);           // READ/WRITE PIN
	SETBIT(IODIR0,LCD_EN);           // ENABLE PIN
	
	// 8 Bit MODE Parallel Connection Model
	delay_Ms(15); // for 8bit mode we need to give its the data sheet tell to us
	CmdLCD(0x30); // function set for 8bit mode
	delay_Ms(4); // ITS AN RULE WE NEED TO FOLLOW THAT'S IT
	CmdLCD(0x30); // same
	delay_Us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE); // USING THE 2 LINES IN THE 16X2 DISPLAY
	CmdLCD(DISP_ON_CUR_BLINK);
	CmdLCD(CLEAR_LCD); // Intially clear the total LCD
	CmdLCD(SHIFT_CUR_RIGHT); // moving the cursor position to right side
	CmdLCD(DISP_ON_CUR_OFF);
}
// sending the command to write in the LCD
void CmdLCD(u8 CmdByte)
{
	 // writing the command 
	 // we need to select the RS Pins as "LOW" RS-0
	 // SO WE NEED TO CLEAR OR SEND THE 0 TO THE RS PIN
	 IOCLR0=1<<LCD_RS;
	// NOW WE NEED TO WRITE INTO THE LCD WHATHERVER WE WANT WRITE EITHER COMMAND OR DATA
	WriteLCD(CmdByte);
}
// Writing the Data or Command to the LCD Driver or to the Module 
void WriteLCD(u8 byte)
{
	// while writing into the LCD we need to Clear the "pin RW-0" then it takes the data from us
	IOCLR0=1<<LCD_RW;
  // using the writebyte macro i am writing into it
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	// aftering writing into it we need to enable "EN" pin as high to low pulse 
	// minimum "450ns" we need to wait for next data writing 
	// so we are performimg some high to low pulse as "1 micro second which is more thsn enough"
	IOSET0=1<<LCD_EN;
	delay_Us(1); // for high to low pulse generation
	IOCLR0=1<<LCD_EN; 
	// after wait some to write it on the LCD
	delay_Ms(2); // wait some milli second here "2ms" I hava Taken
}
// character Displaying on the LCD 
void CharLCD(u8 asciival)
{
	// writing into the LCD 
	 // So RS pin set because we are writing the data into it 
	// RS-1 COMMAND REGISTER
	// RS-0 DATA REGISTER
	IOSET0=1<<LCD_RS;
	WriteLCD(asciival);
}
// String Displaying on the LCD
void StrLCD(s8*p)
{
	while(*p)
	{
		CharLCD(*p);
		p++;
	}
}
// NOW FUNCTION FOR DISPLAYING THE INTEGER VALUE
// U32LCD
// FIRST WE NEED TO KNEW THE RANGE OF unsigned int is 0 to 4,294,967,295-->>which is 10 Digit number
// so array of 10 characters in the ascii format is sufficient 
void U32LCD(u32 num)
{
	u8 lnum[11]; // 10 digits so 10 characters size is enough
	s32 i=0;
	if(num==0)
	{
		CharLCD('0');
		return;
	}
	while(num)
	{
		
		lnum[i++]=(num%10)+'0'; // converting it into the ascii value integer to ascii conversion
		
		num=num/10;
	}
	lnum[i]='\0';
	for(--i;i>=0;i--)
	{
		CharLCD(lnum[i]);
	}
}
// FOR DISPLAYING THE CUSTOM CHARACTERS
void BuildCGRAM(u8*p,u8 nBytes)
{
	u32 i;
	// Send Command to start the CGRAM 
	CmdLCD(GOTO_CGRAM_START);
	// Select The DATA REGISTER
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
		WriteLCD(p[i]); //writing to the CGRAM own symbol character by character
		delay_Us(50);
	} // USING THE INDDEX TRAVERSAL WE HAVE DONE IT 
	  //>>>INPUT ARRAY BASE ADDRESS COLLECTED THROUGH THE character pointer and then index wise displaying one by one character
	  // Again Point Back to DDRAM start Display
	  //CmdLCD(GOTO_LINE1_POS0);
}

void Setcursor(char mode,char pos)
{
	if(mode==1)
	{
		CmdLCD(GOTO_LINE1_POS0+pos);
	}
	else if(mode==2)
	{
		CmdLCD(GOTO_LINE2_POS0+pos);
	}
}

void F32LCD(f32 fnum,u32 nDP)
{
	u32 num,i;
	if(fnum<0.0)
	{
		CharLCD('-');
		fnum=-fnum;
	}
	num=fnum;
	U32LCD(num);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		 fnum=(fnum-num)*10;
		 num=fnum;
		 CharLCD(num+48);
	}
}
