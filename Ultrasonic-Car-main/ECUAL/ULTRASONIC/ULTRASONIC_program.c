#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/TIMER1/TIMER1_interface.h"
#include "../ICU/ICU_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "ULTRASONIC_interface.h"
#include "../LCD/LCD.h"

void ULTRASONIC_voidInit(void)
{
	TIMER1_init(PRESCALE_8);
	ICU_enuInit() ;
	DIO_SetPinDirection(u8_ULTRASONIC_PORT,u8_ULTRASONIC_TRIG_PIN,OUTPUT);
	DIO_SetPinDirection(u8_ULTRASONIC_PORT,u8_ULTRASONIC_ECHO_PIN,INPUT);
    DIO_SetPinValue(u8_ULTRASONIC_PORT,u8_ULTRASONIC_TRIG_PIN,LOW);
}


uint8_t ULTRASONIC_u8GetObstacleDistInCm(uint16_t* pu16_returnDistInCm) 
{
	static uint8_t u8_trigBegin = u8_ULTRASONIC_FALSE ;
	uint32_t u32_echoPulseTimeUS; 
	uint8_t u8_returnDistState = u8_ULTRASONIC_NOK ; 
	EN_timer1DelayStatus_t TIMER1_WaitAnotherTrig  ; 
	enu_ICU_ERROR ICU_status = ICU_NOK ; 

	if(pu16_returnDistInCm !=NULL_POINTER)
	{
		if(u8_trigBegin==u8_ULTRASONIC_FALSE)
		{
			DIO_SetPinValue(u8_ULTRASONIC_PORT,u8_ULTRASONIC_TRIG_PIN,HIGH);
			TIMER1_voidMicroSecDelay(u8_ULTRASONIC_TRIG_TIME_US) ; 
			DIO_SetPinValue(u8_ULTRASONIC_PORT,u8_ULTRASONIC_TRIG_PIN,LOW);
			u8_trigBegin = u8_ULTRASONIC_TRUE ; 
		}
		else if(u8_trigBegin== u8_ULTRASONIC_TRUE )
		{
			ICU_status = ICU_u8SingnalOnTime(&u32_echoPulseTimeUS) ;
			if(ICU_status == ICU_OK )
			{   
				u8_returnDistState = u8_ULTRASONIC_OK ; 
				u8_trigBegin = u8_ULTRASONIC_WAIT_NEW_TRIG ; 
				(*pu16_returnDistInCm) = (uint16_t)(((uint32_t)(u32_echoPulseTimeUS * u16_ULTRASONIC_LIGHT_SPEED_IN_m_PER_SEC*u8_ULTRASONIC_CONVERT_TO_Cm))
													/((uint32_t)((uint32_t)u8_ULTRASONIC_HALF_ECHO_TIME * (uint32_t)u32_ULTRASONIC_CONVERT_FROM_MICRO_TO_SEC))) ; 
			}
		}
		else 
		{
			TIMER1_WaitAnotherTrig = TIMER1_msdelay(u8_ULTRASONIC_TIME_BETWEEN_ECHO_AND_TRIG) ; 
			if(TIMER1_WaitAnotherTrig == TIMER1_MS_DELAY_FINISHED)
			{
				u8_trigBegin = u8_ULTRASONIC_FALSE ; 
			}
		}
	}
	
	return u8_returnDistState ; 
}
