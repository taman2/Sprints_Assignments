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
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KeyPad/KeyPad.h"


int main(void)
{
	GPIO_Value Temp=RESET;
	uinteg16_t X=5;
	LCD_Init();
	KeyPad_Init();
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	GPIO_Init ( _PORTB,(PIN2),InPut);
	Timer_Init(&gstr_Timer0Confing);
	ADC_Init();
	X=(int)ADC_read(ADC_PRESCALER_128,ADC_VREF_AVCC,ADC0);
    LCD_String("Temperature:");
    LCD_Integ((int)X);
    while (1) 
    {
	  
	  
	}
}

