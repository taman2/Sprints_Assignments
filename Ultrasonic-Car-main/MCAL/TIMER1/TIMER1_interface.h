#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "TIMER1_private.h"
#include "../../LIB/STD_types.h"


#define PRESCALE_1    (1   )
#define PRESCALE_8    (8   )
#define PRESCALE_32   (32  )
#define PRESCALE_64   (64  )
#define PRESCALE_128  (128 )
#define PRESCALE_256  (256 )
#define PRESCALE_1028 (1028)
#define PERIODIC_TIME_IN_MS (1000)
#define COUNTS_PER_OVF      (250)

typedef enum{
	TIMER1_MS_DELAY_FINISHED  = 0,                                          // States that timer has finished counting
	TIMER1_DELAY_NFINISHED = 1,                                             // States that timer has not finished counting
	TIMER1_DELAY_STARTED   = 2,                                             // States that timer has started counting
	TIMER1_DELAY_NSTARTED  = 3                                              // States that timer has not started counting
}EN_timer1DelayStatus_t;

EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptEnable(void);
EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptDisable(void);
EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptEnable(EN_timerOneChannel_t EN_channel);
EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptDisable(EN_timerOneChannel_t EN_channel);
EN_timerOneInitStatus_t TIMER1_init(uint16_t u16_prescaler);
void TIMER1_voidMicroSecDelay(uint16_t u16_usdelay);
EN_timerOneMicroDelayStatus_t TIMER1_getMicroDelayStatus(void);
void TIMER1_u32getCounts(uint32_t* pu32_clkCounts, uint8_t u8_status);
EN_timer1DelayStatus_t TIMER1_msdelay(uint16_t mseconds);
void TIMER1_voidStartCounting(void);
void TIMER1_stop(void);
void TIMER1_setclbk(void (*ptrFun)(void));

#endif 
