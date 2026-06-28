// Function Definitions

#include <LPC21XX.H>
#include "defines.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "init_devices.h"
#include "types.h"
#include "lcd.h"
#include "delay.h"
#include "esp01.h"

extern float setpoint;
int cnt;
// 4 x 4 matrix is using here
const unsigned char  keys[4][4]=
{
	{'1','2','3','U'},
	{'4','5','6','D'},                       // LOOK UP TABLE
	{'7','8','9','-'},
	{'O','0','.','E'}
};

//  4 x 4  KEYAD  INITILIAZATION.
void Init_Keypad(void)
{
	 // Setting the row pins as the output through the direction register.
	 WRITENIBBLE(IODIR1,ROW0,0x0F);
	 // No need to set for the columns bydefault the input pins are zero's only.
	 //WRITENIBBLE(IODIR0,COL0,0);
	 
}
// Column Scaning whether any key is pressed or not.
u32 Colscan(void)
{
 u32 status;
	status=READNIBBLE(IOPIN1,COL0);
	return status < 15 ? 0 : 1;
}
// Finding From Which Row the Key is Pressed.
u32 Rowcheck(void)
{
u32 row;
	for(row=0;row<=3;row++)
	{
		 WRITENIBBLE(IOPIN1,ROW0,~(1<<row)); // masking the bit one by one 
		 /* r=0 1110
		    r=1 1101
		    r=2 1011
		    r=3 0111
		*/
		 // now check if the key is pressed in that particular row or not
		if(Colscan()==0)
		{
			 break;  // after pressing the key we will check the Rowcheck before we not checking here
		}
	}
		
		WRITENIBBLE(IOPIN1,ROW0,0); // RESETIING ALL THE 4 BITS AS ZERO For the next presses Detection
		// need to return the value of the row on which it was pressed
		return row;

}


// After That From With Respect to ROW Which Column Key is Pressed.
u32 Columncheck(void)
{
u32  col;
	 for(col=0;col<=3;col++)
	 {
		  if((READBIT(IOPIN1,COL0 + col))== 0) // if the certain bit or column is zero means
				    break;                       // that key is pressed so returning the col value
			
	 }
	 return col;
 }

// With the Help of the Above Three Functions we will Get the ROW and the Column Value.
// From the Keypad Look up Table(A 2D Array) we are Returning the Some Key Value.
unsigned char KeyScan(void)
{
u32 row,col;
unsigned char KeyVal;
	// check if the key is pressed or not
	while(Colscan()); // if it pressed means the PC go to below statement
	                  // else it will in infinte loop only because from "colscan" function
	row=Rowcheck();
	col=Columncheck();
	//KeyVal=kpm_values[row][col];
	KeyVal=keys[row][col];
	return KeyVal;
}


void TakeSesnsorData(char *Data)
{
	        char flag=0,c=2;
          int cnt,i;
					char decimal;
					unsigned char KeyVal;
	        int k;
	  
AGAIN: 	CmdLCD(CLEAR_LCD);
				Setcursor(1,0);
				StrLCD("SET POINT <= 150");
				Setcursor(2,0);
				CmdLCD(DISP_ON_CUR_ON);
				cnt=0;
				i=0,decimal=0,flag=0;
	      
				
	while(1)
	{
		  KeyVal = KeyScan();
		  delay_Ms(250);
		 
		  
		  if((KeyVal >= '0' && KeyVal <= '9') || (KeyVal == '.'))
			{
				cnt++;
				if(KeyVal == 46)
				{
					decimal++;
					if(decimal >1)
						 goto AGAIN;
				}
				if(i==0 && KeyVal == 46)
					 goto AGAIN;
				if((KeyVal!=46)&&(KeyVal!='E'))
					 flag++;
				if((KeyVal == 46) && (cnt==4))
				{
					
					CmdLCD(CLEAR_LCD);
					Setcursor(1,0);
					//CharLCD(0x7E);
					StrLCD(" WRONG SETPOINT");
					Setcursor(2,0);
					StrLCD("ENTER VALID ONE");
					delay_Ms(200);
					goto AGAIN;
				}
				if(i<=4)
				{
				Setcursor(2,cnt-1);
				CharLCD(KeyVal);
				Data[i++] = KeyVal;
				}
				else
					continue;
			}
			else if((KeyVal == 'E') && (cnt>=1))
			{
				  if(flag>=5)
					{

				    CmdLCD(CLEAR_LCD);
					  Setcursor(1,0);
					  //CharLCD(0x7E);
					  StrLCD(" WRONG SETPOINT");
					  Setcursor(2,0);
					  StrLCD("ENTER VALID ONE");
					  delay_Ms(200);
						flag=0;
					  goto AGAIN;


					}
					for(k=0;k<i;k++)
						{
							  if(Data[k]=='.')
								{
									 c=0;
									 break;
								}
								c=1;
						}
						if(c)
						{
							 if(Data[0] > '1' && i==3)
							 {
								   CmdLCD(CLEAR_LCD);
									 Setcursor(1,0);
									 //CharLCD(0x7E);
									 StrLCD(" WRONG SETPOINT");
								   Setcursor(2,0);
								   StrLCD("ENTER VALID ONE");
								   delay_Ms(200);
					
								   goto AGAIN;
							 }
							
							  Data[i++]='.';
						}
					while(i<5)
					{
						 Data[i++]=48;
					}
				  
					Data[i] = '\0';
					setpoint = myatof(Data);//+0.00001f;
				if(setpoint > 150)
					{
									 CmdLCD(CLEAR_LCD);
									 Setcursor(1,0);
									 //CharLCD(0x7E);
									 StrLCD(" OVERFLOW VALUE");
								   Setcursor(2,0);
								   StrLCD("ENTER VALID ONE");
								   delay_Ms(200);
					
								   goto AGAIN;
					}
					break;
			}
		
	}
	        		
}


