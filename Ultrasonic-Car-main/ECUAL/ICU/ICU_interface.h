#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

#include "../../LIB/STD_types.h"

#define u8_FALLING_EDGE_HAPPENED 1
#define u8_RISING_EDGE_HAPPENED  0
#define u8_TOGGEL_EDGE_HAPPENED  2
#define u8_ICU_WAITING_NEW_EDGE  3

typedef enum
{
	ICU_OK,
	ICU_NOK,
	ICU_NREADY
}enu_ICU_ERROR;

enu_ICU_ERROR ICU_enuInit();
void ICU_voidExternalInterrupt02RisgISR(void);
void ICU_voidExternalInterrupt02FallingISR(void);
/* it calculates the period which signal is HIGH using timer01  */
enu_ICU_ERROR ICU_u8SingnalOnTime(uint32_t *pu32_OnTime);

#endif 