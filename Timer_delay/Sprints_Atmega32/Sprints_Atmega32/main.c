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
	//Timer_Init(&gstr_Timer0Confing);
	//timer_callback(Timer_OVF_ISR);
	//TCNT0 = 0xB2;
    /* Replace with your application code */
    while (1) 
    {
		GPIO_Read (&PINB, PIN2 ,&Temp);
		for(uinteg32_t i=0;i<230000;i++);/*40ms delay for denouncing */
		//Timer0_delayMs(5000);
		//GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));

		//TCNT0 = 0xB2;  		/* Load TCNT0, count for 10ms */
		//while((TIFR&0x01)==0);  /* Wait for TOV0 to roll over */
		//TIFR = 0x1;  		/* Clear TOV0 flag */
		// GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));

		//TCCR0 = (1<<CS02) | (1<<CS00); /* Timer0, normal mode, /1024 prescalar */
		/*if(Temp)
		{
		  GPIO_Toggle(&PORTB,(PIN7|PIN6|PIN5|PIN4));
		  Temp=RESET;
		}*/

	}
}



		/*while(1)
		{
			GPIO_Read (&PINB, PIN2 ,&Temp);
			if(Temp)
			{		
				count1++;
				count0=0;
			}
			else
			{
				count0++;
				count1=0;
			}
			if(count0 >=30|| count1 >=30)
			{
			    count0=0;
				count1=0;
				break;
			}
		}*/

    

