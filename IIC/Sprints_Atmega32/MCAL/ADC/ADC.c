/*
 * ADC.c
 *
 * Created: 1/22/2022 10:01:14 PM
 *  Author: Mohamed
 */ 
#include "ADC.h"
 
void (*_adc_handler)(uinteg8_t pin, uinteg16_t);
volatile uinteg8_t _adc_pin_qty;
void ADC_Init(void)
{
		CLR_BIT(DDRA,0);			/* Make ADC port as input */
		ADCSRA = 0x87;			/* Enable ADC, fr/128  */
		ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
}

uinteg16_t ADC_read(uinteg8_t prescaler, uinteg8_t vref, uinteg8_t pin) 
{
#ifdef MUX5
	if (pin > 7) {
	ADCSRB |= _BV(MUX5);
	ADMUX  = vref | (pin - 8);
	} else {
	ADCSRB &= ~(_BV(MUX5));
	ADMUX = vref | pin;
}
#else
	ADMUX = vref | pin;
#endif
	
	ADCSRA = _BV(ADEN) | _BV(ADSC) | prescaler;
	while(!(ADCSRA & _BV(ADIF)));
	
	return (ADCL | (ADCH<<8));
}

void adc_start(uinteg8_t prescaler, uinteg8_t vref, uinteg8_t pin_qty, void (*handler)(uinteg8_t, uinteg16_t)) 
{
	_adc_handler = handler;
	_adc_pin_qty = pin_qty;
	ADMUX = vref;
#ifdef MUX5
	ADCSRB &= ~(_BV(MUX5));
#endif
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | prescaler;
}

void adc_stop() {
	ADCSRA = 0;
}

#ifdef ENABLE_ADC_INT
ISR(ADC_vect) {
	static uinteg8_t cur_pin = 0;
	
	_adc_handler(cur_pin, ADCL | (ADCH<<8));

	cur_pin++;
	if (cur_pin >= _adc_pin_qty)
		cur_pin = 0;
	
#ifdef MUX5
	if (cur_pin > 7) {
		ADCSRB |= _BV(MUX5);
		ADMUX = (ADMUX & 0xe0) | (cur_pin - 8);
	} else {
		ADCSRB &= ~(_BV(MUX5));
		ADMUX = (ADMUX & 0xe0) | cur_pin;
	}
#else
	ADMUX = (ADMUX & 0xe0) | cur_pin;
#endif

	ADCSRA |= _BV(ADSC);
}
#endif