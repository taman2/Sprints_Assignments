#ifndef EXTERNAL_INTERRUPTS_PRIVATE_H_
#define EXTERNAL_INTERRUPTS_PRIVATE_H_


#define GICR     ( *((volatile uint8_t*)0x5B))
#define IVCE    0
#define IVSEL   1
#define INT2    5
#define INT0    6
#define INT1    7
#define GIFR             *((volatile uint8_t*)0x5A)
#define SPMCR            *((volatile uint8_t*)0x57)
#define TWCR             *((volatile uint8_t*)0x56)
#define MCUCR            *((volatile uint8_t*)0x55)
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define SM0     4
#define SM1     5
#define SM2     6
#define SE      7
#define MCUCSR           *((volatile uint8_t*)0x54)
#define ISC2    6
#define PORF    0
#define EXTRF   1
#define BORF    2
#define WDRF    3
#define JTRF    4
#define JTD     7
#define OSCCAL_OCDR      *((volatile uint8_t*)0x51)
#define SFIOR            *((volatile uint8_t*)0x50)
void __vector_1(void) __attribute__((signal,used));
void __vector_2(void) __attribute__((signal,used));
void __vector_3(void) __attribute__((signal,used));

typedef enum
{
	EI_OK,
	EI_NOK
}enu_EI_ERROR;

#endif 