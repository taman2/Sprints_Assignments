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
typedef struct
{	
	uint8_t u8_SensTemperature;
	uint8_t u8_highSwitchTemp;
	uint8_t u8_lowSwitchTemp;
	genu_ProgState progState;
		
}gstr_Program_t;
gstr_Program_t gstr_Program;
int main(void)
{
	
	LM35_voidInit();
	LCD_init();
	LCD_printString("Temperature:");
	Keyad_VoidINit();	
	gstr_Program.u8_SensTemperature=0;
    gstr_Program.u8_highSwitchTemp=10;
	gstr_Program.u8_lowSwitchTemp=0;
	LM35_u8GetTempInC(&u8_SensTemperature);
}
while(1)
{
	switch(progState)
		{	
			case SHOW_CURRENT_TEMP:
				LM35_u8GetTempInC(&u8_SensTemperature);
				LCD_printDigits(&u8_SensTemperature);
				if(u8_SensTemperature >=u8_highSwitchTemp )
				{
					
					/*turn on fan*/
				}
				else if(u8_SensTemperature<= u8_lowSwitchTemp)
				{
					/*turn off fan*/
					
				}
				else
				{
					
				}
				if(u8_userInput == LOW)
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
 				if(u8_userInput == LOW)
 				{u8_SensTemperature
 					progState=SET_MAX_TEMP;
 				}
				break;
				
				

		}