/*
 * Timer_User.c
 *
 * Created: 1/15/2022 8:32:52 PM
 *  Author: Mohamed
 */ 
#include "Timer.h"
str_TimerConfing_t gstr_Timer0Confing=
{
	.enu_TimerId=						TIMER0,
	.enu_TimerWaveMode=					TIMER_NORMAL_MODE,
	.enu_TimerCLK_Source=				PRESCALER_64,
	.enu_TimerWaveOn_OC_PIN=			NO_WAVE_ON_OC,
	.enu_TimerOverFlowInterrupt=		DISABLE_INTERRUPT,
	.enu_TimerCompareMatchInterrupt=	DISABLE_INTERRUPT
		
};
str_TimerConfing_t gstr_Timer2Confing=
{
	.enu_TimerId=						TIMER2,
	.enu_TimerWaveMode=					TIMER_NORMAL_MODE,
	.enu_TimerCLK_Source=				PRESCALER_1024,
	.enu_TimerWaveOn_OC_PIN=			NO_WAVE_ON_OC,
	.enu_TimerOverFlowInterrupt=		ENABLE_INTERRUPT,
	.enu_TimerCompareMatchInterrupt=	DISABLE_INTERRUPT
	
};
void Timer_OVF_ISR(void)
{
	static uinteg32_t count1=0;
	static uinteg32_t count2=3;
	if(count1 >= 300 && count2==3)
	{
		GPIO_Write(&PORTB,(PIN7|PIN6|PIN5|PIN4),RESET);
		count1=0;
		count2=5;
	}
	else if(count1 >=500 && count2==5)
	{
		GPIO_Write(&PORTB,(PIN7|PIN6|PIN5|PIN4),SET);
		count1=0;
		count2=3;
	}
	Timer_SetTimerCountReg(TIMER0,TIMER0_TCNT_INIT_VALUE);
	count1++;
}
