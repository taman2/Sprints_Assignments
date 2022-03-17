/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: software PWM
 *  Layer arch : MCAL
 *  Created on: Jan 10, 2022
 *  Modified on : Jan 15, 2022
 *	version:2
 *
 */



#include "../STD_TYPES.h"
#include "timers_interface.h"
#include "softwarePWM_private.h"
#include "softwarePWM_interface.h"
#include "DIO_interface.h"


void SWPWM_voidChan1OnChan2Off(void)
{
	DIO_SetPinValue(PORTD,PIN4,HIGH);
    DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void SWPWM_voidChan1OffChan2On(void)
{
	DIO_SetPinValue(PORTD,PIN4,LOW);
    DIO_SetPinValue(PORTD,PIN5,HIGH);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void SWPWM_voidChan1OffChan2Off(void)
{
	DIO_SetPinValue(PORTD,PIN4,LOW);
    DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void SWPWM_voidChan1OnChan2On(void)
{
	DIO_SetPinValue(PORTD,PIN4,HIGH);
	DIO_SetPinValue(PORTD,PIN5,HIGH);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void SWPWM_voidPinsInit(void)
{
	 TIMERS_voidInit() ;
	 Timer0_u8setOverFlowRegTicksBeforeOV(u8_MAX_8BIT_REG_HOLD) ;
	 DIO_SetPinDirection(PORTD,PIN4,OUTPUT);
	 DIO_SetPinDirection(PORTD,PIN5,OUTPUT);
	 DIO_SetPinValue(PORTD,PIN4,LOW);
	 DIO_SetPinValue(PORTD,PIN5,LOW);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t SWPWM_u8ControlChannels(uint8_t u8_wantedPWMDuty,uint8_t u8_wantedMotorForPwm)
{
	uint8_t u8_ErrorFlag = u8_OK ; 
	uint8_t u8_SetCompareVal  ;
	if(u8_wantedPWMDuty<=u8_PWM_100_DUTY_PERCENT)
	{
		if(u8_wantedPWMDuty>u8_PWM_0_DUTY_PERCENT && u8_wantedPWMDuty<u8_PWM_100_DUTY_PERCENT)
		{
			u8_SetCompareVal = (uint8_t)((uint16_t)(u8_wantedPWMDuty*u8_MAX_8BIT_REG_HOLD)/u8_PWM_100_DUTY_PERCENT) ;
			Timer0_u8setCompareRegTicksBeforeOV(u8_SetCompareVal) ;
			switch(u8_wantedMotorForPwm)
			{
				case u8_SWPWM_TO_CH1_STOP_CH2 : TIMER0_u8setCallBack(u8_TIMER0_COMPARE_ON_MATCH,SWPWM_voidChan1OffChan2Off) ;
											TIMER0_u8setCallBack(u8_TIMER0_OVER_FLOW,SWPWM_voidChan1OnChan2Off) ;
											break ;  
				case u8_SWPWM_TO_CH2_STOP_CH1 : TIMER0_u8setCallBack(u8_TIMER0_COMPARE_ON_MATCH,SWPWM_voidChan1OffChan2Off) ;
											TIMER0_u8setCallBack(u8_TIMER0_OVER_FLOW,SWPWM_voidChan1OffChan2On) ;
											break ; 
				case u8_SWPWM_TO_CH1_AND_CH2  : TIMER0_u8setCallBack(u8_TIMER0_COMPARE_ON_MATCH,SWPWM_voidChan1OffChan2Off) ;
											TIMER0_u8setCallBack(u8_TIMER0_OVER_FLOW,SWPWM_voidChan1OnChan2On) ;
											break ; 
				default 				  :  u8_ErrorFlag = u8_NOK ; 
											break ; 
			}
			if(u8_ErrorFlag==u8_OK)
			{
				TIMERS_u8IntModesEn(u8_TIMER0_OVER_FLOW) ; 
				TIMERS_u8IntModesEn(u8_TIMER0_COMPARE_ON_MATCH) ;
			}
		}
		else if (u8_wantedPWMDuty==u8_PWM_0_DUTY_PERCENT&&(u8_wantedMotorForPwm>=u8_SWPWM_TO_CH1_STOP_CH2)&&(u8_wantedMotorForPwm<=u8_SWPWM_TO_CH1_AND_CH2))
		{
			TIMERS_u8IntModesDis(u8_TIMER0_OVER_FLOW) ;
			TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ; 
			DIO_SetPinValue(PORTD,PIN4,LOW);
			DIO_SetPinValue(PORTD,PIN5,LOW);
		}
		else 
		{
			switch(u8_wantedMotorForPwm)
			{
				case u8_SWPWM_TO_CH1_STOP_CH2 : DIO_SetPinValue(PORTD,PIN4,HIGH);
											DIO_SetPinValue(PORTD,PIN5,LOW); 
											break ;  
				case u8_SWPWM_TO_CH2_STOP_CH1 : DIO_SetPinValue(PORTD,PIN4,LOW);
											DIO_SetPinValue(PORTD,PIN5,HIGH); 
											break ; 
				case u8_SWPWM_TO_CH1_AND_CH2  : DIO_SetPinValue(PORTD,PIN4,HIGH);
											DIO_SetPinValue(PORTD,PIN5,HIGH); 
											break ; 
				default 				  :  u8_ErrorFlag = u8_NOK ; 
											break ; 
			}
			
			if(u8_ErrorFlag==u8_OK)
			{
				TIMERS_u8IntModesDis(u8_TIMER0_OVER_FLOW) ;
				TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ; 
			}
		}
	}
	else 
	{
		u8_ErrorFlag = u8_NOK ; 
	}
	return u8_ErrorFlag ; 
	
}
