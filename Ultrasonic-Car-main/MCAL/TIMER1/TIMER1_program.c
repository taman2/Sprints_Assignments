#include "../../LIB/ATMEGA32_registers.h"
#include "../DIO/DIO_interface.h"
#include "../../LIB/BIT_math.h"
#include "TIMER1_interface.h"
#include "../../ECUAL/NON_BLOCKING_LCD/lcd_interface.h"
#include <math.h>

EN_timerOneInitStatus_t EN_timerOneInitStatus = TIMER1_NOT_INITIALIZED;

uint32_t gu32_overFlowCounts = NULL;

void (*TIMER1_setclbkOverFlow) (void) = NULL_POINTER;
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if(TIMER1_setclbkOverFlow != NULL_POINTER){
		
		TIMER1_setclbkOverFlow();
	}
}

EN_timerOneInitStatus_t TIMER1_init(uint16_t u16_prescale){  //Normal Mode Init 
	
	if (PRESCALE_1 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS10);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_8 == u16_prescale)
	{
	    Ru8_TCCR1B |= (1<<CS11);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_32 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS11) | (1<<CS10);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_64 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS12);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_128 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS12) | (1<<CS10);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_256 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS12) | (1<<CS11);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	else if (PRESCALE_1028 == u16_prescale)
	{
		Ru8_TCCR1B |= (1<<CS12) | (1<<CS11) | (1<<CS10);
		EN_timerOneInitStatus = TIMER1_INITIALIZED;
	}
	return ((uint8_t)(EN_timerOneInitStatus));
}

void TIMER1_stop(void){
	
	Ru8_TCCR1B = 0;
	gu32_overFlowCounts = NULL;
}

EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptEnable(void){
	
	EN_timerOneOverFlowstatus_t EN_status = TIMER1_OF_ENABLED;
	Ru8_TIMSK |= (HIGH << TOIE1);
	return (uint8_t)(EN_status);
}

EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptDisable(void){
	
	EN_timerOneOverFlowstatus_t EN_status = TIMER1_OF_DISABLED;
	Ru8_TIMSK &= ~(HIGH << TOIE1);
	return (uint8_t)(EN_status);
}

EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptEnable(EN_timerOneChannel_t EN_channel){
	
	EN_timerOneOutputCompareAstatus_t EN_status = TIMER1_OCA_ENABLED;
	switch(EN_channel){
		case CHA:
		Ru8_TIMSK |= (HIGH << OCIE1A);
		break;
		
		case CHB:
		Ru8_TIMSK |= (HIGH << OCIE1B);
		break;
	}
	return (uint8_t)(EN_status);
}

EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptDisable(EN_timerOneChannel_t EN_channel){
	
	EN_timerOneOutputCompareAstatus_t EN_status = TIMER1_OCA_DISABLED;
	
	switch(EN_channel){
		case CHA:
		Ru8_TIMSK &= ~(HIGH << OCIE1A);
		break;
		
		case CHB:
		Ru8_TIMSK &= ~(HIGH << OCIE1B);
		break;
	}
	return (uint8_t)(EN_status);
}
EN_timer1DelayStatus_t TIMER1_msdelay(uint16_t mseconds)
{
	static volatile uint32_t u32_ticks;
	static uint8_t u8_timerBusy = FALSE;
	EN_timer1DelayStatus_t EN_delayStatus;
	static EN_timer1DelayStatus_t EN_timer1Status = TIMER1_DELAY_NSTARTED;
	
	if(FALSE == u8_timerBusy)
	{
		Ru8_TCNT1H   = (uint8_t)((BOTTOM) >> 8);
		Ru8_TCNT1L   = (uint8_t)(BOTTOM);
		u8_timerBusy = TRUE;
	}
	if(TIMER1_DELAY_NSTARTED == EN_timer1Status)
	{
		u32_ticks = round(( ( mseconds * PERIODIC_TIME_IN_MS ) / COUNTS_PER_OVF ));
		TIMER1_setclbk(TIMER1_setCountOverFlow);
		TIMER1_OverFlowInterruptEnable();                    //Enabling system interrupt and flag for overflow for timer 1
		TIMER1_init(PRESCALE_8);                             //Prescaler of one that yields 8MHz frequency
		EN_timer1Status  = TIMER1_DELAY_STARTED;
	}
	else if(gu32_overFlowCounts == u32_ticks)
	{
		TIMER1_stop();
		u8_timerBusy        = FALSE;
		EN_timer1Status     = TIMER1_DELAY_NSTARTED;
		EN_delayStatus      = TIMER1_MS_DELAY_FINISHED;
		
	}
	else
	EN_delayStatus   = TIMER1_DELAY_NFINISHED;
	
	return EN_delayStatus;
}


void TIMER1_voidMicroSecDelay(uint16_t u16_usdelay){
	
	uint16_t u16_desiredCounts = BOTTOM + u16_usdelay;
	Ru8_OCR1AH = (uint8_t)((u16_desiredCounts) >> 8);
	Ru8_OCR1AL = (uint8_t)(u16_desiredCounts);
	Ru8_TCNT1H = (uint8_t)((BOTTOM) >> 8);
	Ru8_TCNT1L = (uint8_t)(BOTTOM);
	SET_BIT(Ru8_TIFR,4);
	TIMER1_init(PRESCALE_8);
	while(GET_BIT(Ru8_TIFR,4) != 1);
	TIMER1_stop();
}

void TIMER1_voidStartCounting(void){
	
	Ru8_TCNT1H = (uint8_t)((BOTTOM) >> 8);
	Ru8_TCNT1L = (uint8_t)(BOTTOM);
	TIMER1_setclbk(TIMER1_setCountOverFlow);
	TIMER1_OverFlowInterruptEnable();                    //Enabling system interrupt and flag for overflow for timer 1
	TIMER1_init(PRESCALE_8);
}

void TIMER1_u32getCounts(uint32_t* pu32_clkCounts, uint8_t u8_status){
	
	uint32_t u32_counts = (gu32_overFlowCounts*COUNTS_PER_OVF);
	*(pu32_clkCounts)   = NULL;
	if((TRUE == u8_status)){
		*(pu32_clkCounts) = u32_counts;
		TIMER1_OverFlowInterruptDisable();
		TIMER1_stop();
	}
	else{
	}
}

void TIMER1_setCountOverFlow(void){
	
	Ru8_TCNT1H = (uint8_t)((BOTTOM) >> 8);
	Ru8_TCNT1L = (uint8_t)(BOTTOM);
	gu32_overFlowCounts++;
}

void TIMER1_setclbk(void (*ptrFun)(void)){
	
		TIMER1_setclbkOverFlow = ptrFun;
}
