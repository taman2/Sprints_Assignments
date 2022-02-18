/*
 * Sprints_Atmega32.c
 *
 * Created: 1/9/2022 12:28:39 AM
 * Author : Mohamed Salah Taman
 */ 
#include "../App/EE_APP/EE_APP.h"
int main(void)
{
	EE_APP_Init();
    while (1) 
    {

	  EE_APPControl();
	}
}

		/*
		
#define SLAVE_ADDRESS_WRITE 0x0A
#define SLAVE_ADDRESS_READ 0x0B
#define  EEPROM_BYTE_ADD 0x0000

			uinteg8_t u8_SentByte=0x0A;
			uinteg8_t u8_RecivedByte=0x07;

		enu_TWI_STATE=EEWriteByte(EEPROM_BYTE_ADD,u8_SentByte);
		if(enu_TWI_STATE == EE_OK)
		{
			enu_TWI_STATE=EEReadByte(EEPROM_BYTE_ADD,&u8_RecivedByte);
			if(enu_TWI_STATE == EE_OK)
			GPIO_Write( &PORTB,u8_RecivedByte,SET);
		}
		else
		GPIO_Write( &PORTB,((PIN7|PIN6|PIN5|PIN4)),RESET);*/