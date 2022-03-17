#include "../../ECUAL/MOTOR_CONTROL/MOTOR.h"
#include "STEERING.h"

void STEERING_init(void){
	
	Motor_Init(MOTOR_ID_01);
	Motor_Init(MOTOR_ID_02);
}

void STEERING_forward(uint8_t u8_pwm){
	
	MoveAllMotors(FORWARD,FORWARD,u8_pwm);
}

void STEERING_backward(uint8_t u8_pwm){
	
	MoveAllMotors(BACKWARD,BACKWARD,u8_pwm);
}

void STEERING_right(){
	
	Motor_Move(MOTOR_ID_02,FORWARD,STEERING_SPEED_80);
}

void STEERING_stop(void){
	
	Motors_Stop();
}