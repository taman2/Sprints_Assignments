#ifndef __ULTRASONIC__
#define __ULTRASONIC__

#include "../../LIB/STD_TYPES.h"

#define u8_ULTRASONIC_PORT								PORTB
#define u8_ULTRASONIC_TRIG_PIN							PIN1
#define u8_ULTRASONIC_ECHO_PIN							PIN2

#define u8_ULTRASONIC_FALSE								0
#define u8_ULTRASONIC_TRUE								1 

#define u8_ULTRASONIC_WAIT_NEW_TRIG						2
#define u8_ULTRASONIC_TIME_BETWEEN_ECHO_AND_TRIG		60

#define u8_ULTRASONIC_OK								30
#define u8_ULTRASONIC_NOK								31

#define u8_ULTRASONIC_TRIG_TIME_US						12

#define u32_ULTRASONIC_CONVERT_FROM_MICRO_TO_SEC		1000000
#define u8_ULTRASONIC_CONVERT_TO_Cm						100

#define u16_ULTRASONIC_LIGHT_SPEED_IN_m_PER_SEC			340
#define u8_ULTRASONIC_HALF_ECHO_TIME					2

void ULTRASONIC_voidInit(void); 
uint8_t ULTRASONIC_u8GetObstacleDistInCm(uint16_t* pu16_returnDistInCm);


#endif
