/*
 * UART_CONFIG.h
 *
 * Created: 10/4/2020 2:16:59 PM
 *  Author: Mohamed
 */ 



#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_
#define  F_CPU 8000000UL
#include "AtmegaPort.h"
#include "stdlib.h"
#include "Data_Types.h"
#include "UART_USER.h"
#include "BitManipulation.h"

#define UART_COTR_STATUS_REGB                         UCSRB
#define UART_BUAD_RATE_REG_HIGH_value                 UBRRH
#define UART_BUAD_RATE_REG_LOW_value                  UBRRL
#define UART_COTR_STATUS_REGC                         UCSRC
#define UART_COTR_STATUS_REGA                         UCSRA
#define UART_COTR_STATUS_REGB                         UCSRB

extern uinteg16_t  MYUBRR;
 


enum USART_SYNCH_MODE_{
	USART_ASYNCH_MODE,
	USART_SYNCH_MODE =(1<<6)      /*Bit 6 – UMSEL: USART Mode Select*/
};

enum USART_SPEED_MODE{
	USART_NORMAL_SPEED,
	USART_DOUBLE_SPEED
};
enum USART_TX{
	USART_TX_DISABLE,
	USART_TX_ENABLE
};
enum USART_RX{
	USART_RX_DISABLE,
	USART_RX_ENABLE
};
enum USART_DATA_FORMAT{
	USART_DATA_FORMAT_5BIT_MODE =(0x0<<1),
	USART_DATA_FORMAT_6BIT_MODE =(0x1<<1),
	USART_DATA_FORMAT_7BIT_MODE =(0x2<<1),
	USART_DATA_FORMAT_8BIT_MODE =(0x3<<1)
};

enum USART_PARITY_MODE{
	USART_PARITY_DISABLE =(0x00<<4),
	USART_PARITY_MODE_EVEN   =(0x01<<4),
	USART_PARITY_MODE_ODD   =(0x11<<4)
	
};
enum USART_STOP_BITS_NUM{
	USART_1_STOP_BIT =(0x0<<3),
	USART_2_STOP_BITS =(0x1<<3)
};
enum USART_TX_INTERRUPT{
	USART_TX_INTERRUPT_DISABLE=(0<<6),
	USART_TX_INTERRUPT_ENABLE=(1<<6)
	
};
enum USART_RX_INTERRUPT{
	USART_RX_INTERRUPT_DISABLE= (0<<7),
	USART_RX_INTERRUPT_ENABLE= (1<<7)
};
/*Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable*/
enum USART_UDR_INTERRUPT{
	USART_UDR_INTERRUPT_DISABLE= (0<<5),
	USART_UDR_INTERRUPT_ENABLE= (1<<5)
	};

struct gstr_USART_Config_t{
	enum USART_SYNCH_MODE_           SYNCH_MODE;
	enum USART_SPEED_MODE            SPEED_MODE;
	enum USART_TX                   TX_;
	enum USART_RX                   RX_;
	enum USART_DATA_FORMAT          CHAR_SIZE;
	enum USART_PARITY_MODE          PARITY_MODE;
	enum USART_STOP_BITS_NUM        STOP_BITS_NUM;
	enum USART_TX_INTERRUPT         TX_INTERRUPT;
	enum USART_RX_INTERRUPT         RX_INTERRUPT;
	enum USART_UDR_INTERRUPT        UDR_INTERRUPT;
	//INT16U                          BUAD_RATE;
};
 struct gstr_USART_Config_t gstr_USART_Config;


void (*ptr_To_TX_Int_fun)(void);
void (*ptr_To_RX_Int_fun)(void);



void USART_Init(struct gstr_USART_Config_t *USART_PRE_CONFIGRATION);
void USART_Transmit( uinteg8_t data );
uinteg8_t USART_Receive(void);
void USART_SendChar(uinteg8_t );
uinteg8_t USART_ReceiveChar(void);
void USART_Send_String (uinteg8_t *Packet_Send_Buffer );
void USART_Recieve_String (uinteg8_t *Packet_Receive_Buffer );
void UART_ReceiveBuffer(uinteg8_t *str,uinteg32_t u32_size);
void USART_Recieve_Packet (uinteg8_t *Packet_Receive_Buffer ,uinteg8_t Header_Byte ,uinteg8_t Tail_Byte);
void USART_Send_Packet(volatile uinteg8_t *str,uinteg8_t Stop_Byte);
void USART_Receive_Byte_Iterrupt(volatile uinteg8_t *Byte_Address);
void USART_RX_Int_CallBack_fun(void (*ptr_To_Fun)(void));
void USART_TX_Int_CallBack_fun(void (*ptr_To_Fun)(void));

#endif /* UART_CONFIG_H_ */