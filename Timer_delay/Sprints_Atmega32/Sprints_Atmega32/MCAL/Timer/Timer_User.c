/*
 * Timer_User.c
 *
 * Created: 1/15/2022 8:32:52 PM
 *  Author: Mohamed
 */ 
#include "Timer.h"
str_TimerConfing_t gstr_Timer0Confing=
{
	.enu_TimerId=				TIMER0,
	.enu_TimerWaveMode=			TIMER_NORMAL_MODE,
	.enu_TimerCLK_Source=		   	PRESCALER_64,
	.enu_TimerWaveOn_OC_PIN=		NO_WAVE_ON_OC,
	.enu_TimerOverFlowInterrupt=		DISABLE_INTERRUPT,
	.enu_TimerCompareMatchInterrupt=	DISABLE_INTERRUPT
		
};
str_TimerConfing_t gstr_Timer2Confing=
{
	.enu_TimerId=				TIMER2,
	.enu_TimerWaveMode=			TIMER_NORMAL_MODE,
	.enu_TimerCLK_Source=			PRESCALER_1024,
	.enu_TimerWaveOn_OC_PIN=		NO_WAVE_ON_OC,
	.enu_TimerOverFlowInterrupt=		ENABLE_INTERRUPT,
	.enu_TimerCompareMatchInterrupt=	DISABLE_INTERRUPT
	
};
