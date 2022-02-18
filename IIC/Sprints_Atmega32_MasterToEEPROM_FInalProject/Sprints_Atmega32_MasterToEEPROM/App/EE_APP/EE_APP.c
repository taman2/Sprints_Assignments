/*
 * EE_APP.c
 *
 * Created: 2/18/2022 2:59:03 AM
 *  Author: Mohamed
 */ 
#include "../App/EE_APP/EE_APP.h"
uinteg8_t *gpu8_RreadComand ="READ";
uinteg8_t *gpu8_WriteComand ="WRITE";
uinteg8_t *gpu8_OkComand ="OK";
uinteg8_t *gpu8_DataInfo ="Data stored is ";
uinteg8_t EEPROM_BYTE_ADD=0;
uinteg8_t u8_RecivedByte=0;
enu_EE_Error_t enu_TWI_STATE;
uinteg8_t garr_Buffer[BUFFER_SIZE]="HI..Sprints";
 
void EE_APP_Init(void)
{
	
	TWI_Init();
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4|PIN3|PIN2|PIN1|PIN0)),OutPut);
	USART_Init(&gstr_USART_Config);
	genu_EE_APPState=_WAITE;
}

void check_command(uinteg8_t *pu8_buffer)
{
	USART_Recieve_Packet(pu8_buffer,ENTER_PRESSED);
	if(strcmp(pu8_buffer,gpu8_RreadComand)== 0 )
	{
		USART_Recieve_Packet(pu8_buffer,ENTER_PRESSED);
		EEPROM_BYTE_ADD=stringToBinary(pu8_buffer);
		USART_Send_Packet(gpu8_OkComand,NULL_CHAR);
		USART_Transmit(ENTER_PRESSED);
		genu_EE_APPState = _READ;
		
	}
	else if(strcmp(pu8_buffer,gpu8_WriteComand)== 0)
	{
		USART_Recieve_Packet(pu8_buffer,ENTER_PRESSED);
		EEPROM_BYTE_ADD=stringToBinary(pu8_buffer);
		USART_Send_Packet(gpu8_OkComand,NULL_CHAR);
		USART_Transmit(ENTER_PRESSED);
		u8_RecivedByte=USART_Receive();
		USART_Receive();
		USART_Send_Packet(gpu8_OkComand,NULL_CHAR);
		USART_Transmit(ENTER_PRESSED);
		genu_EE_APPState = _WRITE;
	}
	else
	{
		
	}
}
void EE_APPControl(void)
{
	switch(genu_EE_APPState)
	{
		case _READ:
			enu_TWI_STATE=EEReadByte((uinteg16_t)EEPROM_BYTE_ADD,&u8_RecivedByte);
			if(enu_TWI_STATE == EE_OK)
			{
				USART_Send_Packet(gpu8_DataInfo,NULL_CHAR);
				USART_Transmit(u8_RecivedByte);
				USART_Transmit(ENTER_PRESSED);
			}
			else
			{
				USART_Send_Packet(" READ ERROR",NULL_CHAR);
				USART_Transmit(ENTER_PRESSED);
			}
			genu_EE_APPState=_WAITE;
			break;
			
		case _WRITE:
			enu_TWI_STATE=EEWriteByte((uinteg16_t)EEPROM_BYTE_ADD,u8_RecivedByte);
			if(enu_TWI_STATE != EE_OK)
			{
				USART_Send_Packet(" WRITE ERROR",NULL_CHAR);
				USART_Transmit(ENTER_PRESSED);				
			}
			genu_EE_APPState=_WAITE;
			break;
		case _WAITE:
			check_command(garr_Buffer);
			break;	

				
	}
}
uinteg8_t stringToBinary(uinteg8_t *pu8_str)
{
	uinteg8_t u8_I=0;
	uinteg8_t u8_Temp1=0;
	uinteg8_t u8_Temp2=0;

	for(u8_I=0;u8_I<8;u8_I++)
	{
		u8_Temp1=pu8_str[u8_I]-'0';
		u8_Temp2+=(u8_Temp1*pow(2,(7-u8_I)));
	}
	return u8_Temp2;
}
