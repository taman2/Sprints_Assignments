#include "ROBOT_control.h"
#include "../../ECUAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../STEERING/STEERING.h"
#include "../../LIB/STD_TYPES.h"
#include "../../ECUAL/NON_BLOCKING_LCD/lcd_interface.h"
#include "../../MCAL/TIMERS0_2/timers_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

uint8_t gu8_lcdState;

uint8_t u8_forwardStr[]  = "FORWARD";
uint8_t u8_backwardStr[] = "BACKWARD";
uint8_t u8_rightStr[]    = "RIGHT";
 
void ROBOT_init(void)
{	
	STEERING_init();
	ULTRASONIC_voidInit();
	gu8_lcdState = LCD_u8Init();
	DIO_SetPinDirection(PORTB,PIN4,OUTPUT);
    DIO_SetPinDirection(PORTB,PIN5,OUTPUT);
	DIO_SetPinDirection(PORTB,PIN6,OUTPUT);
	DIO_SetPinDirection(PORTB,PIN7,OUTPUT);
}

EN_currentCarState_t ROBOT_getCurrentState(void)
{
	
	uint8_t  u8_ultraSonicStatus;
	uint16_t u16_distInCm;
	static EN_currentCarState_t EN_currentObstacleState = NO_OBSTACLES_AHEAD;
	
	if(gu8_lcdState == u8_LCD_NOK)
	{
		gu8_lcdState = LCD_u8Init();		
	}
	
    u8_ultraSonicStatus = ULTRASONIC_u8GetObstacleDistInCm(&u16_distInCm);
	
	if(u8_ULTRASONIC_OK == u8_ultraSonicStatus)
	{	
		if(u16_distInCm > APPROACHING_DISTANCE)
		{	
			EN_currentObstacleState = NO_OBSTACLES_AHEAD;  
		}
		else if((u16_distInCm <= APPROACHING_DISTANCE) && (u16_distInCm > TURNING_DISTANCE_MAX))
		{
			EN_currentObstacleState = APPROACHING_OBSTACLE; 
		}
		else if((u16_distInCm <= TURNING_DISTANCE_MAX) && (u16_distInCm >= TURNING_DISTANCE_MIN))
		{
			EN_currentObstacleState = CLOSE_TO_OBSTACLE;
		}
		else if(u16_distInCm < TURNING_DISTANCE_MIN)
		{	
			EN_currentObstacleState = VERY_CLOSE_TO_OBSTACLE;
		}
		else
		{
	    }
	}
	
	return EN_currentObstacleState;
}


void ROBOT_moveUpdate(void)
{
	
	uint8_t  u8_changeState;
	uint8_t  u8_printState;
	uint8_t u8_clearState; 
	uint8_t u8_stopState; 
	
	EN_currentCarState_t EN_currentCarState;
	
	static EN_currentCarState_t EN_checkStateChange = NO_OBSTACLES_AHEAD;
	static uint8_t u8_printStrDone = FALSE;
	static uint8_t u8_clearStrDone = FALSE;
	static uint8_t u8_stopRequired = FALSE ; 
	static uint8_t u8_waitDelayRequest = FALSE ; 
	
	if(u8_stopRequired == TRUE)
	{
		if(u8_waitDelayRequest == FALSE)
		{
			STEERING_stop(); 
			TIMER2_u8InterruptWait(STOP_DELAY) ; 
			u8_waitDelayRequest = TRUE ; 
		}
		u8_stopState = TIMER2_u8GetIntWaitStatus() ; 
		
		if(u8_stopState == u8_FINISH_INTERRUPT_WAITING)
		{
			u8_stopRequired = FALSE ; 
			u8_waitDelayRequest = FALSE ;
		}
		
	}
	else 
	{
		EN_currentCarState = ROBOT_getCurrentState();
		switch(EN_currentCarState)
		{
			case NO_OBSTACLES_AHEAD:
			
				if(gu8_lcdState == u8_LCD_NOK)
				{
					gu8_lcdState = LCD_u8Init();
				}
				else
				{
					if(u8_clearStrDone == FALSE)
					{
						u8_clearState = LCD_u8sendCommand(u8_LCD_DISPLAY_CLEAR); 
						if(u8_LCD_OK == u8_clearState)
						{
							u8_clearStrDone = TRUE ; 
						}
					}
					else if(FALSE == u8_printStrDone)
					{
						u8_printState = LCD_u8PrintStr(u8_forwardStr);
						if(u8_LCD_OK == u8_printState)
						{
							u8_printStrDone = TRUE;
						}
					}
				}
				
				if (EN_checkStateChange != APPROACHING_OBSTACLE && EN_checkStateChange != NO_OBSTACLES_AHEAD )
				{
					u8_printStrDone = FALSE;
					u8_clearStrDone = FALSE ; 
				}
	
				EN_checkStateChange = NO_OBSTACLES_AHEAD;
				
				STEERING_forward(STEERING_SPEED_80);
	
			
			break;
			
			case APPROACHING_OBSTACLE:
	
	
				if(gu8_lcdState == u8_LCD_NOK)
				{
					gu8_lcdState = LCD_u8Init();
				}
				else
				{
					if(u8_clearStrDone == FALSE)
					{
						u8_clearState = LCD_u8sendCommand(u8_LCD_DISPLAY_CLEAR); 
						if(u8_LCD_OK == u8_clearState)
						{
							u8_clearStrDone = TRUE ; 
						}
					}
					else if(FALSE == u8_printStrDone)
					{
						u8_printState = LCD_u8PrintStr(u8_forwardStr);
						if(u8_LCD_OK == u8_printState)
						{
							u8_printStrDone = TRUE;
						}
					}
				}
				if (EN_checkStateChange != APPROACHING_OBSTACLE && EN_checkStateChange != NO_OBSTACLES_AHEAD )
				{
					u8_printStrDone = FALSE;
					u8_clearStrDone = FALSE ; 
				}
				
				EN_checkStateChange = APPROACHING_OBSTACLE;
	
				STEERING_forward(STEERING_SPEED_30);		
				
				break;
			
			case CLOSE_TO_OBSTACLE:
			
				if(gu8_lcdState == u8_LCD_NOK)
				{
					gu8_lcdState = LCD_u8Init();
				}
				else
				{
					if(u8_clearStrDone == FALSE)
					{
						u8_clearState = LCD_u8sendCommand(u8_LCD_DISPLAY_CLEAR); 
						if(u8_LCD_OK == u8_clearState)
						{
							u8_clearStrDone = TRUE ; 
						}
					}
					else if(FALSE == u8_printStrDone)
					{
						u8_printState = LCD_u8PrintStr(u8_rightStr);
						if(u8_LCD_OK == u8_printState)
						{
							u8_printStrDone = TRUE;
						}
					}
				}
				
				if (EN_checkStateChange == CLOSE_TO_OBSTACLE)
				{
					u8_changeState = FALSE;
				}
				else
				{
					u8_changeState = TRUE;
					u8_printStrDone = FALSE;
					u8_clearStrDone = FALSE; 
				}
				
				if(u8_changeState == TRUE)
				{
					u8_stopRequired = TRUE; 
				}
				
				if(u8_stopRequired == FALSE)
				{
					STEERING_right();
				}
				
				EN_checkStateChange = CLOSE_TO_OBSTACLE;
			
				break;
			
			case VERY_CLOSE_TO_OBSTACLE:
			
				if(gu8_lcdState == u8_LCD_NOK)
				{
					gu8_lcdState = LCD_u8Init();
				}
				else
				{
					if(u8_clearStrDone == FALSE)
					{
						u8_clearState = LCD_u8sendCommand(u8_LCD_DISPLAY_CLEAR); 
						if(u8_LCD_OK == u8_clearState)
						{
							u8_clearStrDone = TRUE ; 
						}
					}
					else if(FALSE == u8_printStrDone)
					{
						u8_printState = LCD_u8PrintStr(u8_backwardStr);
						if(u8_LCD_OK == u8_printState)
						{
							u8_printStrDone = TRUE;
						}
					}
				}
				if (EN_checkStateChange == VERY_CLOSE_TO_OBSTACLE)
				{
					u8_changeState = FALSE;
				}
				else
				{
					u8_changeState = TRUE;
					u8_printStrDone = FALSE;
					u8_clearStrDone = FALSE; 
				}
				if(u8_changeState == TRUE)
				{
					u8_stopRequired = TRUE ; 
				}
				
				if(u8_stopRequired == FALSE )
				{
					STEERING_backward(STEERING_SPEED_30);
				}
				
				EN_checkStateChange = VERY_CLOSE_TO_OBSTACLE;
	
				break;
			
			default:
				break;
		}
	}
}

/*
		DIO_SetPinValue(PORTB,PIN4,HIGH);
		DIO_SetPinValue(PORTB,PIN5,LOW);
		DIO_SetPinValue(PORTB,PIN6,LOW);
		DIO_SetPinValue(PORTB,PIN7,LOW);
*/