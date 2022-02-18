#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "TIMER1_private.h"
#include "../LIB/STD_types.h"


#define PRESCALE_1    (1   )
#define PRESCALE_8    (8   )
#define PRESCALE_32   (32  )
#define PRESCALE_64   (64  )
#define PRESCALE_128  (128 )
#define PRESCALE_256  (256 )
#define PRESCALE_1028 (1028)

EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptEnable(void);
EN_timerOneOverFlowstatus_t TIMER1_OverFlowInterruptDisable(void);
EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptEnable(EN_timerOneChannel_t EN_channel);
EN_timerOneOutputCompareAstatus_t TIMER1_OutputCompareInterruptDisable(EN_timerOneChannel_t EN_channel);
EN_timerOneInitStatus_t TIMER1_init(uint16_t u16_prescaler);
void TIMER1_voidMicroSecDelay(uint16_t u16_usdelay);
EN_timerOneMicroDelayStatus_t TIMER1_getMicroDelayStatus(void);
void TIMER1_u32getCounts(uint32_t* pu32_clkCounts, uint8_t u8_status);

#endif 