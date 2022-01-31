/*
 * IIC.c
 *
 * Created: 1/30/2022 2:11:25 AM
 *  Author: Mohamed Salah Taman
 */ 

#include "IIC_Interface.h"
	
void TWI_Init(void)
{
#if TWI_MODE == TWI_MASTER_MODE
	TWBR = BITRATE(TWI_PRESCALERBITS);
#else
	/* Assign Address in TWI address register */
    TWAR=SLAVE_ADD;		
	/* Enable TWI, Enable ack generation */
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEA);						
	//enable TWI
	SET_BIT(TWCR,TWEN);
#endif
}
void TWI_Start(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);	
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);
}
//send stop signal
void TWI_Stop(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWEN);
}
void TWI_Write(uinteg8_t u8_data)
{
	TWDR = u8_data;
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);
}
uinteg8_t TWI_ReadACK(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWEA);
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);
	return TWDR;
}
//read byte with NACK
uinteg8_t TWI_ReadNACK(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);

	return TWDR;
}
uinteg8_t TWI_GetStatus(void)
{
	uinteg8_t u8_status;
	//mask status
	u8_status = TWSR & 0xF8;
	return u8_status;
}
enu_TWI_STATE_t TWI_ReadACK_returnState(uinteg8_t *u8ptr_dataTemp)
{
	enu_TWI_STATE_t u8_state;
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWEA);
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);
	u8_state=TWI_GetStatus();
	if(u8_state== TWI_SLAVE_DATA_RX_ACK || u8_state == TWI_GENERAL_CALL_DATA_ACK )
	{
			*u8ptr_dataTemp=TWDR;
	}
	return u8_state;
}
enu_TWI_STATE_t TWI_ReadNACK_returnState(uinteg8_t *u8ptr_dataTemp)
{
	uinteg8_t u8_state;
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until operation complete*/
	while (GET_BIT(TWCR,TWINT) == 0);
	u8_state=TWI_GetStatus();
	if(u8_state== TWI_SLAVE_DATA_RX_NACK || u8_state == TWI_GENERAL_CALL_DATA_NACK )
	{
		*u8ptr_dataTemp=TWDR;
	}
	return u8_state;
}
enu_TWI_STATE_t  TWI_msterSendSLV_RW(uinteg8_t u8_SLAVE_ADDRESS_WRITE)
{
	uinteg8_t u8_state=0;
	TWI_Start();
	u8_state=TWI_GetStatus();
	if(u8_state!=TWI_ST_OK)
	return TWI_NOK;
	TWI_Write(u8_SLAVE_ADDRESS_WRITE);
	u8_state=TWI_GetStatus();
	if(u8_state!=TWI_SLA_W_ACK)
	return TWI_SLA_W_NACK;
	return TWI_OK;
}

enu_TWI_STATE_t TWI_SlaveListen(void)
{
	while(1)
	{
		uinteg8_t status;											/* Declare variable */
		while(!(TWCR&(1<<TWINT)));									/* Wait to be addressed */
		status=TWSR&0xF8;											/* Read TWI status register */
		if(status==TWI_OWN_SLA_W_ACK||status==TWI_OWN_SLA_W_ACK2)	/* Own SLA+W received &ack returned */
		return status;												/* Return TWI_OWN_SLA_W_ACK to indicate ack returned */
		if(status==TWI_OWN_SLA_R_ACK||status==TWI_OWN_SLA_R_ACK2)	/* Own SLA+R received &ack returned */
		return status;												/* Return TWI_OWN_SLA_R_ACK to indicate ack returned */
		if(status==TWI_GENERAL_CALL||status==TWI_GENERAL_CALL2)		/* General call received &ack returned */
		return status;												/* Return 1 to indicate ack returned */
		if(status == TWI_SLV_RECEIVED_STOP)
		return status;												/* Return 1 to indicate ack returned */
		else
		continue;													/* Else continue */
	}		
}
// char I2C_Slave_Receive()
// {
// 	uinteg8_t status;											/* Declare variable */
// 	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);						/* Enable TWI & generation of ack */
// 	while(!(TWCR&(1<<TWINT)));									/* Wait until TWI finish its current job */
// 	status=TWSR&0xF8;											/* Read TWI status register */
// 	if(status==0x80||status==0x90)								/* Check for data received &ack returned */
// 	return TWDR;												/* If yes then return received data */
// 
// 	/* Check for data received, nack returned & switched to not addressed slave mode */
// 	if(status==0x88||status==0x98)
// 	return TWDR;												/* If yes then return received data */
// 	if(status==0xA0)											/* Check wether STOP/REPEATED START */
// 	{	
// 		TWCR|=(1<<TWINT);										/* Clear interrupt flag & return -1 */
// 		return -1;
// 	}
// 	else
// 	return -2;			/* Else return -2 */
// }