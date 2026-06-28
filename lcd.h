#ifndef  LCD_H
#define  LCD_H
// HERE FUNCTION DECLEARATION OR PROTITYPING OF THE LCD USED FUNCTIONS
#include "types.h"

void WriteLCD(u8 byte); // write to LCD either Command or Data or Mode Selection through this only we need to write
void CmdLCD(u8 CmdByte); // writing the paticular command and this function writelcd will takes place
void Init_LCD(void); // intitilization of the LCD pins number and Direction Register Setting
void CharLCD(u8 ascival); // writing character on the LCD internally it has the writeLCD will take place
void StrLCD(s8*); // for the string display
void U32LCD(u32); // displaying the integer value--only unsigned integer
void BuildCGRAM(u8*,u8);// OWN CHARACTERS DISPLAYING
void Setcursor(char mode,char pos);
void F32LCD(f32 fnum,u32 nDP);
void Display_temperature_on_LCD(void);
#endif
