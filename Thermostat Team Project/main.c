#include "./HAL/LCD.h"
#include "./HAL/temp_sensor_lm35_interface.h"
#include "./MCAL/adc_interface.h"
#include "./HAL/keypad_interface.h"

typedef enum
{
	SHOW_CURRENT_TEMP,
	SET_MAX_TEMP,
	ALARM
	
}genu_ProgState;
/*typedef struct
{	
	uint8_t u8_SensTemperature;
	uint8_t u8_highSwitchTemp;
	uint8_t u8_lowSwitchTemp;
	genu_ProgState progState;
		
}gstr_Program_t;*/
int main(void)
{
	
	LM35_voidInit();
	LCD_init();
	LCD_printString("Temperature:");
	Keyad_VoidINit();	
	uint8_t u8_SensTemperature=0;
	uint8_t u8_highSwitchTemp=10;
	uint8_t u8_lowSwitchTemp=0;
	LM35_u8GetTempInC(&u8_SensTemperature);
	
	while (1) 
    {
		LCD_printString("Temperature:");
		u8_highSwitchTemp=KeyPad_U8Data();
		
		if(u8_highSwitchTemp<10)
		{
			LCD_printDigits((uint32_t)u8_highSwitchTemp);
			LCD_cursorMove(LEFT);
		}
	///	LCD_cursorMove(LEFT);

		//LCD_cursorMove(LEFT);
		//}
		//LCD_cursorMove(LEFT);
		/*switch(progState)
		{	
			case SHOW_CURRENT_TEMP:
				LM35_u8GetTempInC(&u8_SensTemperature);
				LCD_printDigits(&u8_SensTemperature);
				if(u8_SensTemperature >=u8_highSwitchTemp )
				{
					
					/*turn on fan*/
			/*	}
				else if(u8_SensTemperature<= u8_lowSwitchTemp)
				{
					/*turn off fan*/
					
				/*}
				else
				{
					
				}
				if(u8_userInput == 1)
				{u8_SensTemperature
					progState=SET_MAX_TEMP;
				}
				break;
			case SET_MAX_TEMP:
				/*clear LCD*/
				//LCD_printString("SET MAX SWITCH TEMP:");
				/*get keyPad with max 2 digits*/
				/*check if valid input*/
				/*u8_highSwitchTemp = user input-*/
// 				if(u8_userInput == 1)
// 				{u8_SensTemperature
// 					progState=SET_MAX_TEMP;
// 				}
//*/ 				

		}
		/*LM35_u8GetTempInC(&u8_temperature);
		LCD_printDigits(u8_temperature);
		LCD_cursorMove(LEFT);
		LCD_cursorMove(LEFT);
		TIMER0_msdelay(500);*/	
}

