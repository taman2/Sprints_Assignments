#include "../HAL/keypad.h"
#include "../HAL/Motor.h"
#include "../MCAL/GIE_interface.h"
#include "../HAL/delay.h"

#define CHANGE_STATE (1)
#define MOVE         (2)
#define RIGHT        (3)
#define LEFT         (4)
	
int main()
{
	/*******************************************************************************/
	/*                                                                             */
	/*                       System initialization                                 */                              
	/*                                                                             */
	/*******************************************************************************/
	
	GIE_voidEnable();                //Enabling Global Interrupt
	Motor_Init(MOTOR_ID_01);         //Motor 1 Initialization   
	Motor_Init(MOTOR_ID_02);         //Motor 2 Initialization   
	keypad_init();                   //Keypad Initialization    
	volatile uint8_t state = 0;      //Motor State              
	while(1)
	{
		/*******************************************************************************/
		/*                                                                             */
		/*                  This condition is responsible for altering the state       */
		/*                  of the direction and speed                                 */
		/*                                                                             */
		/*******************************************************************************/
		
		if(CHANGE_STATE == keypad_scan())
		{
			delay();
			state++;
			if(state > 4)
			{
				state = 0;   //Start over the states loop
			}
		}
		
		/*******************************************************************************/
		/*                                                                             */
		/*     The following conditions are responsible for moving the car             */
		/*     according to its current state and whether it's turning left or right   */
		/*                                                                             */
		/*******************************************************************************/
		
		while(RIGHT == keypad_scan())
		{
			delay();
			Motor_Move(MOTOR_ID_01,FORWARD,MOTOR_POWER_60);      //Turn right with 60% speed
		}
		MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);           //Stop the motor after turning right
		
		while(LEFT == keypad_scan())
		{
			delay();
			Motor_Move(MOTOR_ID_02,FORWARD,MOTOR_POWER_60);      //Turn left with 60% speed
		}
		MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);           //Stop the motor after turning left
		
		switch(state)
		{
			case 0:
			while(MOVE == keypad_scan())                         //Execute the loop when MOVE button is pressed
			{
				delay();                                         //This delay is used to overcome the debouncing problem
				MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);   //Not Moving
			}
			break;
			
			case 1:
			while(MOVE == keypad_scan())
			{
				delay();
				MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_30);    //Moving Forward with 30% Speed
			}
			MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00); 
			break;
			
			case 2:
			while(MOVE == keypad_scan())
			{
				delay();
				MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_60);    //Moving Forward with 60% Speed
			}
			MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);
			break;
			
			case 3:
			while(MOVE == keypad_scan())
			{
				delay();
				MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_90);    //Moving Forward with 90% Speed
			}
			MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);
			break;
			
			case 4:
			while(MOVE == keypad_scan())
			{
				delay();
				MoveAllMotors(BACKWARD,BACKWARD,MOTOR_POWER_30);  //Moving Backward with 30% Speed
			}
			MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);
			break;
			
			default:
			MoveAllMotors(FORWARD,FORWARD,MOTOR_POWER_00);
			break;
		}
		
	}
}