/*
 * EEPROM.c
 *
 * Created: 1/30/2022 11:28:36 PM
 *  Author: Mohamed salah
 */ 
#include "EEPROM.h"

enu_EE_Error_t EEWriteByte(uinteg16_t u16_addr, uinteg8_t u8_data)
{
	TWI_Start();
	if (TWI_GetStatus() != TWI_ST_OK)
	return EE_NOK;
	//select devise and send A2 A1 A0 address bits 
	TWI_Write((EEDEVADR)|(uinteg8_t)((u16_addr & 0x0700)>>7));
	if (TWI_GetStatus() != TWI_SLA_W_ACK)
	return EE_NOK;
	//send the rest of u16_addr
	TWI_Write((uinteg8_t)(u16_addr));
	if (TWI_GetStatus() != TWI_MASTER_DATA_TX_ACK)
	return EE_NOK;
	//write byte to eeprom
	TWI_Write(u8_data);
	if (TWI_GetStatus() != TWI_MASTER_DATA_TX_ACK)
	return EE_NOK;
	TWI_Stop();
	return EE_OK;
}
enu_EE_Error_t EEReadByte(uinteg16_t u16_addr, uinteg8_t *u8_data)
{
	TWI_Start();
	if (TWI_GetStatus() != TWI_ST_OK)
	return EE_NOK;
	//select devise and send A2 A1 A0 address bits
	TWI_Write((EEDEVADR)|((uinteg8_t)((u16_addr & 0x0700)>>7)));
	if (TWI_GetStatus() != TWI_SLA_W_ACK)
	return EE_NOK;
	//send the rest of address
	TWI_Write((uinteg8_t)(u16_addr));
	if (TWI_GetStatus() != TWI_MASTER_DATA_TX_ACK)
	return EE_NOK;
	//send start
	TWI_Start();
	if (TWI_GetStatus() != TWI_RST_OK)
	return EE_NOK;
	//select devise and send read bit
	TWI_Write((EEDEVADR)|((uinteg8_t)((u16_addr & 0x0700)>>7))|1);
	if (TWI_GetStatus() != TWI_SLA_R_ACK)
	return EE_NOK;
	*u8_data = TWI_ReadNACK();
	if (TWI_GetStatus() != TWI_MASTER_DATA_RX_NACK)
	return EE_NOK;
	TWI_Stop();
	return EE_OK;
}