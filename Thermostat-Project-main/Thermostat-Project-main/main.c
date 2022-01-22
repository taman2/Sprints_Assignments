/***********************************************************/
/*             Developed By: Mohamed Salah                 */
/*             Developed By: Abdullah Mohamed              */
/***********************************************************/

#include "./HAL/LCD.h"
#include "./HAL/temp_sensor_lm35_interface.h"
#include "./HAL/Motor.h"
#include "./MCAL/adc_interface.h"
#include "./HAL/keypad.h"

#define  SWITCH_BUTTON_PORT     (PORTB)
#define  SWITCH_BUTTON_PIN	    (PIN2 )
#define  SWITCH_BUTTON_PRESSED  (1    )
#define  SWITCH_BUTTON_NPRESSED (0    )
#define  TRUE                   (1    )
#define  FALSE                  (0    )
#define  MAX_ALLOWED_TEMP       (40   )
#define  TOLERANCE              (3    )
#define  INITIAL_VAL            (0    )
#define  ASCII_CONV_FACTOR      ('0'  )
#define  MAX_DIGIT              (9    )
#define  NO_INPUT               (0    )
#define  ONE_DIGIT              (1    )
#define  TWO_DIGITS             (2    )
#define  WEIGHT                 (10   )
#define  DEBOUNCING_DELAY       (50   )
#define  ONE_SECOND             (1000 )


typedef enum
{
	SHOW_CURRENT_TEMP,
	SET_MAX_TEMP
}genu_ProgState_t;


int main(void)
{	
	uint8_t u8_SensTemperature = INITIAL_VAL;
	uint8_t u8_highSwitchTemp  = INITIAL_VAL;
	uint8_t u8_lowSwitchTemp   = INITIAL_VAL;
	uint8_t	u8_progUserInput   = INITIAL_VAL;
	uint8_t u8_count           = INITIAL_VAL;
	uint8_t u8_userInputSwitch = INITIAL_VAL;
	uint8_t u8_firstTime       = TRUE;
	genu_ProgState_t genu_ProgState = SET_MAX_TEMP;                    /* Initial State; Setting Maximum Temperature */

/**********************************************************************/
/*                       Program Initializations                      */
/**********************************************************************/
	                                                                   /***************************************************/
	LM35_voidInit();                                                   /* 1 - Initialize LM35 Temperature Sensor          */ 
	LCD_init();                                                        /* 2 - Initialize The LCD                          */
	keypad_init();	                                                   /* 3 - Initialize The Keypad                       */
	Motor_Init (MOTOR_ID_01);                                          /* 4 - Initialize The Fan Motor                    */
	DIO_SetPinDirection(SWITCH_BUTTON_PORT,SWITCH_BUTTON_PIN,INPUT);   /* 5 - Enable PB1 to be used in case switching     */
	LM35_u8GetTempInC(&u8_SensTemperature);                            /* 6 - Get Current Temperature                     */
	                                                                   /***************************************************/
/**********************************************************************/
/*                     End of Initializations                         */
/**********************************************************************/

	while (1) 
    {
		if(u8_firstTime == FALSE)
		{
			u8_userInputSwitch = DIO_GetPinValue(SWITCH_BUTTON_PORT,SWITCH_BUTTON_PIN);
			TIMER0_msdelay(DEBOUNCING_DELAY);
			while(DIO_GetPinValue(SWITCH_BUTTON_PORT,SWITCH_BUTTON_PIN)==SWITCH_BUTTON_PRESSED);	
		}
		
		switch(genu_ProgState)
		{	
			case SHOW_CURRENT_TEMP:
				
				LM35_u8GetTempInC(&u8_SensTemperature);
				LCD_printDigits(u8_SensTemperature);
				LCD_cursorMove(LEFT);
				LCD_cursorMove(LEFT);
				
				if(u8_SensTemperature >= u8_highSwitchTemp )
				{
					/* Turn On Fan */
					motorOn(MOTOR_ID_01,FORWARD);

				}
				else if(u8_SensTemperature <= u8_lowSwitchTemp)
				{
					/* Turn Off Fan */
					motorOff(MOTOR_ID_01,STOP);
				}
				
				if(u8_userInputSwitch == SWITCH_BUTTON_PRESSED)
				{
					genu_ProgState=SET_MAX_TEMP;
					u8_userInputSwitch = SWITCH_BUTTON_NPRESSED;
				}
				break;
				
			case SET_MAX_TEMP:
			
				LCD_command(DISPLAY_CLEAR);
				LCD_printString("SET MAX TEMP:");
				
				/* Get Input of Max Temperature From User */
				
				while(genu_ProgState == SET_MAX_TEMP )
				{
				   	u8_progUserInput=keypad_scan()- ASCII_CONV_FACTOR;
					
					if(u8_progUserInput > INITIAL_VAL && u8_progUserInput <= MAX_DIGIT && u8_count == NO_INPUT)
					{
						u8_firstTime      = FALSE;
						u8_highSwitchTemp = INITIAL_VAL;
						LCD_printDigits((uint32_t)u8_progUserInput);
						u8_highSwitchTemp=u8_progUserInput;
						u8_count++;						
					}
					else if(u8_progUserInput > INITIAL_VAL && u8_progUserInput <= MAX_DIGIT && u8_count == ONE_DIGIT)
					{
						LCD_printDigits((uint32_t)u8_progUserInput);
						u8_highSwitchTemp  = u8_highSwitchTemp * WEIGHT;
						u8_highSwitchTemp += u8_progUserInput;
						u8_count++;
					}
					else if(u8_progUserInput > INITIAL_VAL && u8_progUserInput <= MAX_DIGIT && u8_count == TWO_DIGITS)
					{
						
						LCD_command(DISPLAY_CLEAR);
						LCD_printString("WRONG INPUT!!");
						TIMER0_msdelay(ONE_SECOND);
						LCD_command(DISPLAY_CLEAR);
						LCD_printString("SET MAX TEMP:");
						u8_count=INITIAL_VAL;
						u8_highSwitchTemp=INITIAL_VAL;
					}
					u8_userInputSwitch=DIO_GetPinValue(SWITCH_BUTTON_PORT,SWITCH_BUTTON_PIN);
					TIMER0_msdelay(DEBOUNCING_DELAY);
					
					if((u8_userInputSwitch == SWITCH_BUTTON_PRESSED) && (u8_firstTime == FALSE))
					{	
						if(u8_highSwitchTemp < MAX_ALLOWED_TEMP)
						{
							motorOff(MOTOR_ID_01,STOP);
							u8_lowSwitchTemp = u8_highSwitchTemp -TOLERANCE;
							LCD_command(DISPLAY_CLEAR);
							LCD_printString("Temperature:");
							genu_ProgState=SHOW_CURRENT_TEMP;
							u8_count = INITIAL_VAL;
						}
						else
						{
							LCD_command(DISPLAY_CLEAR);
							LCD_printString("WRONG INPUT!!");
							TIMER0_msdelay(1000);
							LCD_command(DISPLAY_CLEAR);
							LCD_printString("SET MAX TEMP:");
							u8_count = INITIAL_VAL;
							u8_highSwitchTemp = INITIAL_VAL;
						}
						u8_userInputSwitch = SWITCH_BUTTON_NPRESSED;
					}	
			    }
		}
	}
}
	

