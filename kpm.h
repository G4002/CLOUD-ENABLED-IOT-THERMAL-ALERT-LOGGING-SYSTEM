// FUNCTION DECLERATIONS OF THE KEYPAD MATRIX KEY SCANINNG
#ifndef  KPM_H
#define  KPM_H
#include "types.h"
// Initialization
void Init_Keypad(void);
// column Scan whether the key is pressed or not
u32 Colscan(void);
// checking the row where the key is pressed
u32 Rowcheck(void);
// checking that in specic row which column is pressed
u32 Columncheck(void);
// finally Scaning the value which key is preesed and what's the value of that key
u8 KeyScan(void);
// For Reading the Keys (numeric keypad taken here)
float ReadNum(float *num ,char *ch);
void TakeSesnsorData(char *);

#endif
