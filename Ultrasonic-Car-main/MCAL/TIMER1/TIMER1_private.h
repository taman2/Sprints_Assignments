#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

typedef enum{
	TIMER1_INITIALIZED     = 1,
	TIMER1_NOT_INITIALIZED = 0
	}EN_timerOneInitStatus_t;
	
typedef enum{
	TIMER1_US_DELAY_FINISHED     = 1,
	TIMER1_DELAY_NOT_FINISHED = 0
	}EN_timerOneMicroDelayStatus_t;
	
typedef enum{
	TIMER1_OF_ENABLED  = 1,
	TIMER1_OF_DISABLED = 0
	}EN_timerOneOverFlowstatus_t;

typedef enum{
	TIMER1_OCA_ENABLED  = 1,
	TIMER1_OCA_DISABLED = 0
	}EN_timerOneOutputCompareAstatus_t;
	
typedef enum{
	CHA = 1,
	CHB = 0
}EN_timerOneChannel_t;

#define BOTTOM               (65285)
#define TOP                  (65535)
#define COUNTS_PER_OVERFLOW  (250)
#define NULL                 (0)
#define TIMER1_OVERFLOW      (1)
#define TIMER1_COMPARE_MATCH (2)
#define TRUE                 (1)
#define FALSE                (0)

/****************************************************************************/
/*                                                                          */
/*                   Timers Interrupt Flag Register Bits                    */
/*                                                                          */
/****************************************************************************/

#define TOV1  (2)
#define OCF1B (3)
#define OCF1A (4)
#define ICF1  (5)

/****************************************************************************/
/*                                                                          */
/*                   Timers Interrupt Masking Register Bits                 */
/*                                                                          */
/****************************************************************************/

#define TOIE1  (2)
#define OCIE1B (3)
#define OCIE1A (4)
#define TICIE1 (5)


#define CS10  (0)
#define CS11  (1)
#define CS12  (2)

void TIMER1_setCountOverFlow(void);


#endif 
