/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: software PWM
 *  Layer arch : MCAL
 *  Created on: Jan 10, 2022
 *  Modified on : Jan 15, 2022
 *	version:2
 *
 */


#ifndef __SOFTWARE__PWM__INTERFACE__
#define __SOFTWARE__PWM__INTERFACE__

#include "../../LIB/STD_TYPES.h"

#define u8_SWPWM_TO_CH1_STOP_CH2			120
#define u8_SWPWM_TO_CH2_STOP_CH1			121
#define u8_SWPWM_TO_CH1_AND_CH2				122


#define u8_PWM_0_DUTY_PERCENT				0
#define u8_PWM_10_DUTY_PERCENT				10
#define u8_PWM_20_DUTY_PERCENT				20
#define u8_PWM_30_DUTY_PERCENT				30
#define u8_PWM_40_DUTY_PERCENT				40
#define u8_PWM_50_DUTY_PERCENT				50
#define u8_PWM_60_DUTY_PERCENT				60
#define u8_PWM_70_DUTY_PERCENT				70
#define u8_PWM_80_DUTY_PERCENT				80
#define u8_PWM_90_DUTY_PERCENT				90
#define u8_PWM_100_DUTY_PERCENT				100

void SWPWM_voidInit(void)                                                                ;
uint8_t SWPWM_u8ControlChannels(uint8_t u8_wantedPWMDuty,uint8_t u8_wantedChannelForPwm) ;


#endif
