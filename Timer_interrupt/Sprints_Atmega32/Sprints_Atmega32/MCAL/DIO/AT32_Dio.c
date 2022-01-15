/*
 * AT32_Dio.c
 *
 * Created: 1/9/2022 1:42:34 AM
 *  Author: Mohamed Salah Taman
 */ 
#include "AT32_Dio.h"

/*EX: GPIO_Init ( _PORTA, PIN1,Input);
EX: GPIO_Init ( _PORTB, (PIN7| PIN0| PIN3),Onput);*/

genu_ERROR_t GPIO_Init (PORTX_t _PORTX,PIN_t PINX, GPIO_Mode PinMode)
{
	if(PinMode == OutPut)
	{
		switch(_PORTX)
		{
			case _PORTA:
				SET_BITS(DDRA,PINX);/*make PINX OutPut*/
				break;
			case _PORTB:
				SET_BITS(DDRB,PINX);/*make PINX OutPut*/
				break;
			case _PORTC:
				SET_BITS(DDRC,PINX);/*make PINX OutPut*/
				break;
			case _PORTD:
				SET_BITS(DDRD,PINX);/*make PINX OutPut*/
				break;
			default:
				return DIO_ERROR_NOK;
				break;
		}	
		return DIO_ERROR_OK;
	}
	else if(PinMode == InPut)
	{
		switch(_PORTX)
		{
			case _PORTA:
				CLR_BITS(DDRA,PINX);/*make PINX Input*/
				SET_BITS(PORTA,PINX);/*Pull up*/
				break;
			case _PORTB:
				CLR_BITS(DDRB,PINX);/*make PINX Input*/
				SET_BITS(PORTB,PINX);/*Pull up*/
				break;
			case _PORTC:
				CLR_BITS(DDRC,PINX);/*make PINX Input*/
				SET_BITS(PORTC,PINX);/*Pull up*/
				break;
			case _PORTD:
				CLR_BITS(DDRD,PINX);/*make PINX Input*/
				SET_BITS(PORTD,PINX);/*Pull up*/
				break;
			default:
				return DIO_ERROR_NOK;
				break;
		}
	}
	else{return DIO_ERROR_NOK;}
	return DIO_ERROR_OK;	
}
/*EX: GPIO_Write (&PORTA, PIN0 , RESET);
EX: GPIO_Write (&PORTB, (PIN7| PIN0| PIN3), SET);*/

genu_ERROR_t GPIO_Write (volatile uinteg8_t *PORTX,PIN_t PINX, GPIO_Value Value)
{
	if(PORTX == NULL ) return DIO_ERROR_NOK;
	if(Value == RESET)
	{
		CLR_BITS(*PORTX,PINX);
	}
	else if(Value == SET)
	{
		SET_BITS(*PORTX,PINX);
	}
	else
	{
		return DIO_ERROR_NOK;
	}
	return DIO_ERROR_OK;

}
/*EX: GPIO_Toggle (&PORTA, PIN0 );*/

genu_ERROR_t GPIO_Toggle (volatile uinteg8_t *PORTX,PIN_t PINX)
{
	if(PORTX == NULL ) return DIO_ERROR_NOK;
	TOGGLE_BITS(*PORTX,PINX);
	return DIO_ERROR_OK;
}
/*EX: GPIO_Read (&PORTA, PIN0 ,&enu_GPIOTemp);*/
genu_ERROR_t GPIO_Read (volatile uinteg8_t *PORTX,PIN_t PINX,GPIO_Value *GPIO_Value)
{
	if(PORTX == NULL || GPIO_Value == NULL) return DIO_ERROR_NOK;
	if(GET_BITS((*PORTX),PINX))
	{
		*GPIO_Value=SET;
	}
	else 
	{
		*GPIO_Value=RESET;

	}
	return DIO_ERROR_OK;
}
