/*
 * Sprints_Atmega32.c
 *
 * Created: 1/9/2022 12:28:39 AM
 * Author : Mohamed Salah Taman
 */ 
#define F_CPU 8000000UL

#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
#include "delay.h"
#include "../HAL/KeyPad/KeyPad.h"
#include "../HAL/LCD/LCD.h"
GPIO_Value Temp=RESET;


int main(void)
{
	uinteg16_t X=0;
	LCD_Init();
	KeyPad_Init();
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	GPIO_Init ( _PORTB,(PIN2),InPut);
	Timer_Init(&gstr_Timer0Confing);
    LCD_String("key");

    while (1) 
    {
	   X=Key_KeyPressed();
	   if(X<20)
	   {
		  LCD_Clear();
	  	  LCD_Int((int)X);
		   X=20;
	   }
	  
	}
}

