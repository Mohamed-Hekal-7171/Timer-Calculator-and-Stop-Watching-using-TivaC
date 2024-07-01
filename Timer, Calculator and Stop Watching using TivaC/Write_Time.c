#include "Write_Time.h"
#include "lcd.h"
#include "SystickTimer.h"
#include "std_types.h"

char flag_continue = 1; //a flag to resume cooking or stop cooking


void Write_Timer_zero(void)
{
	LCD_Cmd(moveCursorRight);      //direction of cursor to right
	LCD_Cmd(clear_display);        //clear whatever is written on display 
	LCD_Data('0');					//(0)0:00
	LCD_Data('0');					//0(0):00
	LCD_Data(':');					//00(:)00
	LCD_Data('0');					//00:(0)0
	LCD_Data('0');					//00:0(0)
	delay_milli(500);
}


void Write_Timer(short time4, short time3, short time2, short time1)
{
	LCD_Cmd(moveCursorRight);      //direction of cursor to right
	LCD_Cmd(clear_display);        //clear whatever is written on display 
	LCD_Data(time4 + '0');					//(0)0:00
	LCD_Data(time3 + '0');					//0(0):00
	LCD_Data(':');					        //00(:)00
	LCD_Data(time2 + '0');					//00:(0)0
	LCD_Data(time1 + '0');					//00:0(0)
}       


void Start_timer(short time_sec)									
{
	short time4 = (time_sec/60)/10;						//varaible to know first digit in minutes (0)0:00
	short time3 = (time_sec/60 - time4*10);					//variable to know second digit in minutes 0(0):00
	short time2 = (time_sec - (((time4*10)+time3)*60))/10;			//variable to know first digit in seconds  00:(0)0
	short time1 = (time_sec - (((time4*10)+time3)*60) - (time2*10));	//variable to know second digit in seconds 00:0(0)
	Write_Timer(time4, time3, time2, time1);			        //write timer
	SysTick_Wait(1000);																					//wait 1 second
	while ((time4 || time1 || time2 || time3) && flag_continue)		//while loop to start count down and check if timer ends		
	{
		if (time1 != 0 && flag_continue)
		{
			time1 = time1 - 1;
			Write_Timer(time4, time3, time2, time1);	        //write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
		
		else if((time2 != 0 && time1 == 0) && flag_continue) 
		{
			time2 = time2 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1);		//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}

		else if ((time3 != 0 &&time2 == 0 && time1 == 0) && flag_continue)
		{
			time2 = 5;
			time3 = time3 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1);		//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
		
		else if ((time4 != 0 && time3 == 0 &&time2 == 0 && time1 == 0) && flag_continue)
		{
			time3 = 9;
			time2 = 5;
			time4 = time4 - 1;
			time1 = 9;
			Write_Timer(time4, time3, time2, time1);		//write timer on lcd
			SysTick_Wait(1000);																					//wait 1 second
		}
	}
}
