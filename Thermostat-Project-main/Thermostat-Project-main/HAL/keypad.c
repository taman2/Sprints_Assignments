/***********************************************************/
/*             Developed By: Muhammad Ahmed Ali            */
/***********************************************************/
#include "keypad.h"

void keypad_init(void)
{
	//Setting rows as outputs
	DIO_SetPinDirection(PORTC,2,OUTPUT);
	DIO_SetPinDirection(PORTC,3,OUTPUT);
	DIO_SetPinDirection(PORTC,4,OUTPUT);
	//Setting rows initial values to high
	DIO_SetPinValue(PORTC,2,HIGH);
	DIO_SetPinValue(PORTC,3,HIGH);
	DIO_SetPinValue(PORTC,4,HIGH);
	//Setting columns as inputs
	DIO_SetPinDirection(PORTC,5,INPUT);
	DIO_SetPinDirection(PORTC,6,INPUT);
	DIO_SetPinDirection(PORTC,7,INPUT);
	//Setting columns initial values to high
	DIO_SetPinValue(PORTC,5,HIGH);
	DIO_SetPinValue(PORTC,6,HIGH);
	DIO_SetPinValue(PORTC,7,HIGH);
}

uint8_t keypad_scan(void)
{
	uint8_t u8_button = ONE, u8_row = FIRST_ROW, u8_column = FIRST_COLUMN;
	
	for ( u8_row = FIRST_ROW ; u8_row <= ROWS ; u8_row++)
	{
	    DIO_SetPinValue(PORTC,u8_row,LOW);
		for (u8_column = FIRST_COLUMN ; u8_column <= COLUMNS ; u8_column++)
	    {
		    if(LOW == DIO_GetPinValue(PORTC,u8_column))
		    {
				TIMER0_msdelay(40);
				while(LOW == DIO_GetPinValue(PORTC,u8_column));
			    DIO_SetPinValue(PORTC,u8_row,HIGH);
			    return u8_button;
		    }
		    else
		    {
			    u8_button++;
		    }
	    }
		DIO_SetPinValue(PORTC,u8_row,HIGH);
	}
	return NO_BUTTON_PRESSED;
}