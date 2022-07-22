#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "../../LIB/STD_types.h"
#include "../../LIB/BIT_math.h"
#include "EXTERNAL_interruptsPrivate.h"


#define FALLING_EDGE 1
#define RISING_EDGE  2
#define TOGGLE       3

#define EXTERNAL_INT_00			0
#define EXTERNAL_INT_01			1
#define EXTERNAL_INT_02			2



void(*External_Int0_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT0_FUCTION  */
void(*External_Int1_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT1_FUCTION  */
void(*External_Int1_Fun)(void);/*POINTER TO FUCTION CARRY THE ADRESS OF INT2_FUCTION  */

enu_EI_ERROR External_Interrupts_Init(uint8_t INT_Num,uint8_t Interrupt_triggering ,void(*External_Int_Fun_Address)(void));


#endif /* EXTERNAL_INTERRUPTS_H_ */