/*
* Sprints_Atmega32.c
*
* Created: 1/9/2022 12:28:39 AM
* Author : Mohamed Salah Taman
*/
#define F_CPU 8000000UL

#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
#include "delay.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KeyPad/KeyPad.h"
#include "../MCAL/UART/UART_CONFIG.h"
#include "IIC_Interface.h"

#define SLAVE_ADDRESS_WRITE 0x0A
#define SLAVE_ADDRESS_READe 0x0B


int main(void)
{
	
	enu_TWI_STATE_t enu_TWI_STATE;
	uinteg8_t u8_data;
	GPIO_Init ( _PORTD,((PIN7|PIN6|PIN5|PIN4|PIN3|PIN2|PIN1|PIN0)),OutPut);
	TWI_Init();
	while (1)
	{
		enu_TWI_STATE=TWI_SlaveListen();
		/* Make sure that Own SLA+W received &ack returned */
		if(enu_TWI_STATE==TWI_OWN_SLA_W_ACK||enu_TWI_STATE==TWI_OWN_SLA_W_ACK2)	
		enu_TWI_STATE=TWI_ReadACK_returnState(&u8_data);
		/*Make sure that data received and ACK SENT by slave*/
		if(enu_TWI_STATE== TWI_SLAVE_DATA_RX_ACK || enu_TWI_STATE == TWI_GENERAL_CALL_DATA_ACK )
		GPIO_Write(&PORTD,u8_data,SET);
		
	}
}

