/*
 * Traffic_APP.c
 *
 * Created: 2/17/2022 11:15:45 PM
 *  Author: Mohamed
 */ 
#include "Trafic_APP.h"
#include <string.h>
#include <math.h>
uinteg8_t garr_Buffer[BUFFER_SIZE]="HI..Sprints";
char_t *gpu8_StartComand= "START";
char_t *gpu8_WaitingComand="WAIT";
char_t *gpu8_StopComand="STOP";
char_t *gpu8_ATComand="AT";
char_t *gpu8_StartInfo="led green on now ";
char_t *gpu8_WaitingInfo="LED yellow on now";
char_t *gpu8_StopInfo="led red on now ";
char_t *gpu8_ATInfo="OK";
genu_TraficState_t genu_TraficState = _WAIT_NEW_STATE;

void Traffic_Init(void)
{
	GPIO_Init ( _PORTB,((PIN7|PIN6|PIN5|PIN4)),OutPut);
	USART_Init(&gstr_USART_Config);
	USART_Send_String((uinteg8_t*)garr_Buffer);
	USART_Transmit(ENTER_PRESSED);
}
void Traffic_LightControl(void)
{
	
	switch(genu_TraficState)
	{
		case _START:
			GPIO_Write( &PORTB,((GREEN_LIGH)),SET);
			GPIO_Write( &PORTB,(RED_LIGH | YELLO_LIGH),RESET);
			USART_Send_Packet((uinteg8_t*)gpu8_StartInfo,NULL_CHAR);
			USART_Transmit(ENTER_PRESSED);
			genu_TraficState=_WAIT_NEW_STATE;
			break;
		case _WAITING:
			GPIO_Write( &PORTB,((YELLO_LIGH)),SET);
			GPIO_Write( &PORTB,(RED_LIGH | GREEN_LIGH),RESET);
			USART_Send_Packet((uinteg8_t*)gpu8_WaitingInfo,NULL_CHAR);
			USART_Transmit(ENTER_PRESSED);
			genu_TraficState=_WAIT_NEW_STATE;
			break;
		case _STOP:
			GPIO_Write( &PORTB,((RED_LIGH)),SET);
			GPIO_Write( &PORTB,(GREEN_LIGH | YELLO_LIGH),RESET);
			USART_Send_Packet((uinteg8_t*)gpu8_StopInfo,NULL_CHAR);
			USART_Transmit(ENTER_PRESSED);
			genu_TraficState=_WAIT_NEW_STATE;
			break;
		case _AT:
			USART_Send_Packet((uinteg8_t*)gpu8_ATInfo,NULL_CHAR);
			USART_Transmit(ENTER_PRESSED);
			genu_TraficState=_WAIT_NEW_STATE;
			break;
		case _WAIT_NEW_STATE:
			check_command(garr_Buffer);
			break;
		
	}
}
void check_command(uinteg8_t *pu8_buffer)
{
	USART_Recieve_Packet(pu8_buffer,ENTER_PRESSED);
	if(strcmp((char_t*)pu8_buffer,gpu8_StartComand)== 0 )
	{
		genu_TraficState = _START;
	}
	else if(strcmp((char_t*)pu8_buffer,gpu8_WaitingComand)== 0)
	{
		genu_TraficState = _WAITING;
	}
	else if(strcmp((char_t*)pu8_buffer,gpu8_StopComand)== 0)
	{
		genu_TraficState = _STOP;
	}
	else if(strcmp(pu8_buffer,gpu8_ATComand)== 0)
	{
		genu_TraficState = _AT;
	}
	else
	{
		
	}
}
