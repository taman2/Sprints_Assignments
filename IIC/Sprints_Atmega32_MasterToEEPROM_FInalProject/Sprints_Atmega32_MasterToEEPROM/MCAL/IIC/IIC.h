/*
 * IIC.h
 *
 * Created: 1/30/2022 2:11:37 AM
 *  Author: Mohamed Salah Taman
 */ 


#ifndef IIC_H_
#define IIC_H_

#include "AT32_Dio.h"
#include "math.h"

#define TWI_PRESCALER_1  0X00
#define	TWI_PRESCALER_4  0X01
#define	TWI_PRESCALER_16 0X02
#define	TWI_PRESCALER_64 0X03

#define TWI_MASTER_MODE 0x0A
#define TWI_SLAVE_MODE 0x0B

#define	 BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
typedef enum
{
	TWI_OK,
	TWI_NOK,
/*Status Codes for Master Transmitter Mode*/	
	TWI_ST_OK=0x08,
	TWI_RST_OK=0x10,
	TWI_SLA_W_ACK=0x18,
	TWI_SLA_W_NACK=0x20,	
	TWI_MASTER_DATA_TX_ACK=0x28,
	TWI_MASTER_DATA_TX_NACK=0x30,
	TWI_SLA_W_AR_LOST=0x38,
/*Status Codes for Master Receiver Mode*/	
	TWI_SLA_R_ACK=0x40,
	TWI_SLA_R_NACK=0x48,
	TWI_MASTER_DATA_RX_ACK=0x50,
	TWI_MASTER_DATA_RX_NACK=0x58,
	TWI_SLA_R_AR_LOST=0x38,
/*Status Codes for Slave Receiver Mode*/
	TWI_OWN_SLA_W_ACK=0x60,
	TWI_OWN_SLA_W_ACK2=0x68,
	TWI_GENERAL_CALL=0X70,
	TWI_GENERAL_CALL2=0X78,
	TWI_SLAVE_DATA_RX_ACK=0X80,
	TWI_SLAVE_DATA_RX_NACK=0X88,
	TWI_GENERAL_CALL_DATA_ACK=0X90,
	TWI_GENERAL_CALL_DATA_NACK=0X98,
	TWI_SLV_RECEIVED_STOP=0X0A,
/*Status Codes for Slave Transmitter Mode*/
	TWI_OWN_SLA_R_ACK=0xA8,
	TWI_OWN_SLA_R_ACK2=0xB0,
	TWI_SLAVE_DATA_TX_ACK=0X80,
	TWI_SLAVE_DATA_TX_NACK=0XB8,
	TWI_SLAVE_DATA_TX_LAST_BYTE_ACK=0XC8
	
}enu_TWI_STATE_t;
enu_TWI_STATE_t TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uinteg8_t u8_data);
uinteg8_t TWI_ReadACK(void);
//read byte with NACK
uinteg8_t TWI_ReadNACK(void);
uinteg8_t TWI_GetStatus(void);
enu_TWI_STATE_t TWI_ReadACK_returnState(uinteg8_t *u8ptr_dataTemp);
enu_TWI_STATE_t  TWI_msterSendSLV_RW(uinteg8_t u8_SLAVE_ADDRESS_WRITE);


#endif /* IIC_H_ */