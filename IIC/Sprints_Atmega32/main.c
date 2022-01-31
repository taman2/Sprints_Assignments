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
	TWI_Init();
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	//USART_Init(&gstr_USART_Config);
	
    while (1) 
    {

	 
		enu_TWI_STATE=TWI_msterSendSLV_RW(SLAVE_ADDRESS_WRITE);
		if(enu_TWI_STATE == TWI_OK)
		{
			TWI_Write(0x0f);
			TWI_Stop();
			GPIO_Write( &PORTB,((PIN7|PIN6|PIN5|PIN4)),SET);
		}
		else
		GPIO_Write( &PORTB,((PIN7|PIN6|PIN5|PIN4)),RESET);
	  
	}
}

