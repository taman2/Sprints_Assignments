/*
 * Sprints_Atmega32.c
 *
 * Created: 1/9/2022 12:28:39 AM
 * Author : Mohamed Salah Taman
 */ 

#define F_CPU 8000000UL
//#include <avr/io.h>
#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
GPIO_Value Temp=RESET;


int main(void)
{
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	GPIO_Init ( _PORTB,(PIN2),InPut);
	
    while (1) 
    {
		GPIO_Read (&PINB, PIN2 ,&Temp);
		for(uinteg32_t i=0;i<230000;i++);/*40ms delay for denouncing */
	    	if(Temp == SET)
		{
	    		GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
			Temp == RESET;
		}
			
    }
}

    

