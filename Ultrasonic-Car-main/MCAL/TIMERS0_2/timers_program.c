/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: Timer0 , Timer 2
 *  Layer arch : MCAL
 *  Created on: Feb 9, 2022
 *  Modified on : Jan 15, 2022
 *	version:4
 *
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/atmega32_registers.h"
#include "../TIMERS0_2/timers_config.h"
#include "../TIMERS0_2/timers_interface.h"
#include "../TIMERS0_2/timers_private.h"
//timer 0 ISR(global pointer to functions)
static void (*Timer0CompareMatchSetCallBackISR)(void) = NULL_POINTER; 
static void (*Timer0OverFlowSetCallBackISR)(void) = NULL_POINTER; 
//timer 2 ISR(global pointer to functions)
static void (*Timer2CompareMatchSetCallBackISR)(void) = NULL_POINTER;
static void (*Timer2OverFlowSetCallBackISR)(void) = NULL_POINTER;

//timer 0 flags(global variables )
uint8_t gu8_timer0FinishIntWaitFlag = u8_WAITING_FIRST_INT_WAIT_NOT_BEGIN ;
static uint8_t gu8_timer0FlagIfUsed = u8_TIMER0_FLAG_NOT_USED ;
static uint64_t gu64_timer0IntWaitcounter = u8_INTIAL_COUNTER_VAL ;

//timer 2 flags(global variables )
uint8_t gu8_timer2FinishIntWaitFlag = u8_WAITING_FIRST_INT_WAIT_NOT_BEGIN ;
static uint8_t gu8_timer2FlagIfUsed = u8_TIMER2_FLAG_NOT_USED ;
static uint64_t gu64_timer2IntWaitcounter = u8_INTIAL_COUNTER_VAL ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


void TIMER0_voidInit(void)
{
	#if	u8_TIMER0_MODE_CONFIG==u8_NORMAL_MODE
		CLR_BIT(Ru8_TCCR0,u8_WGM01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_WGM01_BIT) ;
		CLR_BIT(Ru8_TCCR0,Ru8_TCCR2) ;
	#elif u8_TIMER0_MODE_CONFIG==u8_CTC_MODE
		CLR_BIT(Ru8_TCCR0,u8_WGM00_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_WGM01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_FOC0_BIT) ;
	#else
		#error "error in prebuild timer0 config"
	#endif
	
	
	
	#if	u8_TIMER0_MODE_CONFIG==u8_NORMAL_MODE||u8_TIMER0_MODE_CONFIG==u8_CTC_MODE
		#if u8_TIMER0_COMP_MATCH_NON_PWM_CONFIG==u8_OC0_DISCONNECTED
			CLR_BIT(Ru8_TCCR0,u8_COM00_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_COM01_BIT) ;
		#elif u8_TIMER0_COMP_MATCH_NON_PWM_CONFIG==u8_TOGGLE_ON_COMPARE_MATCH
			SET_BIT(Ru8_TCCR0,u8_COM00_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_COM01_BIT) ;
		#elif u8_TIMER0_COMP_MATCH_NON_PWM_CONFIG==u8_OC0_CLEAR_ON_COMPARE_MATCH
			CLR_BIT(Ru8_TCCR0,u8_COM00_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_COM01_BIT) ;
		#elif u8_TIMER0_COMP_MATCH_NON_PWM_CONFIG==u8_OC0_SET_ON_COMPARE_MATCH
			SET_BIT(Ru8_TCCR0,u8_COM00_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_COM01_BIT) ;
		#else 
			#error "oc0 config error "
		#endif
		
	#else 
		#error "error in prebuild timer0 config"
	#endif
	
	
	#if u8_TIMER0_1_CLOCK_SELECT==u8_NO_CLK_TIMER_STOP
		CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_INTERNAL_CLK_NO_PRE
		CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_8
		CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_64
		CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_256
		SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_1024
		SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_EXTERNAL_CLK_FALLING
		SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#elif u8_TIMER0_1_CLOCK_SELECT==u8_EXTERNAL_CLK_RISING
		SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
		SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
	#else
		#error "wrong clock select config"
	#endif

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void TIMER2_voidInit(void)
{
	#if	u8_TIMER2_MODE_CONFIG==u8_NORMAL_MODE
		CLR_BIT(Ru8_TCCR2,u8_WGM20_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_WGM21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_FOC2_BIT) ;
	#elif u8_TIMER2_MODE_CONFIG==u8_CTC_MODE
		CLR_BIT(Ru8_TCCR2,u8_WGM20_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_WGM21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_FOC2_BIT) ;
	#else
		#error "error in prebuild timer2 config"
	#endif



	#if	u8_TIMER2_MODE_CONFIG==u8_NORMAL_MODE||u8_TIMER2_MODE_CONFIG==u8_CTC_MODE
		#if u8_TIMER2_COMP_MATCH_NON_PWM_CONFIG==u8_OC2_DISCONNECTED
			CLR_BIT(Ru8_TCCR2,u8_COM20_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_COM21_BIT) ;
		#elif u8_TIMER2_COMP_MATCH_NON_PWM_CONFIG==u8_TOGGLE_ON_COMPARE_MATCH
			SET_BIT(Ru8_TCCR2,u8_COM20_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_COM21_BIT) ;
		#elif u8_TIMER2_COMP_MATCH_NON_PWM_CONFIG==u8_OC2_CLEAR_ON_COMPARE_MATCH
			CLR_BIT(Ru8_TCCR2,u8_COM20_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_COM21_BIT) ;
		#elif u8_TIMER2_COMP_MATCH_NON_PWM_CONFIG==u8_OC2_SET_ON_COMPARE_MATCH
			SET_BIT(Ru8_TCCR2,u8_COM20_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_COM21_BIT) ;
		#else
			#error "oc0 config error "
		#endif

	#else
		#error "error in prebuild timer2 config"
	#endif


	#if u8_TIMER2_CLOCK_SELECT==u8_NO_CLK_TIMER_STOP
		CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_INTERNAL_CLK_NO_PRE
		CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_8
		CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_64
		CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_256
		SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_INTERNAL_CLK_PRE_1024
		SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_EXTERNAL_CLK_FALLING
		SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#elif u8_TIMER2_CLOCK_SELECT==u8_EXTERNAL_CLK_RISING
		SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
		SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
	#else
		#error "wrong clock select config"
	#endif

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMER0_u8StartWithclockAndPrescalerSelect(uint8_t u8_preScallerVal) 
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	switch(u8_preScallerVal)
	{
		case u8_INTERNAL_CLK_NO_PRE:
			CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ; 
		case u8_INTERNAL_CLK_PRE_8:
			CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ; 
		case u8_INTERNAL_CLK_PRE_64:
			CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ;
		case u8_INTERNAL_CLK_PRE_256:
			SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ; 
		case u8_INTERNAL_CLK_PRE_1024:
			SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ;
		case u8_EXTERNAL_CLK_FALLING : 
			SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ;
		case u8_EXTERNAL_CLK_RISING:
			SET_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
			SET_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
			break ; 
		
		default : u8_ErrorFlag = u8_NOK ; 
		break ;
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMER2_u8StartWithclockAndPrescalerSelect(uint8_t u8_preScallerVal)
{
	uint8_t u8_ErrorFlag = u8_OK ;
	switch(u8_preScallerVal)
	{
		case u8_INTERNAL_CLK_NO_PRE:
			CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_INTERNAL_CLK_PRE_8:
			CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_INTERNAL_CLK_PRE_64:
			CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_INTERNAL_CLK_PRE_256:
			SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_INTERNAL_CLK_PRE_1024:
			SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_EXTERNAL_CLK_FALLING :
			SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;
		case u8_EXTERNAL_CLK_RISING:
			SET_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
			SET_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
			break ;

		default : u8_ErrorFlag = u8_NOK ;
		break ;
	}
	return u8_ErrorFlag ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void TIMER0_voidstop(void)
{
	CLR_BIT(Ru8_TCCR0,u8_CS02_BIT) ;
	CLR_BIT(Ru8_TCCR0,u8_CS01_BIT) ;
	CLR_BIT(Ru8_TCCR0,u8_CS00_BIT) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void TIMER2_voidstop(void)
{
	CLR_BIT(Ru8_TCCR2,u8_CS22_BIT) ;
	CLR_BIT(Ru8_TCCR2,u8_CS21_BIT) ;
	CLR_BIT(Ru8_TCCR2,u8_CS20_BIT) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMERS_u8ClearIntFlag(uint8_t u8_wantedIntClearFlag)
{
		uint8_t u8_ErrorFlag = u8_OK ; 
	switch(u8_wantedIntClearFlag)
	{
		case u8_TIMER0_OVER_FLOW			: SET_BIT(Ru8_TIFR,u8_TOV0_BIT) ;
											  break ;
		case u8_TIMER0_COMPARE_ON_MATCH		: SET_BIT(Ru8_TIFR,u8_OCF0_BIT) ;
											  break ;
		case u8_TIMER2_OVER_FLOW			: SET_BIT(Ru8_TIFR,u8_TOV2_BIT) ;
											  break ;
		case u8_TIMER2_COMPARE_ON_MATCH		: SET_BIT(Ru8_TIFR,u8_OCF2_BIT) ;
											  break ;
		default								: u8_ErrorFlag = u8_NOK ;
											  break ; 
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMERS_u8GetIntFlag(uint8_t u8_wantedIntClearFlag,uint8_t* pu8_retturnIntFlag)
{
		uint8_t u8_ErrorFlag = u8_OK ; 
	switch(u8_wantedIntClearFlag)
	{
		case u8_TIMER0_OVER_FLOW			: (*pu8_retturnIntFlag) = GET_BIT(Ru8_TIFR,u8_TOV0_BIT) ;
											  break ;
		case u8_TIMER0_COMPARE_ON_MATCH		: (*pu8_retturnIntFlag) = GET_BIT(Ru8_TIFR,u8_OCF0_BIT) ;
											  break ;
		case u8_TIMER2_OVER_FLOW			: (*pu8_retturnIntFlag) = GET_BIT(Ru8_TIFR,u8_TOV2_BIT) ;
											  break ;
		case u8_TIMER2_COMPARE_ON_MATCH		: (*pu8_retturnIntFlag) = GET_BIT(Ru8_TIFR,u8_OCF2_BIT) ;
											  break ;
		default								: u8_ErrorFlag = u8_NOK ;
											  break ; 
	}
	return u8_ErrorFlag ; 
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMERS_u8IntModesEn(uint8_t u8_wantedIntModeEn)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	switch(u8_wantedIntModeEn)
	{
		case u8_TIMER0_OVER_FLOW			:  SET_BIT(Ru8_TIFR,u8_TOV0_BIT) ;
											   SET_BIT(Ru8_TIMSK,u8_TOIE0_BIT);
											   break ; 
		case u8_TIMER0_COMPARE_ON_MATCH		:  SET_BIT(Ru8_TIFR,u8_OCF0_BIT) ;
											   SET_BIT(Ru8_TIMSK,u8_OCIE0_BIT);
											   break ;
		case u8_TIMER2_OVER_FLOW			:  SET_BIT(Ru8_TIFR,u8_TOV2_BIT) ;
											   SET_BIT(Ru8_TIMSK,u8_TOIE2_BIT);
											   break ;
		case u8_TIMER2_COMPARE_ON_MATCH		:  SET_BIT(Ru8_TIFR,u8_OCF2_BIT) ;
											   SET_BIT(Ru8_TIMSK,u8_OCIE2_BIT);
											   break ;
		default 							:  u8_ErrorFlag = u8_NOK ; 
											   break ; 
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMERS_u8IntModesDis(uint8_t u8_wantedIntModeDis)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	switch(u8_wantedIntModeDis)
	{
		case u8_TIMER0_OVER_FLOW			:  CLR_BIT(Ru8_TIMSK,u8_TOIE0_BIT);
											   break ; 
		case u8_TIMER0_COMPARE_ON_MATCH		:  CLR_BIT(Ru8_TIMSK,u8_OCIE0_BIT);
											   break ;
		case u8_TIMER2_OVER_FLOW			:  CLR_BIT(Ru8_TIMSK,u8_TOIE2_BIT);
											   break ;
		case u8_TIMER2_COMPARE_ON_MATCH		:  CLR_BIT(Ru8_TIMSK,u8_OCIE2_BIT);
											   break ;
		default 							:  u8_ErrorFlag = u8_NOK ; 
											   break ; 
	}
	return u8_ErrorFlag ; 
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t Timer0_u8setOverFlowRegTicksBeforeOV(uint8_t u8_wantedTicksBeforeOV)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	uint8_t u8_SetTimer0CounterReg ; 
	if(u8_wantedTicksBeforeOV<=u8_MAX_8BIT_REG_HOLD)
	{
		u8_SetTimer0CounterReg = u8_MAX_8BIT_REG_HOLD-u8_wantedTicksBeforeOV ; 
		Ru8_TCNT0=u8_SetTimer0CounterReg ;
	}
	else 
	{
		u8_ErrorFlag = u8_NOK ; 
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t Timer2_u8setOverFlowRegTicksBeforeOV(uint8_t u8_wantedTicksBeforeOV)
{
	uint8_t u8_ErrorFlag = u8_OK ;
	uint8_t u8_SetTimer2CounterReg ;
	if(u8_wantedTicksBeforeOV<=u8_MAX_8BIT_REG_HOLD)
	{
		u8_SetTimer2CounterReg = u8_MAX_8BIT_REG_HOLD-u8_wantedTicksBeforeOV ;
		Ru8_TCNT2=u8_SetTimer2CounterReg ;
	}
	else
	{
		u8_ErrorFlag = u8_NOK ;
	}
	return u8_ErrorFlag ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t Timer0_u8setCompareRegTicksBeforeOV(uint8_t u8_wantedTicksToCompare)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	if(u8_wantedTicksToCompare<=u8_MAX_8BIT_REG_HOLD)
	{
		Ru8_OCR0 = u8_wantedTicksToCompare ;
	}
	else 
	{
		u8_ErrorFlag = u8_NOK ; 
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t Timer2_u8setCompareRegTicksBeforeOV(uint8_t u8_wantedTicksToCompare)
{
	uint8_t u8_ErrorFlag = u8_OK ;
	if(u8_wantedTicksToCompare<=u8_MAX_8BIT_REG_HOLD)
	{
		Ru8_OCR2 = u8_wantedTicksToCompare ;
	}
	else
	{
		u8_ErrorFlag = u8_NOK ;
	}
	return u8_ErrorFlag ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t TIMER0_u8setCallBack(uint8_t u8_wantedISRModeToSet,void(*ISRFuncToSet)(void))
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	if(ISRFuncToSet!=NULL_POINTER)
	{
		switch(u8_wantedISRModeToSet)
		{
			case u8_TIMER0_OVER_FLOW			:  Timer0OverFlowSetCallBackISR = ISRFuncToSet ; 
												   break ; 
			case u8_TIMER0_COMPARE_ON_MATCH		:  Timer0CompareMatchSetCallBackISR = ISRFuncToSet ; 
											       break ;
			default 							:  u8_ErrorFlag = u8_NOK ; 
											       break ; 
		}
	}
	else 
	{
		u8_ErrorFlag = u8_NOK ; 
	}
	return u8_ErrorFlag ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t TIMER2_u8setCallBack(uint8_t u8_wantedISRModeToSet,void(*ISRFuncToSet)(void))
{
	uint8_t u8_ErrorFlag = u8_OK ;
	if(ISRFuncToSet!=NULL_POINTER)
	{
		switch(u8_wantedISRModeToSet)
		{
			case u8_TIMER2_OVER_FLOW			:  Timer2OverFlowSetCallBackISR = ISRFuncToSet ;
												   break ;
			case u8_TIMER2_COMPARE_ON_MATCH		:  Timer2CompareMatchSetCallBackISR = ISRFuncToSet ;
											       break ;
			default 							:  u8_ErrorFlag = u8_NOK ;
											       break ;
		}
	}
	else
	{
		u8_ErrorFlag = u8_NOK ;
	}
	return u8_ErrorFlag ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void __vector_10 (void)      __attribute__((signal));
void __vector_10 (void)
{
	if(Timer0CompareMatchSetCallBackISR!=NULL_POINTER)
	{
		Timer0CompareMatchSetCallBackISR();
	}
	else 
	{
		//do nothing
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void __vector_11 (void)      __attribute__((signal));
void __vector_11 (void)
{
	if(Timer0OverFlowSetCallBackISR!=NULL_POINTER)
	{
		Timer0OverFlowSetCallBackISR() ;
	}
	else 
	{
		//do nothing
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void __vector_4 (void)      __attribute__((signal));
void __vector_4 (void)
{
	if(Timer2CompareMatchSetCallBackISR!=NULL_POINTER)
	{
		Timer2CompareMatchSetCallBackISR();
	}
	else
	{
		//do nothing
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void __vector_5 (void)      __attribute__((signal));
void __vector_5 (void)
{
	if(Timer2OverFlowSetCallBackISR!=NULL_POINTER)
	{
		Timer2OverFlowSetCallBackISR() ;
	}
	else
	{
		//do nothing
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//busy wait with prescaller 8
uint8_t TIMER0_u8BusyWaitMS(uint32_t u32_BusyTimeInMilliSec)
{
	uint8_t u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_NOT_USED ;
	if(gu8_timer0FlagIfUsed== u8_TIMER0_FLAG_NOT_USED)
	{
		volatile uint64_t u64_BusyWaitcounter = u8_INTIAL_COUNTER_VAL ;
		volatile uint8_t u8_CheckCompareFlag ;
		TIMERS_u8IntModesDis(u8_TIMER0_OVER_FLOW) ;
		TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ;
		TIMER0_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		TIMERS_u8ClearIntFlag(u8_TIMER0_COMPARE_ON_MATCH) ;
		Timer0_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer0_u8setOverFlowRegTicksBeforeOV(u8_MAX_TIMER0_COUNTS) ;
		while(u64_BusyWaitcounter <=(uint64_t)(u32_BusyTimeInMilliSec*u8_NUMBER_OF_COUNTS_TO_COMP_1mS_with_8_pre))
		{
			TIMERS_u8GetIntFlag(u8_TIMER0_COMPARE_ON_MATCH,(uint8_t*)(&u8_CheckCompareFlag)) ;
			if(u8_CheckCompareFlag == u8_Flag_RAISED )
			{
				TIMERS_u8ClearIntFlag(u8_TIMER0_COMPARE_ON_MATCH) ;
				u64_BusyWaitcounter++ ;
			}
		}
	}
	else
	{
		u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_USED ;
	}
	return u8_Timer0FlagIfUsed ;
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//busy wait with prescaller 8
uint8_t TIMER0_u8BusyWaitUS(uint32_t u32_BusyTimeInMicroSec)
{
	uint8_t u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_NOT_USED ;
	if(gu8_timer0FlagIfUsed== u8_TIMER0_FLAG_NOT_USED)
	{
		volatile uint32_t u32_BusyWaitcounter = u8_INTIAL_COUNTER_VAL ;
		volatile uint8_t u8_CheckCompareFlag ;
		TIMERS_u8IntModesDis(u8_TIMER0_OVER_FLOW) ;
		TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ;
		TIMER0_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		TIMERS_u8ClearIntFlag(u8_TIMER0_COMPARE_ON_MATCH) ;
		Timer0_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer0_u8setOverFlowRegTicksBeforeOV(u8_MAX_TIMER0_COUNTS) ;
		while(u32_BusyWaitcounter <=u32_BusyTimeInMicroSec)
		{
			TIMERS_u8GetIntFlag(u8_TIMER0_COMPARE_ON_MATCH,(uint8_t*)(&u8_CheckCompareFlag)) ;
			if(u8_CheckCompareFlag == u8_Flag_RAISED )
			{
				TIMERS_u8ClearIntFlag(u8_TIMER0_COMPARE_ON_MATCH) ;
				u32_BusyWaitcounter++ ;
			}
		}
	}
	else
	{
		u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_USED ;
	}
	return u8_Timer0FlagIfUsed ;
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMER0_u8InterruptWait(uint32_t u32_interruptTimeInMilliSec)
{
	uint8_t u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_NOT_USED ;
	if(gu8_timer0FlagIfUsed==u8_TIMER0_FLAG_NOT_USED &&gu8_timer0FinishIntWaitFlag != u8_BEGIN_INTERRUPT_WAITING )
	{
		gu64_timer0IntWaitcounter = (uint64_t)(u32_interruptTimeInMilliSec*u8_NUMBER_OF_COUNTS_TO_COMP_1mS_with_8_pre) ;
		Timer0_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer0_u8setOverFlowRegTicksBeforeOV(u8_MAX_TIMER0_COUNTS) ;
		gu8_timer0FlagIfUsed = u8_TIMER0_FLAG_USED ;
		TIMERS_u8IntModesEn(u8_TIMER0_COMPARE_ON_MATCH);
		TIMER0_u8setCallBack(u8_TIMER0_COMPARE_ON_MATCH,TIMER0_voidIntWaitControlFlagCount) ;
		TIMER0_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		gu8_timer0FinishIntWaitFlag = u8_BEGIN_INTERRUPT_WAITING ;

	}
	else
	{
		u8_Timer0FlagIfUsed = u8_TIMER0_FLAG_USED ;
	}
	return u8_Timer0FlagIfUsed ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t TIMER0_u8GetIntWaitStatus(void)
{
	return gu8_timer0FinishIntWaitFlag  ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

static void TIMER0_voidIntWaitControlFlagCount(void)
{

	if(gu8_timer0FlagIfUsed==u8_TIMER0_FLAG_USED&&gu64_timer0IntWaitcounter > u8_INTIAL_COUNTER_VAL)
	{
		gu64_timer0IntWaitcounter-- ;
	}
	else
	{
		gu8_timer0FlagIfUsed = u8_TIMER0_FLAG_NOT_USED ;
		gu8_timer0FinishIntWaitFlag = u8_FINISH_INTERRUPT_WAITING ;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//busy wait with prescaller 8
uint8_t TIMER2_u8BusyWaitMS(uint32_t u32_BusyTimeInMilliSec)
{
	uint8_t u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_NOT_USED ;
	if(gu8_timer2FlagIfUsed== u8_TIMER2_FLAG_NOT_USED)
	{
		volatile uint64_t u64_BusyWaitcounter = u8_INTIAL_COUNTER_VAL ;
		volatile uint8_t u8_CheckCompareFlag ;
		TIMERS_u8IntModesDis(u8_TIMER2_OVER_FLOW) ;
		TIMERS_u8IntModesDis(u8_TIMER2_COMPARE_ON_MATCH) ;
		TIMER2_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		TIMERS_u8ClearIntFlag(u8_TIMER2_COMPARE_ON_MATCH) ;
		Timer2_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer2_u8setOverFlowRegTicksBeforeOV(u8_INTIALIZING_TIMER2_COUNTER) ;
		while(u64_BusyWaitcounter <=(uint64_t)(u32_BusyTimeInMilliSec*u8_NUMBER_OF_COUNTS_TO_COMP_1mS_with_8_pre))
		{
			TIMERS_u8GetIntFlag(u8_TIMER2_COMPARE_ON_MATCH,(uint8_t*)(&u8_CheckCompareFlag)) ;
			if(u8_CheckCompareFlag == u8_Flag_RAISED )
			{
				TIMERS_u8ClearIntFlag(u8_TIMER2_COMPARE_ON_MATCH) ;
				u64_BusyWaitcounter++ ;
			}
		}
	}
	else
	{
		u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_USED ;
	}
	return u8_Timer2FlagIfUsed ;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//busy wait with prescaller 8
uint8_t TIMER2_u8BusyWaitUS(uint32_t u32_BusyTimeInMicroSec)
{
	uint8_t u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_NOT_USED ;
	if(gu8_timer2FlagIfUsed== u8_TIMER2_FLAG_NOT_USED)
	{
		volatile uint32_t u32_BusyWaitcounter = u8_INTIAL_COUNTER_VAL ;
		volatile uint8_t u8_CheckCompareFlag ;
		TIMERS_u8IntModesDis(u8_TIMER2_OVER_FLOW) ;
		TIMERS_u8IntModesDis(u8_TIMER2_COMPARE_ON_MATCH) ;
		TIMER2_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		TIMERS_u8ClearIntFlag(u8_TIMER2_COMPARE_ON_MATCH) ;
		Timer2_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer2_u8setOverFlowRegTicksBeforeOV(u8_INTIALIZING_TIMER2_COUNTER) ;
		while(u32_BusyWaitcounter <=u32_BusyTimeInMicroSec)
		{
			TIMERS_u8GetIntFlag(u8_TIMER2_COMPARE_ON_MATCH,(uint8_t*)(&u8_CheckCompareFlag)) ;
			if(u8_CheckCompareFlag == u8_Flag_RAISED )
			{
				TIMERS_u8ClearIntFlag(u8_TIMER2_COMPARE_ON_MATCH) ;
				u32_BusyWaitcounter++ ;
			}
		}
	}
	else
	{
		u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_USED ;
	}
	return u8_Timer2FlagIfUsed ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TIMER2_u8InterruptWait(uint32_t u32_interruptTimeInMilliSec)
{
	uint8_t u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_NOT_USED ;
	if(gu8_timer2FlagIfUsed==u8_TIMER2_FLAG_NOT_USED &&gu8_timer2FinishIntWaitFlag != u8_BEGIN_INTERRUPT_WAITING )
	{
		gu64_timer2IntWaitcounter = (uint64_t)(u32_interruptTimeInMilliSec*u8_NUMBER_OF_COUNTS_TO_COMP_1mS_with_8_pre) ;
		Timer2_u8setCompareRegTicksBeforeOV(u8_NUM_OF_COUNTS_FOR_250_uS_with_8_pre) ;
		Timer2_u8setOverFlowRegTicksBeforeOV(u8_INTIALIZING_TIMER2_COUNTER) ;
		gu8_timer2FlagIfUsed = u8_TIMER2_FLAG_USED ;
		TIMERS_u8IntModesEn(u8_TIMER2_COMPARE_ON_MATCH);
		TIMER2_u8setCallBack(u8_TIMER2_COMPARE_ON_MATCH,TIMER2_voidIntWaitControlFlagCount) ;
		TIMER2_u8StartWithclockAndPrescalerSelect(u8_INTERNAL_CLK_PRE_8) ;
		gu8_timer2FinishIntWaitFlag = u8_BEGIN_INTERRUPT_WAITING ;

	}
	else
	{
		u8_Timer2FlagIfUsed = u8_TIMER2_FLAG_USED ;
	}
	return u8_Timer2FlagIfUsed ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t TIMER2_u8GetIntWaitStatus(void)
{
	return gu8_timer2FinishIntWaitFlag  ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

static void TIMER2_voidIntWaitControlFlagCount(void)
{

	if(gu8_timer2FlagIfUsed==u8_TIMER2_FLAG_USED&&gu64_timer2IntWaitcounter > u8_INTIAL_COUNTER_VAL)
	{
		gu64_timer2IntWaitcounter-- ;
	}
	else
	{
		gu8_timer2FlagIfUsed = u8_TIMER2_FLAG_NOT_USED ;
		gu8_timer2FinishIntWaitFlag = u8_FINISH_INTERRUPT_WAITING ;
	}
}
