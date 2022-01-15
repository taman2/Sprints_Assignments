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
GPIO_Value Temp=RESET;

void Timer_OVF_ISR(void)
{
	static uinteg32_t count1=0;
	static uinteg32_t count2=5;
	count1++;
	if(count1 > 30 && count2==5)
	{
		GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
		count1=0;
		count2=3;
	}
	if(count1 >50 && count2==3)
	{
		GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
		count1=0;
		count2=5;
	}
}

int main(void)
{
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	GPIO_Init ( _PORTB,(PIN2),InPut);
	Timer_Init(&gstr_Timer0Confing);
	timer_callback(Timer_OVF_ISR);

    while (1) 
    {
		/*GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
		Timer0_delayMs(300);
		GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
		Timer0_delayMs(500);*/

	}
}

