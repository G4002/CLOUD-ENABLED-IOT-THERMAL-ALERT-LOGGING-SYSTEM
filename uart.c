// Uart.c Function defintions.

#include  <LPC21XX.H>
#include  "pin_connect_block.h"
#include  "pin_function_defines.h"
#include  "uart_defines.h"
#include  "types.h"
#include  "delay.h"

unsigned char i=0,ch,r_flag;
char buff[200]="hello",dummy;


void UART_ISR(void)__irq
{
	  if((U0IIR & 0x04))
		{
			 ch = U0RBR;
			 if(i<200)
			 {
				 buff[i++] = ch;
			 }
		}
		else
		{ 
			  dummy = U0IIR;
		}
		VICVectAddr = 0;
}


void  Init_UART(void)
{
	 // Initialization of the UART Pins or(configguring the Pins and the Loading the Baud Value).
	 
	 CfgPortPinFunc(0,0,PIN_FUNC2);
	 CfgPortPinFunc(0,1,PIN_FUNC2);
	 
	 U0LCR = 1<<DLAB_BIT | WORD_LENGTH;
	
	 U0DLL = DIVISOR;
	 U0DLM = DIVISOR>>8;
	
	 U0LCR &=~(1<<DLAB_BIT); 
	 
	 VICIntEnable |= 1 << 6;
	 VICVectAddr0 = (unsigned int)UART_ISR;
	 VICVectCntl0 = 0x20|6;
	 
	 U0IER = 1<<0;
	
}


// Now transmit 1 Byte.

void UART_TxChar(unsigned char TxByte)
{
	U0THR = TxByte;
	while(((U0LSR >> TEMT)&1)==0);
}

unsigned char UART_RxChar(void)
{
	while(((U0LSR >> RDR)&1)==0);
	return U0RBR;
}

void UART_TxString(char *str)
{
	while(*str)
	{
		UART_TxChar(*str);
		
		str++;
	}
}

void UART_U32(unsigned int num)
{
	int i=0;
	char str_num[10];
	
	while(num)
	{
		str_num[i++] = (num%10) + 48;
		num/=10;
	}
	str_num[i]='\0';
	
	for(--i;i>=0;i--)
	{
		UART_TxChar(str_num[i]);
	}
}

void UART_S32(int num)
{
	if(num<0)
	{
		UART_TxChar('-');
		num = -num;
	}
	UART_U32(num);
}

void UART_F32(float fnum,unsigned char Ndp)
{
	// Ndp ---> Upto the N Decimal Points.
	int n,i;
	if(fnum < 0.0)
	{
		UART_TxChar('-');
		fnum = -fnum;
	}
	n = fnum;
	UART_U32(n);
	UART_TxChar('.');
	for(i=0;i<Ndp;i++)
	{
		fnum = (fnum - n)*10;
		n=fnum;
		UART_TxChar(n+48);
	}
}

void  UART_RxString( char *str,unsigned int MaxLen)
{
	     int i=0;  // indexing purpose.
	     unsigned char ch;     // reading character by character.
	     while(1)
			 {
				 ch = UART_RxChar();
				 if(ch=='\n'||ch=='\r')
				 {
					 str[i]='\0';
					 break;
				 }
				 else if(i>=MaxLen-1)
				 {
					 str[i]='\0';
					 break;
				 }
				 else
				 {
					 str[i++]=ch;
				 }
			 }
		 }
