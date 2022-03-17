#include "GLOBAL_INTERRUPT.h"
#include "../../LIB/atmega32_registers.h"

void GI_enable(void)
{
	Ru8_SREG |= (ONE << GLOBAL_INTERRUPT_PIN);
}

void GI_disable(void)
{
	Ru8_SREG &= ~(ONE << GLOBAL_INTERRUPT_PIN);
}