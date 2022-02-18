/*
 * AtmegaPort.h
 *
 * Created: 09/01/2022 01:13:33
 *  Author: Mohamed salah Taman
 */ 


#ifndef AtmegaPort_H_
#define AtmegaPort_H_

#include "Data_types.h"
/*Configuration by user*/
#define ATMEGA 32
/*The designer of driver only play on this defines*/
#if    ATMEGA==8
#define  No_of_ports 3
#elif  ATMEGA==16
#define  No_of_ports 4
#elif ATMEGA==32
#define  No_of_ports 4
#elif ATMEGA==128
#define  No_of_ports 6
#endif

#define  DataBus     8
#define  PortSize    DataBus


#define  EnableGeneralInterrupt()       SET_BIT(SREG,I)
#define  DisableGeneralInterrupt()      CLR_BIT(SREG,I)
#define NULL_POINTER ((void *)0)
//TWI Registers
#define TWBR    ( *((volatile uinteg8_t* )(0X20)) )
#define TWSR    ( *((volatile uinteg8_t* )(0X21)) )
#define TWAR    ( *((volatile uinteg8_t* )(0X22)) )
#define TWDR    ( *((volatile uinteg8_t* )(0X23)) )
//ADC Registers
#define ADCL    ( *((volatile uinteg8_t* )(0X24)) )
#define ADCH    ( *((volatile uinteg8_t* )(0X25)) )
#define ADCSRA  ( *((volatile uinteg8_t* )(0X26)) )
#define ADMUX   ( *((volatile uinteg8_t* )(0X27)) )
//Analog Comparator Registers
#define ACSR    ( *((volatile uinteg8_t* )(0X28)) )
/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0
//UART Registers
#define UBRRL   ( *((volatile uinteg8_t* )(0X29)) )
#define UCSRB   ( *((volatile uinteg8_t* )(0X2A)) )
#define UCSZ2    2
#define TXEN     3
#define RXEN     4
#define UDRIE    5
#define TXCIE    6
#define RXCIE    7
#define UCSRA   ( *((volatile uinteg8_t* )(0X2B)) )
#define UDRE     5
#define RXC      7
#define UDR     ( *((volatile uinteg8_t* )(0X2C)) )


//DIO Registers
#define PIND    ( *((volatile uinteg8_t* )(0X30)) )
#define DDRD    ( *((volatile uinteg8_t* )(0X31)) )
#define PORTD   ( *((volatile uinteg8_t* )(0X32)) )
#define PINC    ( *((volatile const uinteg8_t* )(0X33)) )
#define DDRC    ( *((volatile uinteg8_t* )(0X34)) )
#define PORTC   ( *((volatile uinteg8_t* )(0X35)) )
#define PINB    ( *((volatile const uinteg8_t* )(0X36)) )
#define DDRB    ( *((volatile uinteg8_t* )(0X37)) )
#define PORTB   ( *((volatile uinteg8_t* )(0X38)) )
#define PINA    ( *((volatile const uinteg8_t* )(0X39)) )
#define DDRA    ( *((volatile uinteg8_t* )(0X3A)) )
#define PORTA   ( *((volatile uinteg8_t* )(0X3B)) )
#define  P0     0     
#define  P1     1
#define  P2     2
#define  P3     3
#define  P4     4
#define  P5     5
#define  P6     6
#define  P7     7


//EEPROM Registers
#define EECR    ( *((volatile uinteg8_t* )(0X3C)) )
#define EEDR    ( *((volatile uinteg8_t* )(0X3D)) )
#define EEARL   ( *((volatile uinteg8_t* )(0X3E)) )
#define EEARH   ( *((volatile uinteg8_t* )(0X3F)) )
//The rest of UART Registers
#define UCSRC   ( *((volatile uinteg8_t* )(0X40)) )
#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPMO     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7
#define UBRRH   ( *((volatile uinteg8_t* )(0X40)) )
#define WDTCR   ( *((volatile uinteg8_t* )(0X41)) )
//Asynchronous Timer Registers
#define ASSR    ( *((volatile uinteg8_t* )(0X42)) )
#define OCR2    ( *((volatile uinteg8_t* )(0X43)) )
#define TCNT2   ( *((volatile uinteg8_t* )(0X44)) )
#define TCCR2   ( *((volatile uinteg8_t* )(0X45)) )
//Timer1 Registers
#define ICR1	( *((volatile uinteg16_t* )(0X46)) )
#define ICR1L	( *((volatile uinteg8_t* )(0X46)) )
#define ICR1H   ( *((volatile uinteg8_t* )(0X47)) )
#define OCR1B   ( *((volatile uinteg16_t*)(0X48)) )
#define OCR1BL  ( *((volatile uinteg8_t* )(0X48)) )
#define OCR1BH  ( *((volatile uinteg8_t* )(0X49)) )
#define OCR1A   ( *((volatile uinteg16_t* )(0X4A)) )
#define OCR1AL  ( *((volatile uinteg8_t* )(0X4A)) )
#define OCR1AH  ( *((volatile uinteg8_t* )(0X4B)) )
#define TCNT1   ( *((volatile uinteg16_t* )(0X4C)) )
#define TCNT1L  ( *((volatile uinteg8_t* )(0X4C)) )
#define TCNT1H  ( *((volatile uinteg8_t* )(0X4D)) )
#define TCCR1B  ( *((volatile uinteg8_t* )(0X4E)) )
#define TCCR1A  ( *((volatile uinteg8_t* )(0X4F)) )
//Special Function Register
#define SFIOR   ( *((volatile uinteg8_t* )(0X50)) )
//On-Chip Debug Register
#define OCDR    ( *((volatile uinteg8_t* )(0X51)) )
////On-Chip Debug Register
#define OSCCAL  ( *((volatile uinteg8_t* )(0X51)) )
//TIMER0 Registers
#define TCNT0   ( *((volatile uinteg8_t* )(0X52)) )
#define TCCR0   ( *((volatile uinteg8_t* )(0X53)) )
/* TCCR0 ********************************************/
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0
//MCU Status and Control Registers
#define MCUCSR  ( *((volatile uinteg8_t* )(0X54)) )
#define MCUCR   ( *((volatile uinteg8_t* )(0X55)) )
//Register of TWO WIRE Control Register
#define TWCR    ( *((volatile uinteg8_t* )(0X56)) )

#define SPMCR   ( *((volatile uinteg8_t* )(0X57)) )
/*Timer's Interrupt Flags*/
#define TIFR    ( *((volatile uinteg8_t* )(0X58)) )
#define TOV0    0
#define OCF0    1
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
#define TOV2    6
#define OCF2    7

#define TIMSK   ( *((volatile uinteg8_t* )(0X59)) )
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0
//General Interrupt Flags
#define GIFR    ( *((volatile uinteg8_t* )(0X5A)) )
#define GICR    ( *((volatile uinteg8_t* )(0X5B)) )
#define INT1    7
#define INT0    6
#define INT2    5
//TIMER0 Output Compare Register
#define OCR0    ( *((volatile uinteg8_t* )(0X5C)) )
//Stack pointer Register
#define SPL     ( *((volatile uinteg8_t* )(0X5D)) )
#define SPH     ( *((volatile uinteg8_t* )(0X5E)) )
//Status Register
#define SREG    ( *((volatile uinteg8_t* )(0X5F)) )
#define I       7

//SPI Registers
#define SPCR    ( *((volatile uinteg8_t* )(0X2D)) )
#define SPCR_SPR0 0
#define SPCR_SPR1 1
#define SPCR_CPHA 2
#define SPCR_CPOL 3
#define SPCR_MSTR 4
#define SPCR_DORD 5
#define SPCR_SPE  6
#define SPCR_SPIE 7
#define SPSR    ( *((volatile uinteg8_t* )(0X2E)) )
#define SPSR_SPIF  7
#define SPSR_WCOL  6
#define SPSR_SPI2X 0
#define SPDR    ( *((volatile uinteg8_t* )(0X2F)) )
/*TWC REGs*/
#define TWDR	( *((volatile uinteg8_t* )(0X23)) )
#define TWAR	( *((volatile uinteg8_t* )(0X22)) )
#define TWSR	( *((volatile uinteg8_t* )(0X21)) )
#define TWBR	( *((volatile uinteg8_t* )(0X20)) )
/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

/*******************************************Interrupt Vector Table********************/
/* External Interrupt Request 0 */
#define INT0_vect_num		1
#define INT0_vect			__VECTOR_1
#define SIG_INTERRUPT0		__VECTOR(1)

/* External Interrupt Request 1 */
#define INT1_vect_num		2
#define INT1_vect			__VECTOR_2
#define SIG_INTERRUPT1			__VECTOR_2

/* External Interrupt Request 2 */
#define INT2_vect_num		3
#define INT2_vect			__VECTOR_3
#define SIG_INTERRUPT2			__VECTOR(3)

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect_num	4
#define TIMER2_COMP_vect		__VECTOR_4
#define SIG_OUTPUT_COMPARE2		__VECTOR(4)

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect_num		5
#define TIMER2_OVF_vect			__VECTOR_5
#define SIG_OVERFLOW2			__VECTOR(5)

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect_num	6
#define TIMER1_CAPT_vect		__VECTOR_6
#define SIG_INPUT_CAPTURE1		__VECTOR(6)

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect_num	7
#define TIMER1_COMPA_vect		__VECTOR_7
#define SIG_OUTPUT_COMPARE1A		__VECTOR(7)

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect_num	8
#define TIMER1_COMPB_vect		__VECTOR_8
#define SIG_OUTPUT_COMPARE1B		__VECTOR(8)

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect_num		9
#define TIMER1_OVF_vect			__VECTOR_9
#define SIG_OVERFLOW1			__VECTOR(9)

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect_num	10
#define TIMER0_COMP_vect		__VECTOR_10
#define SIG_OUTPUT_COMPARE0		__VECTOR(10)

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect_num		11
#define TIMER0_OVF_vect			__VECTOR_11
#define SIG_OVERFLOW0			__VECTOR(11)

/* Serial Transfer Complete */
#define SPI_STC_vect_num		12
#define SPI_STC_vect			__VECTOR_12
#define SIG_SPI				__VECTOR(12)

/* USART, Rx Complete */
#define USART_RXC_vect_num		13
#define USART_RXC_vect			__VECTOR_13
#define SIG_USART_RECV			__VECTOR(13)
#define SIG_UART_RECV			__VECTOR(13)

/* USART Data Register Empty */
#define USART_UDRE_vect_num		14
#define USART_UDRE_vect			__VECTOR_14
#define SIG_USART_DATA			__VECTOR(14)
#define SIG_UART_DATA			__VECTOR(14)

/* USART, Tx Complete */
#define USART_TXC_vect_num		15
#define USART_TXC_vect			__VECTOR_15
#define SIG_USART_TRANS			__VECTOR(15)
#define SIG_UART_TRANS			__VECTOR(15)

/* ADC Conversion Complete */
#define ADC_vect_num		16
#define ADC_vect			__VECTOR_16
#define SIG_ADC				__VECTOR(16)

/* EEPROM Ready */
#define EE_RDY_vect_num		17
#define EE_RDY_vect			__VECTOR_17
#define SIG_EEPROM_READY		__VECTOR(17)

/* Analog Comparator */
#define ANA_COMP_vect_num		18
#define ANA_COMP_vect			__VECTOR_18
#define SIG_COMPARATOR			__VECTOR(18)

/* 2-wire Serial Interface */
#define TWI_vect_num		19
#define TWI_vect			__VECTOR_19
#define SIG_2WIRE_SERIAL		__VECTOR(19)

/* Store Program Memory Ready */
#define SPM_RDY_vect_num		20
#define SPM_RDY_vect			__VECTOR_20
#define SIG_SPM_READY			__VECTOR(20)
/********************************ISRs****************************/
void __vector_1(void) __attribute__((signal,used));
void __vector_2(void) __attribute__((signal,used));
void __vector_3(void) __attribute__((signal,used));
void __vector_4(void) __attribute__((signal,used));
void __vector_5(void) __attribute__((signal,used));
void __vector_6(void) __attribute__((signal,used));
void __vector_7(void) __attribute__((signal,used));
void __vector_8(void) __attribute__((signal,used));
void __vector_9(void) __attribute__((signal,used));
void __vector_10(void) __attribute__((signal,used));
void __vector_11(void) __attribute__((signal,used));
void __vector_12(void) __attribute__((signal,used));
void __vector_13(void) __attribute__((signal,used));
void __vector_14(void) __attribute__((signal,used));
void __vector_15(void) __attribute__((signal,used));
void __vector_16(void) __attribute__((signal,used));
void __vector_17(void) __attribute__((signal,used));
void __vector_18(void) __attribute__((signal,used));
void __vector_19(void) __attribute__((signal,used));
void __vector_20(void) __attribute__((signal,used));
/**************************ERROR*******************************/
typedef enum
{
	DIO_ERROR_NOK=0x00,
    DIO_ERROR_OK=0x01,
	TIMER_ERROR_OK=0x10,
	TIMER_ERROR_NOK=0x11
}genu_ERROR_t;
genu_ERROR_t genu_ERROR;
#endif /* AtmegaPort_H_ */