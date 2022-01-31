/*
 * UART_USER.h
 *
 * Created: 9/13/2020 4:16:18 PM
 *  Author: Mohamed
 */ 


#ifndef UART_USER_H_
#define UART_USER_H_
#include "UART_CONFIG.h"

#define BUAD_RATE (9600) /*SET BUAD RATE*/

extern volatile	uinteg8_t UART_buffer[50];


void USART_RX_ISR(void);

#endif /* UART_USER_H_ */