#ifndef  UART_H
#define  UART_H

void  Init_UART(void);
void UART_TxChar(unsigned char TxByte);
void UART_TxString(char *str);
void UART_U32(unsigned int num);
void UART_S32(int num);
void UART_F32(float fnum,unsigned char Ndp);
unsigned char UART_RxChar(void);
void  UART_RxString(unsigned char *str,unsigned MaxLen);
void UART_ISR(void)__irq;
#endif
