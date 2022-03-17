#include "MOTOR.h"
#include "../../LIB/STD_TYPES.h"

uint8_t Motor_Init(uint8_t u8_MotorId)
{
	switch(u8_MotorId)
	{
		case MOTOR_ID_01:
			SWPWM_voidInit();
			SWPWM_u8ControlChannels(u8_PWM_0_DUTY_PERCENT,u8_SWPWM_TO_CH1_AND_CH2);
			DIO_SetPinDirection(MOTOR_01_DIR_PORT,MOTOR_01_DIR_PIN01, OUTPUT);
			DIO_SetPinDirection(MOTOR_01_DIR_PORT,MOTOR_01_DIR_PIN02, OUTPUT);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_DIR_PIN01, LOW);
			DIO_SetPinValue(MOTOR_01_DIR_PORT, MOTOR_01_DIR_PIN02, LOW);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			SWPWM_voidInit();
			SWPWM_u8ControlChannels(u8_PWM_0_DUTY_PERCENT,u8_SWPWM_TO_CH1_AND_CH2);
			DIO_SetPinDirection(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN01,OUTPUT);
			DIO_SetPinDirection(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN02,OUTPUT);
			DIO_SetPinValue(MOTOR_02_DIR_PORT, MOTOR_02_DIR_PIN01,LOW);
			DIO_SetPinValue(MOTOR_02_DIR_PORT,MOTOR_02_DIR_PIN02, LOW);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}

}
uint8_t Motor_setDirection(uint8_t u8_MotorId, uint8_t u8_MotorDirection)
{
	switch(u8_MotorId)
	{
		case MOTOR_ID_01:
			if(u8_MotorDirection == FORWARD)
			{
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN01, LOW);
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN02, HIGH);
			}
			else
			{
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN01, HIGH);
				DIO_SetPinValue(MOTOR_01_DIR_PORT , MOTOR_01_DIR_PIN02, LOW);
			}
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			if(u8_MotorDirection == FORWARD)
			{
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN01, LOW);
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN02, HIGH);
			}
			else
			{
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN01, HIGH);
				DIO_SetPinValue(MOTOR_02_DIR_PORT , MOTOR_02_DIR_PIN02, LOW);
			}
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
			break;
	}
	return MOTOR_ERROR_NOK;
}
uint8_t Motor_Move(uint8_t MotorId, uint8_t u8_MotorDirection,uint8_t u8_MotorPower)
{
	switch(MotorId)
	{
		case MOTOR_ID_01:
			Motor_setDirection(MotorId,u8_MotorDirection);
			SWPWM_u8ControlChannels(u8_MotorPower,u8_SWPWM_TO_CH1_STOP_CH2);
			return MOTOR_ERROR_OK;
			break;
		case MOTOR_ID_02:
			Motor_setDirection(MotorId,u8_MotorDirection);
			SWPWM_u8ControlChannels(u8_MotorPower,u8_SWPWM_TO_CH2_STOP_CH1);
			return MOTOR_ERROR_OK;
			break;
		default:
			return MOTOR_ERROR_NOK;
	}
	
}
uint8_t MoveAllMotors(uint8_t u8_Motor01Direction,uint8_t u8_Motor02Direction,uint8_t u8_MotorsPower)
{
	Motor_setDirection(MOTOR_ID_01,u8_Motor01Direction);
	Motor_setDirection(MOTOR_ID_02,u8_Motor02Direction);
	SWPWM_u8ControlChannels(u8_MotorsPower,u8_SWPWM_TO_CH1_AND_CH2);
	return MOTOR_ERROR_OK;

}

uint8_t Motors_Stop(void){
	
	Motor_Move(MOTOR_ID_01,BACKWARD,MOTOR_POWER_00);
	Motor_Move(MOTOR_ID_02,BACKWARD,MOTOR_POWER_00);
	
	return MOTOR_ERROR_OK;
}
