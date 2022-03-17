#ifndef STEERING_H_
#define STEERING_H_

#include "../../ECUAL/MOTOR_CONTROL/MOTOR.h"

#define STEERING_SPEED_00       (MOTOR_POWER_00)
#define STEERING_SPEED_30       (MOTOR_POWER_60)
#define STEERING_SPEED_80       (MOTOR_POWER_80)

void STEERING_init(void);
void STEERING_forward (uint8_t u8_pwm);
void STEERING_backward(uint8_t u8_pwm);
void STEERING_right(void);
void STEERING_stop(void);

#endif