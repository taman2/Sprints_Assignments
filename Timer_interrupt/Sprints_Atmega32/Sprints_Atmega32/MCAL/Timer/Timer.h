/*
 * Timer.h
 *
 * Created: 1/15/2022 3:05:39 PM
 *  Author: Mohamed
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "AT32_Dio.h"

#define TIMER0_TCNT_INIT_VALUE  131

typedef enum
{
	TIMER0,
	TIMER2
}enu_TimerId_t;
typedef enum
{
	TIMER_NORMAL_MODE=(0x00),
	TIMER_CTC_MODE=(1<<WGM01),
	TIMER_PHASE_CORRECT_PWM_MODE=(1<<WGM00),
	TIMER_FAST_PWM_MODE=((1<WGM01)|(1<WGM00))

}enu_TimerWaveModes_t;

typedef enum
{
	NO_CLK=(0x00),
	PRESCALER_1=(0X01),
	PRESCALER_8=(0X02),
	PRESCALER_64=(0X03),
	PRESCALER_256=(0X04),
	PRESCALER_1024=(0X05),
	EXTERNAL_CLK_Tx_RISING=(0X06),
	EXTERNAL_CLK_Tx_FALLING=(0X07)
}enu_TimerCLK_Source_t;
typedef enum
{
	NO_WAVE_ON_OC=0X00,
	TOGGLE_OCX_ON_COMPARE_MATCH=(1<<COM00),
	CLEAR_OCX_ON_COMPARE_MATCH=(1<<COM01),
	SET_OCX_ON_COMPARE_MATCH=((1<<COM00) | (1<<COM01))
}enu_TimerWaveOn_OCX_t;
typedef enum
{
	DISABLE_INTERRUPT=0x00,
	ENABLE_INTERRUPT=0x01
}enu_TimerInterrupt_t;
/********************************* structs ***************************************************/
typedef struct
{
	enu_TimerId_t enu_TimerId;
	enu_TimerWaveModes_t enu_TimerWaveMode;
	enu_TimerCLK_Source_t enu_TimerCLK_Source;
	enu_TimerWaveOn_OCX_t enu_TimerWaveOn_OC_PIN;
	enu_TimerInterrupt_t enu_TimerOverFlowInterrupt;
	enu_TimerInterrupt_t enu_TimerCompareMatchInterrupt;
	
}str_TimerConfing_t;
extern str_TimerConfing_t gstr_Timer0Confing;
extern str_TimerConfing_t gstr_Timer2Confing;


/****************************function prototypes*******************************************/

genu_ERROR_t Timer_Init(str_TimerConfing_t *str_TimerConfing);
genu_ERROR_t Timer0_delayMs(uinteg32_t u32_delay);
genu_ERROR_t Timer_SetTimerCountReg(enu_TimerId_t enu_TimerId,uinteg8_t u8_TCNT_Value);
void Timer_OVF_ISR(void);



#endif /* TIMER_H_ */
