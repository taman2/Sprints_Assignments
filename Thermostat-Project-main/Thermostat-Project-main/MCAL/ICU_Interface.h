/*
 * ICU_Interface.h
 *
 * Created: 2/12/2022 7:37:13 PM
 *  Author: Mohamed salah taman
 */ 


#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_


#define u8_FALLING_EDGE_HAPPENED 1
#define u8_RISING_EDGE_HAPPENED  0
#define u8_TOGGEL_EDGE_HAPPENED  2
#define u8_ICU_WAITING_NEW_EDGE  3

enu_ICU_ERROR ICU_enuInit();
void ICU_voidExternalInterrupt01ISR(void);
/* it calculates the period which signal is HIGH using timer01  */
enu_ICU_ERROR ICU_u8SingnalOnTime(uint32_t *pu32_OnTime);


#endif /* ICU_INTERFACE_H_ */