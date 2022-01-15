/*
 * Timer.c
 *
 * Created: 1/14/2022 9:48:31 PM
 *  Author: Mohamed Salah Taman
 */ 
#include "Timer.h"
void (*gcallBack)(void)=NULL;

void timer_callback(void(*CallBack)(void))
{
	gcallBack =CallBack ;
}
genu_ERROR_t Timer_Init(str_TimerConfing_t *str_TimerConfing)
{
	if(str_TimerConfing == NULL){return TIMER_ERROR_NOK;}
	switch(str_TimerConfing->enu_TimerId)
	{
		case TIMER0:							
			if(str_TimerConfing->enu_TimerCompareMatchInterrupt == ENABLE_INTERRUPT)
			{
				EnableGeneralInterrupt();
				SET_BIT(TIMSK,OCIE0);  	/* Enable Timer0 overflow interrupts */
			}
			else
			{
				CLR_BIT(TIMSK,OCIE0); /*Disable Timer0 Compare match interrupts */
			}
			if(str_TimerConfing->enu_TimerOverFlowInterrupt == ENABLE_INTERRUPT)
			{
				EnableGeneralInterrupt();
				SET_BIT(TIMSK,TOIE0);  	/* Enable Timer0 Compare match interrupts */
				TIMSK=(1<<TOIE0);  	/* Enable Timer0 overflow interrupts */

			}
		    else
			{
				CLR_BIT(TIMSK,TOIE0); /*Disable Timer0 over flow interrupts */
			}
			TCCR0 =(str_TimerConfing->enu_TimerCLK_Source | str_TimerConfing->enu_TimerWaveMode
					|str_TimerConfing->enu_TimerWaveOn_OC_PIN);
			return TIMER_ERROR_OK;
			break;
		case TIMER2:
			if(str_TimerConfing->enu_TimerCompareMatchInterrupt == ENABLE_INTERRUPT)
			{
				EnableGeneralInterrupt();
				SET_BIT(TIMSK,OCIE2);  	/* Enable Timer2 overflow interrupts */
			}
			else
			{
				CLR_BIT(TIMSK,OCIE2); /*Disable Timer2 Compare match interrupts */
			}
			if(str_TimerConfing->enu_TimerOverFlowInterrupt == ENABLE_INTERRUPT)
			{
				EnableGeneralInterrupt();
				SET_BIT(TIMSK,TOIE2);  	/* Enable Timer2 Compare match interrupts */
			}
			else
			{
				CLR_BIT(TIMSK,TOIE2); /*Disable Timer2 over flow interrupts */
			}
			TCCR2 =(str_TimerConfing->enu_TimerCLK_Source | str_TimerConfing->enu_TimerWaveMode
					|str_TimerConfing->enu_TimerWaveOn_OC_PIN);
			return TIMER_ERROR_OK;
			break;
		default:
			return TIMER_ERROR_NOK;
			break;
	}

}

genu_ERROR_t Timer0_delayMs(uinteg32_t u32_delay)
{
	if(u32_delay > 100000){return TIMER_ERROR_NOK;}
	uinteg32_t u32_count=0;
	Timer_SetTimerCountReg(TIMER0,TIMER0_TCNT_INIT_VALUE);
	while((u32_count) <u32_delay)
	{
		if((GET_BIT(TIFR,TOV0)==1))
		{
			SET_BIT(TIFR,TOV0);
			u32_count++;
		}
	}
	return TIMER_ERROR_OK;
	
}
genu_ERROR_t Timer_SetTimerCountReg(enu_TimerId_t enu_TimerId,uinteg8_t u8_TCNT_Value)
{
	if(u8_TCNT_Value >255){return TIMER_ERROR_NOK;}
	switch(enu_TimerId)
	{
		case TIMER0:
			TCNT0=u8_TCNT_Value;
			break;
		case  TIMER2:
			TCNT2=u8_TCNT_Value;
			break;
		default:
			return TIMER_ERROR_NOK;
			break;
	}
	return TIMER_ERROR_OK;
}

void __vector_11(void)
{
	gcallBack();
}
void __vector_10(void)
{
	
}
