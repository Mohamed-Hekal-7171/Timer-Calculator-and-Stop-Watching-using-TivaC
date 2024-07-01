#include "std_types.h"

#ifndef SYSTICKTIMER_H_
#define SYSTICKTIMER_H_



void SysTickDisable(void);
void SysTickEnable(void);
void giveReload(int N);
int getReload(void);
int getCurrent(void);
int getDesiredTicks(float seconds);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait_1ms(void);

#endif