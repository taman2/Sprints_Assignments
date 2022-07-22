#include "../LIB/STD_types.h"
#include "../MCAL/USART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/I2C/I2C_interface.h"
#include "../LIB/ATMEGA32_registers.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/TIMERS/TIMERS.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/EXTI/EXTERNAL_interrupts.h"

#include "CARD_interface.h"
#include <string.h>


static void ATM_voidSetWaitingState(void);
static void ATM_voidSetPanSendState(void);
static void ATM_voidSetPinSendState(void);
static void ATM_voidSetEndOfTransState(void) ; 



extern struct gstr_USART_Config_t gstr_USART_Config;


cardMode_t u8_mode = ADMIN;

send_req_T sendStatus = waitingState; 


void CARD_init(void)
{	
	Ru8_SREG |= 0x80;
	External_Interrupts_Init(EXTERNAL_INT_00,RISING_EDGE,ATM_voidSetWaitingState) ; 
	External_Interrupts_Init(EXTERNAL_INT_01,RISING_EDGE,ATM_voidSetWaitingState) ;
	DIO_SetPinDirection(PORTB,PIN0,OUTPUT) ;
	SPI_init();
	TERMINAL_init();
	EEPROM_voidInit();
}

void TERMINAL_init(void)
{
	USART_voidInit(&gstr_USART_Config);
}

void TERMINAL_display(uint8_t* pu8_stream)
{
	if (pu8_stream != NULL_POINTER)
	{
		USART_voidSendString(pu8_stream);
	}
}

void TERMINAL_command(uint8_t* pu8_buffer, uint8_t u8_arrSize)
{
	USART_voidRecievePacket(pu8_buffer, u8_arrSize, '\r');
}

void CARD_voidCheckPanValidity(uint8_t* pu8_cardPAN, uint8_t* u8_panSize)
{
	uint8_t u8_arrIndex    = u8_INTIAL_VAL;
	TERMINAL_display(PAN_REQ_STR);
	TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
	do
	{
		if((pu8_cardPAN[u8_arrIndex] >= '0') && (pu8_cardPAN[u8_arrIndex] <= '9'))
		{
			u8_arrIndex++;
		}
		else
		{
			TERMINAL_display(WRONG_PAN_STR);
			TERMINAL_display(PAN_REQ_STR);
			TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
		if(((pu8_cardPAN[u8_arrIndex] == NULL_CHAR)) && (u8_arrIndex < u8_PAN_MIN_SIZE ))
		{
			TERMINAL_display(WRONG_PAN_STR);
			TERMINAL_display(PAN_REQ_STR);
			TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
	}while((pu8_cardPAN[u8_arrIndex] != NULL_CHAR));
	
	*(u8_panSize) = u8_arrIndex;
}

void CARD_voidCheckPinValidity(uint8_t* pu8_cardPIN)
{
	uint8_t u8_arrIndex    = u8_INTIAL_VAL;
	TERMINAL_display(PIN_REQ_STR);
	TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
	
	do
	{
		if((pu8_cardPIN[u8_arrIndex] >= '0') && (pu8_cardPIN[u8_arrIndex] <= '9'))
		{
			u8_arrIndex++ ;
		}
		else
		{
			TERMINAL_display(WRONG_PIN_STR);
			TERMINAL_display(PIN_REQ_STR);
			TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
		if(((pu8_cardPIN[u8_arrIndex] == NULL_CHAR)) && ((u8_arrIndex < (u8_PIN_SIZE - 1))))
		{
			TERMINAL_display(WRONG_PIN_STR);
			TERMINAL_display(PIN_REQ_STR);
			TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
	}while((pu8_cardPIN[u8_arrIndex] != NULL_CHAR));
}

uint8_t CARD_u8ModeSelection(void)
{
	uint8_t u8_noChoice = TRUE;
	uint8_t u8_choice   = u8_INTIAL_VAL;
	uint8_t u8_mode     = u8_INTIAL_VAL;
	
	TERMINAL_display("Choose mode\r\n");
	TERMINAL_display("1- Programming mode\r\n");
	TERMINAL_display("2- User mode\r\n");
	
	while(u8_noChoice)
	{
		TERMINAL_display("Choice: ");
		u8_choice = USART_u8Receive();
		if(u8_choice == PROGRAMMING_MODE)
		{
			u8_noChoice = FALSE;
			u8_mode = ADMIN;
		}
		else if (u8_choice == USER_MODE)
		{
			u8_noChoice = FALSE;
			u8_mode = USER;
		}
		else
		{
			TERMINAL_display("WRONG CHOICE!!!\r\n");
		}
	}
	return u8_mode;
}


static void ATM_voidSetWaitingState(void)
{
	sendStatus = waitingState ;
}

static void ATM_voidSetPanSendState(void)
{
	sendStatus = sendCardPan ; 
}


static void ATM_voidSetPinSendState(void)
{
	sendStatus = sendCardPin ;
}



static void ATM_voidSetEndOfTransState(void)
{
	sendStatus = sendEndOfTransaction ; 
}




void CARD_voidProgram(void) 
{
	static uint8_t u8_noChoice               = TRUE; 
	static uint8_t u8_panNotValid            = TRUE;
	static uint8_t u8_beginUserMode		     = FALSE;
	static uint8_t u8_pinNotValid            = TRUE;
	static uint8_t u8_noResponse             = TRUE;
	static uint8_t u8_adminAccessed          = FALSE; 
	static uint8_t u8_arrIndex               = u8_INTIAL_VAL;
	static uint8_t u8_panSize                = u8_INTIAL_VAL;
	static uint8_t u8_requestCode            = u8_INTIAL_VAL;
	static uint8_t u8_statusCode             = u8_INTIAL_VAL;
	static uint8_t u8_cardState              = u8_CARD_INTIAL_VAL; 
	static uint8_t pu8_cardPIN[u8_PIN_SIZE];
	static uint8_t pu8_command[10];
	static uint8_t pu8_neededData[15];
	static uint8_t pu8_cardHolderName[10];
	static uint8_t pu8_cardPAN[u8_PAN_MAX_SIZE];


	
	switch(u8_mode)
	{
		case ADMIN :
		TERMINAL_display(PROG_MODE_STR);
		CARD_voidCheckPanValidity(pu8_cardPAN, &u8_panSize);	
		EEPROM_u8WriteNeededPartBlock(u8_PAN_PAGE_NUM,u8_PAN_BYTE_NUM,pu8_cardPAN,u8_panSize);
		CARD_voidCheckPinValidity(pu8_cardPIN);
		EEPROM_u8WriteNeededPartBlock(u8_PIN_PAGE_NUM,u8_PIN_BYTE_NUM,pu8_cardPIN,u8_PIN_SIZE);
		u8_mode = USER;
		break;
		
		case USER :
		if(FALSE == u8_beginUserMode)
		{
			TERMINAL_display(NEW_LINE);
			TERMINAL_display(USER_MODE_STR);
			EEPROM_u8ReadNeededPartBlock(u8_PAN_PAGE_NUM, u8_PAN_BYTE_NUM, pu8_cardPAN, u8_panSize);
			External_Interrupts_Init(EXTERNAL_INT_00,RISING_EDGE,ATM_voidSetPanSendState) ; 
			TERMINAL_display("\r\n");
			TERMINAL_display(pu8_cardPAN);
			TERMINAL_display("\r\n");
			u8_beginUserMode = TRUE ; 
		}

		switch(sendStatus)
		{	
			case sendCardPan:
					SPI_masterTransmitString(pu8_cardPAN);
					External_Interrupts_Init(EXTERNAL_INT_00,RISING_EDGE,ATM_voidSetPinSendState) ; 
					External_Interrupts_Init(EXTERNAL_INT_01,RISING_EDGE,ATM_voidSetEndOfTransState) ;
					sendStatus = waitingState ; 
					break ;

			case sendCardPin :
					EEPROM_u8ReadNeededPartBlock(u8_PIN_PAGE_NUM, u8_PIN_BYTE_NUM, pu8_cardPIN, u8_PIN_SIZE);
					SPI_masterTransmitString(pu8_cardPIN);
				    External_Interrupts_Init(EXTERNAL_INT_00,RISING_EDGE,ATM_voidSetWaitingState) ;
					External_Interrupts_Init(EXTERNAL_INT_01,RISING_EDGE,ATM_voidSetEndOfTransState) ; 
					sendStatus = waitingState ;
					break ; 

			case sendEndOfTransaction : 
					u8_mode = CARD_u8ModeSelection();
					External_Interrupts_Init(EXTERNAL_INT_00,RISING_EDGE,ATM_voidSetWaitingState) ; 
					External_Interrupts_Init(EXTERNAL_INT_01,RISING_EDGE,ATM_voidSetWaitingState) ;
					u8_beginUserMode = FALSE;
					sendStatus = waitingState;
					break; 
		}
		break;
	}
}
