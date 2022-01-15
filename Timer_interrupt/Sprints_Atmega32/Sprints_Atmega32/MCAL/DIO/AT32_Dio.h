/*
 * AT32_Dio.h
 *
 * Created: 1/9/2022 1:43:18 AM
 *  Author: Mohamed
 */ 


#ifndef AT32_DIO_H_
#define AT32_DIO_H_
#include "AtmegaPort.h"
#include "Data_Types.h"
#include "BitManipulation.h"
#define  NULL ((void*) 0)
typedef enum {
	InPut,
	OutPut	
}GPIO_Mode;
typedef enum 
{
	PIN0=0b00000001,PIN1=0b00000010,PIN2=0b00000100,PIN3=0b00001000,
	PIN4=0b00010000,PIN5=0b00100000,PIN6=0b01000000,PIN7=0b10000000
}PIN_t;
typedef enum {
	RESET=0,
	SET=1
}GPIO_Value;
typedef enum
{
	_PORTA,_PORTB,_PORTC,_PORTD
}PORTX_t;


genu_ERROR_t GPIO_Init (PORTX_t _PORTX,PIN_t PINX, GPIO_Mode PinMode);
genu_ERROR_t GPIO_Write (volatile uinteg8_t *PORTX,PIN_t PINX, GPIO_Value Value);
genu_ERROR_t GPIO_Toggle (volatile uinteg8_t *PORTX,PIN_t PINX);
genu_ERROR_t GPIO_Read (volatile uinteg8_t *PORTX,PIN_t PINX,GPIO_Value *GPIO_Value);


#endif /* AT32_DIO_H_ */