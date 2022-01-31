/*
 * UART_USER.c
 *
 * Created: 10/4/2020 2:25:21 PM
 *  Author: Mohamed salah taman
 */ 
#include "UART_interface.h"


#ifdef UART
/*              to initiate UART please configure  these parameters and use this function at app.c

			                	 USART_voidInit( &gstr_USART_Config);                                */ 


	struct gstr_USART_Config_t gstr_USART_Config={  .SYNCH_MODE=USART_ASYNCH_MODE               ,
													.SPEED_MODE=USART_NORMAL_SPEED              ,
													.TX_=USART_TX_ENABLE                        ,
													.RX_=USART_RX_ENABLE                        ,
													.CHAR_SIZE=USART_DATA_FORMAT_8BIT_MODE      ,
													.PARITY_MODE=USART_PARITY_DISABLE           ,
													.STOP_BITS_NUM=USART_1_STOP_BIT             ,
													.TX_INTERRUPT=USART_TX_INTERRUPT_ENABLE    ,
													.RX_INTERRUPT=USART_RX_INTERRUPT_ENABLE    ,
													.UDR_INTERRUPT=USART_UDR_INTERRUPT_DISABLE  };
void USART_RX_ISR(void)
{
	/*Write your ISR here*/
}
void USART_TX_ISR(void)
{
	/*Write your ISR here*/
	
}
#endif