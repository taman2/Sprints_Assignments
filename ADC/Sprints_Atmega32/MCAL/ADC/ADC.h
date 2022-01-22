/*
 * ADC.h
 *
 * Created: 1/22/2022 10:01:26 PM
 *  Author: Mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
#include "delay.h"
// Comment or delete this line to disable interrupt definition.
// You can still use the "adc_read" function if this is disabled.
//#define ENABLE_ADC_INT

#define ADC_PRESCALER_2 	0
#define ADC_PRESCALER_4 	2
#define ADC_PRESCALER_16 	4
#define ADC_PRESCALER_32 	5
#define ADC_PRESCALER_64 	6
#define ADC_PRESCALER_128 	7

#define _BV( bit ) ( 1<<(bit) )

#define ADC_VREF_AREF 	0
#define ADC_VREF_AVCC 	64
#define ADC_VREF_MISC1 	128
#define ADC_VREF_MISC2 	192
#define ADC0 0

uinteg16_t ADC_read(uinteg8_t prescaler, uinteg8_t vref, uinteg8_t pin);
void adc_start(uinteg8_t prescaler, uinteg8_t vref, uinteg8_t pin_qty, void (*handler)(uinteg8_t, uinteg16_t));
void adc_stop();





#endif /* ADC_H_ */