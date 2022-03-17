/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: USART
 *  Layer arch : MCAL
 *  Created on: Jan 26, 2022
 *	version:1
 *
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/atmega32_registers.h"
#include "../TIMERS0_2/timers_interface.h"
#include "../DIO/dio_interface.h"
#include "usart_config.h"
#include "usart_private.h"
#include "usart_interface.h"




void USART_voidInit(void) 
{
	TIMER0_voidInit();
	CLR_BIT(Ru8_UCSRA,u8_USART_UDRE);
	CLR_BIT(Ru8_UCSRA,u8_USART_FE);
	CLR_BIT(Ru8_UCSRA,u8_USART_DOR);
	CLR_BIT(Ru8_UCSRA,u8_USART_PE);

	//U2X is disabled 
	CLR_BIT(Ru8_UCSRA,u8_USART_U2X);
	//multiprocessor (Master-Slave) disabled
	CLR_BIT(Ru8_UCSRA,u8_USART_MPCM);
	

	DIO_SetPinDirection(u8_USART_PORT,u8_USART_RX_PIN,INPUT);
	DIO_SetPinDirection(u8_USART_PORT,u8_USART_TX_PIN,OUTPUT);
	
	//DIO_u8SetPinVal(u8_USART_PORT,u8_USART_RX_PIN,u8_DIO_PIN_HIGH);
	DIO_SetPinValue(u8_USART_PORT,u8_USART_TX_PIN,HIGH);
	
	#if u8_USART_RX_COMP_INT_STATE==u8_USART_ENABLE
		SET_BIT(Ru8_UCSRB,u8_USART_RXCIE) ; 
	#elif u8_USART_RX_COMP_INT_STATE==u8_USART_DISABLE
		CLR_BIT(Ru8_UCSRB,u8_USART_RXCIE) ; 
	#else 
		#error "Pre-build config error in set Rx int state "
	#endif
	
	
	#if u8_USART_TX_COMP_INT_STATE==u8_USART_ENABLE
		SET_BIT(Ru8_UCSRB,u8_USART_TXCIE) ; 
	#elif u8_USART_TX_COMP_INT_STATE==u8_USART_DISABLE
		CLR_BIT(Ru8_UCSRB,u8_USART_TXCIE) ; 
	#else
		#error "Pre-build config error in set Tx int state"
	#endif
	
	
	#if u8_USART_DATA_REG_EMPTY_INT_STATE==u8_USART_ENABLE
		SET_BIT(Ru8_UCSRB,u8_USART_UDRIE) ; 
	#elif u8_USART_DATA_REG_EMPTY_INT_STATE== u8_USART_DISABLE
		CLR_BIT(Ru8_UCSRB,u8_USART_UDRIE) ; 
	#else
		#error "Pre-build config error in set Data Reg Empty int state"
	#endif
	
	
	#if u8_USART_TRANS_STATE==u8_USART_ENABLE 
		SET_BIT(Ru8_UCSRB,u8_USART_TXEN) ; 
	#elif u8_USART_TRANS_STATE== u8_USART_DISABLE
		CLR_BIT(Ru8_UCSRB,u8_USART_TXEN) ; 		
	#else 
		#error "Pre-build config error in set Transmit state"
	#endif
	
	
	
	#if u8_USART_RECEIVE_STATE==u8_USART_ENABLE
		SET_BIT(Ru8_UCSRB,u8_USART_RXEN) ; 
	#elif u8_USART_RECEIVE_STATE==u8_USART_DISABLE
		CLR_BIT(Ru8_UCSRB,u8_USART_RXEN) ; 
	#else 
		#error "Pre-build config error in set Receive state"
	#endif
	
	
	
	#if u8_USART_USEFULL_DATA_IN_FRAME==u8_USART_5BITS_TO_TRANS
		#if u8_USART_PARITY_CONFIG==u8_USART_PARITY_DISABLE
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) | (u8_USART_SET<<u8_USART_USBS)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_EVEN
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)|(u8_USART_SET<<u8_USART_USBS)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_ODD
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
							  |(u8_USART_SET<<u8_USART_UPM0)|(u8_USART_SET<<u8_USART_USBS)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#else 
			#error "Pre-build config error in set Parity Config"
		#endif
		
	#elif u8_USART_USEFULL_DATA_IN_FRAME==u8_USART_6BITS_TO_TRANS
		#if u8_USART_PARITY_CONFIG==u8_USART_PARITY_DISABLE
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) | (u8_USART_SET<<u8_USART_USBS)| (u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_EVEN
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
							   |(u8_USART_SET<<u8_USART_USBS)| (u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_ODD
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
							  |(u8_USART_SET<<u8_USART_UPM0)|(u8_USART_SET<<u8_USART_USBS)| (u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#else 
			#error "Pre-build config error in set Parity Config"
		#endif
		
	#elif u8_USART_USEFULL_DATA_IN_FRAME==u8_USART_7BITS_TO_TRANS
		#if u8_USART_PARITY_CONFIG==u8_USART_PARITY_DISABLE
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) | (u8_USART_SET<<u8_USART_USBS)| (u8_USART_SET<<u8_USART_UCSZ1)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_EVEN
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
								|(u8_USART_SET<<u8_USART_USBS)|| (u8_USART_SET<<u8_USART_UCSZ1)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_ODD
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
							  |(u8_USART_SET<<u8_USART_UPM0)|(u8_USART_SET<<u8_USART_USBS)| (u8_USART_SET<<u8_USART_UCSZ1)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#else 
			#error "Pre-build config error in set Parity Config"
		#endif
	#elif u8_USART_USEFULL_DATA_IN_FRAME==u8_USART_8BITS_TO_TRANS
		#if u8_USART_PARITY_CONFIG==u8_USART_PARITY_DISABLE
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL)
							  |(u8_USART_SET<<u8_USART_UCSZ1) |(u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_EVEN
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1)
							   |(u8_USART_SET<<u8_USART_USBS) |(u8_USART_SET<<u8_USART_UCSZ1)|(u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#elif u8_USART_PARITY_CONFIG==u8_USART_PARITY_ODD
			Ru8_UBRRH_UCSRC = ((u8_USART_SET<<u8_USART_URSEL) |(u8_USART_SET<<u8_USART_UPM1) |(u8_USART_SET<<u8_USART_UPM0)
							  |(u8_USART_SET<<u8_USART_USBS)  |(u8_USART_SET<<u8_USART_UCSZ1)|(u8_USART_SET<<u8_USART_UCSZ0)) ; 
			CLR_BIT(Ru8_UCSRB,u8_USART_UCSZ2) ; 
		#else 
			#error "Pre-build config error in set Parity Config"
		#endif
	#else 
		#error "Pre-build config error in set Trans usefull data size "
	#endif 
	
		
	Ru8_UBRRL = u8_USART_BAUD_RATE_9600;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function that transmit data sent in argument to another usart device
uint8_t USART_u8TransData(uint8_t u8_DataSent)
{
	//the state of the data if sent of not
	uint8_t u8_DataState = u8_USART_DATA_NOT_SENT ;
	uint8_t u8_FinishIntWaitFlag ;
	//make timer0 compare on match interrupt enable to config the time out
	TIMERS_u8IntModesEn(u8_TIMER0_COMPARE_ON_MATCH) ;
	//config the interrupt time as the user want
	TIMER0_u8InterruptWait(u8_MAX_WAIT_IN_MS) ;
	//time out pulling to make sure if the function reached this time, return to main
	u8_FinishIntWaitFlag = TIMER0_u8GetIntWaitStatus() ;
	while(u8_FinishIntWaitFlag!=u8_FINISH_INTERRUPT_WAITING)
	{
		u8_FinishIntWaitFlag = TIMER0_u8GetIntWaitStatus() ;

		//check if the transmit reg is empty or not and, if so,send the wanted data
		if(GET_BIT(Ru8_UCSRA,u8_USART_UDRE)==u8_USART_DATA_REG_EMPTY)
		{
			Ru8_UDR = u8_DataSent ;
			SET_BIT(Ru8_UCSRA,u8_USART_TXC) ;
			u8_DataState = u8_USART_DATA_SENT ;
			break ;
		}

	}
	//disable the interrupt
	TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ;
	//return the received data
	return  u8_DataState ; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//receive data from another usart device
uint8_t USART_u8ReceiveData(uint8_t* pu8_DataReceive)
{
	uint8_t u8_ReturnReciveState = u8_USART_NOT_RECEIVED ;   
	uint8_t u8_FinishIntWaitFlag ;
	if(pu8_DataReceive!=NULL_POINTER)
	{
		//config timer to enable interrupt and config time out for receiving
		TIMERS_u8IntModesEn(u8_TIMER0_COMPARE_ON_MATCH) ;
		TIMER0_u8InterruptWait(u8_MAX_WAIT_IN_MS) ;
		u8_FinishIntWaitFlag = TIMER0_u8GetIntWaitStatus() ;
		while(u8_FinishIntWaitFlag!=u8_FINISH_INTERRUPT_WAITING)
		{
			u8_FinishIntWaitFlag = TIMER0_u8GetIntWaitStatus() ;
			// when the REG receive data , the flag will set, so we will check the data received and return the state of the data
			if(GET_BIT(Ru8_UCSRA,u8_USART_RXC)==u8_USART_FLAG_SET)
			{
				if(GET_BIT(Ru8_UCSRA,u8_USART_FE)==u8_USART_FLAG_SET)
				{
					u8_ReturnReciveState = u8_USART_FRAME_ERROR ; 
				}
				else if((GET_BIT(Ru8_UCSRA,u8_USART_DOR)==u8_USART_FLAG_SET))
				{
					u8_ReturnReciveState = u8_USART_DATA_OVER_RUN ; 
				}
				else if((GET_BIT(Ru8_UCSRA,u8_USART_PE)==u8_USART_FLAG_SET) && (u8_USART_PARITY_CONFIG != u8_USART_PARITY_DISABLE))
				{
					u8_ReturnReciveState = u8_USART_PARITY_ERROR ; 
				}
				else 
				{
					u8_ReturnReciveState = u8_USART_RECEIVED_CORRECT ; 
				}
				//return the data received
				*pu8_DataReceive = Ru8_UDR ;
				break ;
			}
		}
		TIMERS_u8IntModesDis(u8_TIMER0_COMPARE_ON_MATCH) ;
	}
	else
	{
		u8_ReturnReciveState = u8_USART_RECEIVED_NULL_PTR_ARG ;  
	}
	return u8_ReturnReciveState ;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function the use USART_u8TransData function to transmit string
uint8_t USART_u8TransStr(uint8_t* pu8_StrSent)
{
	uint8_t u8_ReturnTransState = u8_USART_DATA_SENT , u8_indexArr = u8_INTIAL_COUNTER_VAL;

	if(pu8_StrSent != NULL_POINTER)
	{
		while(pu8_StrSent[u8_indexArr] !=NULL_CHAR && u8_ReturnTransState == u8_USART_DATA_SENT)
		{
			u8_ReturnTransState = USART_u8TransData(pu8_StrSent[u8_indexArr])  ;
			u8_indexArr++ ;
		}

	}
	else
	{
		u8_ReturnTransState = u8_USART_DATA_NOT_SENT ;
	}

	return  u8_ReturnTransState ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function the use USART_u8ReceiveData function to receive string with fixed size and special char to terminate
uint8_t USART_u8ReceiveStr(uint8_t* pu8_StrReceive, uint8_t u8_strSize,uint8_t u8_terminator)
{
	uint8_t u8_ReturnTransState = u8_USART_RECEIVED_CORRECT , u8_indexArr = u8_INTIAL_COUNTER_VAL;
	if(pu8_StrReceive != NULL_POINTER)
	{
		do
		{
			if(u8_ReturnTransState==u8_USART_RECEIVED_CORRECT)
			{
				u8_ReturnTransState = USART_u8ReceiveData(&(pu8_StrReceive[u8_indexArr]))  ;
				u8_indexArr++ ;
			}
			else
			{
				u8_ReturnTransState = u8_USART_NOT_RECEIVED ;
 				break ;
			}
		}while(pu8_StrReceive[u8_indexArr-1] != u8_terminator && (u8_indexArr<u8_strSize-1)) ;

		pu8_StrReceive[u8_indexArr-1] = NULL_CHAR ;
	}
	else
	{
		u8_ReturnTransState = u8_USART_RECEIVED_NULL_PTR_ARG ;
	}
	return u8_ReturnTransState ;
}

