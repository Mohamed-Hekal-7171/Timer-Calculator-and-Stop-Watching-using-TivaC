
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*
R1 - R4 : Pins E0 - E3
C1 - C4 : Pins D0 - D3
*/

void KeyPad_Init(void);
void delay(uint32_t n);
char KeyPad_Read(void);

#endif