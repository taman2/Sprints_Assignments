/*
 * UART_USER.h
 *
 * Created: 9/13/2020 4:16:18 PM
 *  Author: Mohamed
 */ 


#ifndef UART_USER_H_
#define UART_USER_H_
#include "UART_CONFIG.h"

 /*SET BUAD RATE*/
#define BUAD_RATE (9600)
/*to use UART in Interrupt mode please #define UART_INTERRUPT*/
// #define  UART_INTERRUPT

/* User ISRS */
void USART_RX_ISR(void);
void USART_TX_ISR(void);

#endif /* UART_USER_H_ */