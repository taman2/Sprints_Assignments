#include "keypad.h"

void keypad_init(void)
{
	//Setting rows as outputs
	GPIO_dir(C,2,OUTPUT);
	GPIO_dir(C,3,OUTPUT);
	GPIO_dir(C,4,OUTPUT);
	//Setting rows initial values to high
	GPIO_setHigh(C,2);
	GPIO_setHigh(C,3);
	GPIO_setHigh(C,4);
	//Setting columns as inputs
	GPIO_dir(C,5,INPUT);
	GPIO_dir(C,6,INPUT);
	GPIO_dir(C,7,INPUT);
	//Setting columns initial values to high
	GPIO_setHigh(C,5);
	GPIO_setHigh(C,6);
	GPIO_setHigh(C,7);
}

uint8_t keypad_scan(void)
{
	uint8_t u8_button = ONE, u8_row = FIRST_ROW, u8_column = FIRST_COLUMN;
	
	for ( u8_row = FIRST_ROW ; u8_row <= ROWS ; u8_row++)
	{
	    GPIO_setLow(C,u8_row);
		for (u8_column = FIRST_COLUMN ; u8_column <= COLUMNS ; u8_column++)
	    {
		    if(LOW == GPIO_read(C,u8_column))
		    {
			    GPIO_setHigh(C,u8_row);
			    return u8_button;
		    }
		    else
		    {
			    u8_button++;
		    }
	    }
		GPIO_setHigh(C,u8_row);
	}
	return NO_BUTTON_PRESSED;
}