#include "tm4c123gh6pm.h"
#include "dio.h"
#include "keypad.h"
#include "bitwise_operation.h"
#include <stdio.h>
#include <stdbool.h>
#include "SystickTimer.h"
#include "lcd.h"
#include "Write_Time.h"
#include <math.h>
#include "dio.h"

#define RED 0x2
#define BLUE 0x4
#define GREEN 0x8

void Buzzer_Init(void)   					//Intilization of  SW3 and Buzzer
{
	SYSCTL_RCGCGPIO_R |= 0x01;           			//activate clock for PORTA
  while((SYSCTL_PRGPIO_R & 0x01)==0){}           		//Check if PORTA is activated or not							
	GPIO_PORTA_LOCK_R = 0x4C4F434B;           		//unlock GPIO of PORTA
	GPIO_PORTA_CR_R |= 0x0C;                   		//Enable GPIOPUR register enable to commit
	GPIO_PORTA_PUR_R |= 0x08;   				//Enable Pull Up SW on PA3	
  GPIO_PORTA_DEN_R |= 0x04;        	  			//Digital Enable A2 of PORTA 
	GPIO_PORTA_DEN_R |= 0x08;        	  		//Digital Enable A3 of PORTA 
  GPIO_PORTA_DIR_R |= 0x04;        	  			//Make A2 of PORTA as ouptut pin
	GPIO_PORTA_PCTL_R &=~ 0x04; 				//Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &=~ 0x04;        				//Disable analog function on A2 of PORTA
	GPIO_PORTA_AFSEL_R &=~ 0x04;        			//Disable alternate function on A2 of PORTA
	GPIO_PORTA_PCTL_R &=~ 0x08 ; 				// Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &=~ 0x08;        				//Disable analog function on A3 of PORTA
	GPIO_PORTA_AFSEL_R &=~ 0x08;        			//Disable alternate function on A3 of PORTA
}

//Turn ON, Turn OFF Buzzer
void Buzzer_Output(unsigned char data)							
{
  if(data)
  {
    GPIO_PORTA_DATA_R |= 0x04;
  }
  else
  {
    GPIO_PORTA_DATA_R &=~ 0x04;
  }
}


void Timer(void)
{
  KeyPad_Init();
  Buzzer_Init();
  LCD_init();
  LCD_Cmd(moveCursorRight);
  LCD_Cmd(clear_display);
  LCD_Write("Enter Time");
  char time[4] = {'0','0','0','0'};
  int count1 = 0;
  char exit = 0;
  char input1;
  int fTime = 0;
  char str[10];
   DIO_PORTFinit();
   fTime = 0;
   
  while(!exit){
    input1 = KeyPad_Read();
     while(!exit)
     {
       if ((GPIO_PORTF_DATA_R & 0x01)==0){
                while(((GPIO_PORTF_DATA_R & 0x01)==0));
                if(input1 == 'A')
                  fTime = fTime + 1;
                else if(input1 == 'B')
                  fTime = fTime + 60;
                printf("%d", fTime);
                LCD_Cmd(moveCursorRight);
  LCD_Cmd(clear_display);
                 sprintf(str,"%d",fTime); 
                 LCD_String(str);
        }
     
     if ((GPIO_PORTF_DATA_R & 0x10)==0){ // switch2 pressed
               Start_timer(fTime); // functions takes time in seconds and starts going from up to down
                 fTime = 0;
                 GPIO_PORTF_DATA_R |= 0x02; // red led is on
                 Buzzer_Output(1); // buzzer is on
                 SysTick_Wait(3000);
                 GPIO_PORTF_DATA_R = 0; // red led is off
                 exit = 1; // returns to idle
                 Buzzer_Output(0); // buzzer is off
        }
     }
    
    
  }
}


void StopWatch(void)
{
  KeyPad_Init(); // Keypad initialization
  LCD_init();   // LCD initialization
  LCD_Cmd(moveCursorRight); // Mover cursor to right in LCD
  LCD_Cmd(clear_display); // Clear LCD display
  Write_Timer_zero();
  char input2;
  char input3;
  // intialize times for to display on LCD later
  short t1=0;
  short t2=0;
  short t3=0;
  short t4=0;
  
  char exit = 0;
  while(!exit){
    input2 = KeyPad_Read();
    DIO_PORTFinit(); //portF initialization
    LCD_Cmd(moveCursorRight);
    LCD_Cmd(clear_display);
    Write_Timer_zero(); //make the screen has (00:00)
    if ( input2 == 'A'){ // Starts ticking of stopwatch
      t1=0;
      t2=0;
      t3=0;
      t4=0;
      Write_Timer_zero();
      for (short i=0; i < 6 && !exit ;i++){     // nested for loop for minutes here is for (0)0:00
        for (short j=0; j < 10 && !exit; j++){  // nested for loop for minutes here is for 0(0):00
          for (short k=0; k < 6 && !exit ; k++){        // nested for loop for minutes here is for 00:(0)0
            for (short m=0; m < 10 && !exit ; m++){     // nested for loop for minutes here is for 00:0(0)
              t3 = j;
              t2 = k;
              t4 = m;
              if(j == 9 && k== 5 && m==9 && t1 !=5){
                t1 = t1+1;
              }
              if ((GPIO_PORTF_DATA_R & 0x01)==0){ //Stops ticking
                input3 = KeyPad_Read(); // input in keypad makes it continue
                 
              }
              if ((GPIO_PORTF_DATA_R & 0x10)==0){ // Reset
                Write_Timer_zero();
                t1=0;
                t2=0;
                t3=0;
                t4=0;
                i = 0;
                j = 0;
                k = 0;
                m = 0;
                input3 = KeyPad_Read();
                if(input3 == 'B') // If you reset then choose B in keypad you return to idle
                {
                  exit = 1;
                  LCD_Cmd(moveCursorRight);
                   LCD_Cmd(clear_display);
                }
              }
              Write_Timer(t1,t3,t2,t4); //give all the times to the function that prints them on the screen
              SysTick_Wait(1000); // systick timer function used to wait in milliseconds

            }
          }
        }
      }
    }

  }
}

void Calc(void)
{
  KeyPad_Init(); // Keypad initialization
 LCD_init(); // LCD initialization
 DIO_PORTFinit(); //portF initialization
 LCD_Cmd(moveCursorRight); // Mover cursor to right in LCD
 LCD_Cmd(clear_display); // Clear LCD display
 char Op = 'A'; 
 char dummy = 'n';
 bool GivenOP = false; // To check if an operation is used
 int countX = 0;
 int countY = 0;
 int countZ = 0;
 char strZ[10];
 char str1[30];
 char strX[10];
 char strY[10];
 int x = 0;
 int y = 0;
 int z = 0;
 char input = ',';
  while(input != 'D') {
    
    input = ',';
    input = KeyPad_Read(); // read keypad input
    delay(50);
    if (input == 'A' ||input == 'B' || input == 'C' || input == '*') { // Choose one of the operations
      Op = input;
       dummy = 'y';
      switch (Op)
      {
       
        case 'A':
          LCD_Cmd(moveCursorRight);
          LCD_Cmd(clear_display);
          LCD_Data('+'); //display character '+'
          break;
          
        case 'B':
          LCD_Cmd(moveCursorRight);
          LCD_Cmd(clear_display);
          LCD_Data('-'); //display character '-'
          
          break;
          
        case 'C':
          LCD_Cmd(moveCursorRight);
          LCD_Cmd(clear_display);
          LCD_Data('/'); //display character '/'
          
          break;
          
      case '*':
          LCD_Cmd(moveCursorRight);
          LCD_Cmd(clear_display);
          LCD_Data('*'); //display character '*'
          
          break;
          
        default:
          break;
      }
      GivenOP = true;
      
      
    }
    
    else if(input == 'D'){
      LCD_Cmd(moveCursorRight);
      LCD_Cmd(clear_display);
      LCD_Data('='); //display character '='
      delay(50000);
      LCD_Cmd(moveCursorRight);
      LCD_Cmd(clear_display);
      for (int i= 0; i < countX; i++){
              x = x + (((strX[i]) - 48)*(pow(10,countX -i - 1))); // put value in integer in y
      }
      printf("%d \n",x);
      for (int i= 0; i < countY; i++){
              y = y + (((strY[i]) - 48)*(pow(10,countY -i - 1))); // put value in integer in y
      }
      printf("%d \n",y);
      switch (Op)
      {
        case 'A':  // Add
          z = x + y;
          printf("%d", z);
          break;
      
      
        case 'B': // Subtract
        z = x - y;
        printf("%d", z);
        break;
      
      
        case 'C': // Divide
          if(y != 0){
          z = x / y;    // in case y = 0 pending
          }
          printf("%d", z);
          break;
      
        case '*': // Multiply
        z = x * y;
        printf("%d", z);
        break;
        
      default:
        break;
      }
      
      LCD_Cmd(moveCursorRight);
      LCD_Cmd(clear_display);
      sprintf(strZ,"%d",z); // Switch z to string in strZ
      LCD_String(strZ); //display string strZ
      // After displaying on screen the result it returns to idle
      for (int i=0; i<10; i++){
        strX[i] = 0;
        strY[i] = 0;
        x = 0;
        y = 0;
        z = 0;
        countX = 0;
        countY = 0;
        countZ = 0;
        dummy = 'n';
      }
      
    }
    

   
    else if (input >= '0' && input <= '9'){ // Check that the input is an integer

      if(! GivenOP && dummy == 'n') { // Check if you pressed an Operation button or not and dummy character to prevent infinite looping
       if(countX == 0)
       {
         LCD_Cmd(moveCursorRight);
         LCD_Cmd(clear_display);
       }
        strX[countX] = input;
        LCD_Data(strX[countX]); // Display character that is the input No. on keypad
        countX++;
        delay(50);
        
        printf("\n");
        }
        

      else if (input != 'D') { 
        if(countY == 0)
       {
         LCD_Cmd(moveCursorRight);
          LCD_Cmd(clear_display);
       }
        strY[countY] = input;
        LCD_Data(strY[countY]); // Display character that is the input No. on keypad
        countY++;
        GivenOP = false; 
        delay(50);
        printf("\n");
      }

      
      
    }
    
  }
}

int main()
{
  KeyPad_Init(); //// Keypad initialization
   LCD_init(); // LCD initialization
   
  char input;
  while(1)
  {
    LCD_Cmd(moveCursorRight);
    LCD_Cmd(clear_display);
    input = KeyPad_Read();
    LCD_Cmd(moveCursorRight);
    LCD_Cmd(clear_display);
    switch(input)
    {
  case 'A':
    printf("In Time");
    while((GPIO_PORTF_DATA_R & 0x01)==1); // switch1 pressed after pressing 'A'
    Timer(); // Call timer function
    break;
  case 'B': // pressing 'B'
    StopWatch(); // Call stopwatch function
    break;
  case 'C':
    while((GPIO_PORTF_DATA_R & 0x01)==1); // switch1 pressed after pressing 'C'
    Calc(); // Call calculator function
    break;
    }
  }
}
