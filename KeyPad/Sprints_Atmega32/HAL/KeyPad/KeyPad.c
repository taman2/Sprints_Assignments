/*
 * KeyPad.c
 *
 * Created: 1/22/2022 8:16:19 PM
 *  Author: Mohamed
 */ 
#include "KeyPad.h"



void KeyPad_Init(void)
{
	/*Cols Input */
	GPIO_Init ( _KEYPAD_PORT,((COL1_PIN|COL1_PIN|COL1_PIN)),InPut);

	GPIO_Init ( _KEYPAD_PORT,((ROW1_PIN|ROW2_PIN|ROW3_PIN)),OutPut);
	
}

uinteg16_t Key_KeyPressed(void)
{
	uinteg8_t i=0;
	uinteg8_t j=0;
	uinteg16_t sw=5;
	for(i=0;i<ROW_NUM;i++)
	{
		KEYPAD_PORT=0xFF;
		CLR_BIT(KEYPAD_PORT,(i+ROW1_PIN_ID));
		_delay_ms(1);
		for(j=0;j<COL_NUM;j++)
		{
			if(GET_BIT(KEYPAD_PIN,(j+COL1_PIN_ID))==RESET)
			{
				_delay_ms(20);
				sw =(i*ROW_NUM)+j+1;	
				return sw;
			}
		}
	}
	return 20;
}

   


