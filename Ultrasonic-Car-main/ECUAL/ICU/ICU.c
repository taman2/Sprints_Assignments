#include "../../MCAL/EXTI/EXTERNAL_interrupts.h"
#include "../../MCAL/TIMER1/TIMER1_interface.h"
#include "ICU_Interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

typedef uint8_t ICU_SIGNAL_STATUS_t;

volatile ICU_SIGNAL_STATUS_t gu8_ICU_SIGNAL_STATUS= u8_ICU_WAITING_NEW_EDGE;


enu_ICU_ERROR ICU_enuInit()
{
	External_Interrupts_Init(EXTERNAL_INT_02,RISING_EDGE,ICU_voidExternalInterrupt02RisgISR);
	/*timer 1 init*/
	TIMER1_init(PRESCALE_8);
	return ICU_OK;
}

void ICU_voidExternalInterrupt02FallingISR(void)
{
	gu8_ICU_SIGNAL_STATUS=u8_FALLING_EDGE_HAPPENED;
}
void ICU_voidExternalInterrupt02RisgISR(void)
{
	gu8_ICU_SIGNAL_STATUS=u8_RISING_EDGE_HAPPENED;	
}
enu_ICU_ERROR ICU_u8SingnalOnTime(uint32_t *pu32_OnTime)
{
	if(pu32_OnTime == NULL_POINTER)
	{
		return ICU_NOK;
	}
	enu_ICU_ERROR enu_ICU_ERROR_State;
	switch(gu8_ICU_SIGNAL_STATUS)
	{
		case u8_RISING_EDGE_HAPPENED:
			TIMER1_voidStartCounting();
			External_Interrupts_Init(EXTERNAL_INT_02,FALLING_EDGE,ICU_voidExternalInterrupt02FallingISR);
			gu8_ICU_SIGNAL_STATUS = u8_ICU_WAITING_NEW_EDGE;
			enu_ICU_ERROR_State= ICU_NREADY;
			break;
		
		case u8_FALLING_EDGE_HAPPENED:
			gu8_ICU_SIGNAL_STATUS=u8_ICU_WAITING_NEW_EDGE;
			External_Interrupts_Init(EXTERNAL_INT_02,RISING_EDGE,ICU_voidExternalInterrupt02RisgISR);
			TIMER1_u32getCounts(pu32_OnTime, u8_FALLING_EDGE_HAPPENED);
			enu_ICU_ERROR_State= ICU_OK;
			break;
		
		case u8_ICU_WAITING_NEW_EDGE:
			enu_ICU_ERROR_State = ICU_NREADY;
			break;
		default:
			enu_ICU_ERROR_State= ICU_NOK;
			break;
	}
	return enu_ICU_ERROR_State;
}
