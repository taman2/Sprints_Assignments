 #include "EXTERNAL_interrupts.h"

void(*External_Int0_Fun)(void)=NULL_POINTER;/*POINTER TO FUCTION CARRY THE ADRESS OF INT0_ISR_FUCTION  */
void(*External_Int1_Fun)(void)=NULL_POINTER;/*POINTER TO FUCTION CARRY THE ADRESS OF INT1_ISR_FUCTION  */
void(*External_Int2_Fun)(void)=NULL_POINTER;/*POINTER TO FUCTION CARRY THE ADRESS OF INT2_ISR_FUCTION  */
enu_EI_ERROR External_Interrupts_Init(uint8_t INT_Num,uint8_t Interrupt_triggering ,void(*External_Int_Fun_Address)(void))
{
	if(External_Int_Fun_Address== NULL_POINTER)
	{
		return EI_NOK;
	}
	if(INT_Num==0)
	{
		External_Int0_Fun=External_Int_Fun_Address;
		GICR |= 1<<INT0;		/* Enable INT0*/
		if(Interrupt_triggering==RISING_EDGE)
		MCUCR |= 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
		else if(Interrupt_triggering==FALLING_EDGE)
		MCUCR |= 1<<ISC01 ;  /* Trigger INT0 on falling edge */
		else
		MCUCR |= 1<<ISC00  ;  /* Trigger INT0 on falling edge */
	}
	else if(INT_Num==1)
	{
		External_Int1_Fun=External_Int_Fun_Address;
		GICR |= 1<<INT1;		/* Enable INT1*/
		if(Interrupt_triggering==RISING_EDGE)
		MCUCR |= 1<<ISC11 | 1<<ISC10;  /* Trigger INT1 on rising edge */
		else if(Interrupt_triggering==FALLING_EDGE)
		MCUCR |= 1<<ISC11 ;  /* Trigger INT1 on falling edge */
		else
		MCUCR |= 1<<ISC10  ;  /* Trigger INT1 on falling edge */
	}
	else if(INT_Num==2)
	{
		External_Int2_Fun=External_Int_Fun_Address;
		GICR |= 1<<INT2;		/* Enable INT2*/
		if(Interrupt_triggering==RISING_EDGE)
		MCUCSR |= 1<<ISC2; /* Trigger INT2 on rising edge */
		else
		MCUCSR &= ~(1<<ISC2);  /* Trigger INT2 on falling edge */
		
	}
	else
	return EI_NOK;
	return EI_OK;
}

/*external interrupt 00 ISR*/
void __vector_1(void)
{
	External_Int0_Fun();
}
/*external interrupt 01 ISR*/
void __vector_2(void)
{
	External_Int1_Fun();
}
/*external interrupt 02 ISR*/
void __vector_3(void)
{
	External_Int2_Fun();
}