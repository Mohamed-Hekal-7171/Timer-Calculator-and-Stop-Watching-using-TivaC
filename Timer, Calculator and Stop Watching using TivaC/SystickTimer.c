#include "stdio.h"
#include "tm4c123gh6pm.h"
#include "std_types.h"
#include "math.h"
#include "SystickTimer.h"

//1ms Timer
void SysTick_Wait_1ms(void)							
{
	NVIC_ST_CTRL_R = 0;										// disable sysTick during setup
	NVIC_ST_RELOAD_R = 16000 - 1;					// number of counts
	NVIC_ST_CURRENT_R = 0;								// any write to CURRENT clears it
	NVIC_ST_CTRL_R = 0x05;								// enable SysTick with core clock
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0){}		//wait for flag
	NVIC_ST_CTRL_R = 0;										// disable sysTick
}


//1ms*delay Timer
void SysTick_Wait(uint32_t delay)
{
	uint32_t i;
	for (i = 0; i < delay; i++)
	{
		SysTick_Wait_1ms();					// wait 1ms
	}
}



void SysTickDisable(void){
  NVIC_ST_CTRL_R =0;
}

void SysTickEnable(void){
  NVIC_ST_CTRL_R =5;
}

void giveReload(int N){
  NVIC_ST_RELOAD_R = N;
}

int getReload(void){
  return NVIC_ST_RELOAD_R;
}

int getCurrent(void){
  return NVIC_ST_CURRENT_R;
}


int getDesiredTicks(float seconds){
  int N;
  N = seconds*16*10*10*10*10*10*10;
  N = N-1;
  return N;
}


