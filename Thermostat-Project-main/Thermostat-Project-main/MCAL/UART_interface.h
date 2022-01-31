/*
 * UART_USER.h
 *
 * Created: 9/13/2020 4:16:18 PM
 *  Author: Mohamed
 */ 


#ifndef UART_USER_H_
#define UART_USER_H_
#include "UART.h"
/* To Use this driver please modify only in UART_interface.h and  UART_interface.c */
#define  UART /*pleas define UART to use the driver*/
#define BUAD_RATE (9600) /*SET BUAD RATE*/


void USART_RX_ISR(void);
void USART_TX_ISR(void);

#endif /* UART_USER_H_ */