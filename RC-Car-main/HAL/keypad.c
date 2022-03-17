
#include "../MCAL/DIO_interface.h"

#define TRUE  (1)
#define FALSE (0)

void keypad_init(void)
{
	//Setting rows as outputs
	DIO_SetPinDirection(PORTC,PIN2,OUTPUT);
	DIO_SetPinDirection(PORTC,PIN3,OUTPUT);
	DIO_SetPinDirection(PORTC,PIN4,OUTPUT);
	//Setting rows initial values to high
	DIO_SetPinValue(PORTC,PIN2,HIGH);
	DIO_SetPinValue(PORTC,PIN3,HIGH);
	DIO_SetPinValue(PORTC,PIN4,HIGH);
	//Setting columns as inputs
	DIO_SetPinDirection(PORTC,PIN5,INPUT);
	DIO_SetPinDirection(PORTC,PIN6,INPUT);
	DIO_SetPinDirection(PORTC,PIN7,INPUT);
	//Setting columns initial values to high
	DIO_SetPinValue(PORTC,PIN5,HIGH);
	DIO_SetPinValue(PORTC,PIN6,HIGH);
	DIO_SetPinValue(PORTC,PIN7,HIGH);
}

//Here we scan only the needed buttons for our very specific application and not scanning the whole 3x3 matrix

uint8_t keypad_scan(void)
{
	DIO_SetPinValue(PORTC,PIN2,LOW);
	DIO_SetPinValue(PORTC,PIN3,HIGH);
	DIO_SetPinValue(PORTC,PIN4,HIGH);
	
	if(DIO_GetPinValue(PORTC,PIN5) == 0)
	{
		DIO_SetPinValue(PORTC,PIN2,HIGH);
		return 1;
	}
	else if(DIO_GetPinValue(PORTC,PIN6) == 0)
	{
		DIO_SetPinValue(PORTC,PIN2,HIGH);
		return 2;
	}
	else if(DIO_GetPinValue(PORTC,PIN7) == 0)
	{
		DIO_SetPinValue(PORTC,PIN2,HIGH);     
		return 3;
	}
	else 
	{
		DIO_SetPinValue(PORTC,PIN2,HIGH);	
	}
	DIO_SetPinValue(PORTC,PIN2,HIGH);
	DIO_SetPinValue(PORTC,PIN3,LOW);
	DIO_SetPinValue(PORTC,PIN4,HIGH);
	if(DIO_GetPinValue(PORTC,PIN5) == 0)
	{
		DIO_SetPinValue(PORTC,PIN3,HIGH);
		return 4;
	}
	else 
	{
		DIO_SetPinValue(PORTC,PIN3,HIGH);
	}
	return 0;
}