#ifndef MOTOR_H_
#define MOTOR_H_

#include "../STD_TYPES.h"
#include "../BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/DIO_private.h"
#include "../MCAL/softwarePWM_interface.h"

#define	MOTOR_ERROR_OK				1U
#define	MOTOR_ERROR_NOK				0U
#define MOTOR_ID_01					20
#define MOTOR_ID_02					21
#define	MOTOR_01_DIR_PORT			PORTD
#define	MOTOR_02_DIR_PORT			PORTD
#define MOTOR_01_DIR_PIN01			PIN2
#define	MOTOR_01_DIR_PIN02			PIN3
#define MOTOR_02_DIR_PIN01			PIN6
#define	MOTOR_02_DIR_PIN02			PIN7
#define FORWARD						23U
#define BACKWARD					24U

#define	MOTOR_POWER_00				u8_PWM_0_DUTY_PERCENT				
#define	MOTOR_POWER_10				u8_PWM_10_DUTY_PERCENT				
#define MOTOR_POWER_20				u8_PWM_20_DUTY_PERCENT				
#define MOTOR_POWER_30				u8_PWM_30_DUTY_PERCENT				
#define MOTOR_POWER_40				u8_PWM_40_DUTY_PERCENT				
#define MOTOR_POWER_50				u8_PWM_50_DUTY_PERCENT				
#define MOTOR_POWER_60				u8_PWM_60_DUTY_PERCENT				 
#define MOTOR_POWER_70				u8_PWM_70_DUTY_PERCENT				 
#define MOTOR_POWER_80				u8_PWM_80_DUTY_PERCENT				 
#define MOTOR_POWER_90				u8_PWM_90_DUTY_PERCENT				 
#define MOTOR_POWER_100			    u8_PWM_100_DUTY_PERCENT				

/**************************************User Functions**************************************************/
/*EX:	Motor_Init(MOTOR_ID_01);   */
uint8_t Motor_Init(uint8_t u8_MotorId);

/*EX:	Motor_Move(MOTOR_ID_01, BACKWARD,MOTROR_POWER_10);    */
uint8_t Motor_Move(uint8_t MotorId, uint8_t u8_MotorDirection,uint8_t u8_MotorPower);

/*EX:	MoveAllMotors(FORWARD,BACKWARD,MOTROR_POWER_10);    */
uint8_t MoveAllMotors(uint8_t u8_Motor01Direction,uint8_t u8_Motor02Direction,uint8_t u8_MotorsPower);

/************************************static functions***************************************************/
uint8_t Motor_setDirection(uint8_t u8_MotorId, uint8_t u8_MotorDirection);

#endif /* MOTOR_H_ */
