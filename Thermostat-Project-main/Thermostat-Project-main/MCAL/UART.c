/*
 * UART.c
 *
 * Created: 10/4/2020 2:25:35 PM
 *  Author: Mohamed
 */ 


#include "../MCAL/UART.h"


uint16_t  MYUBRR=0;
void (*ptr_To_TX_Int_fun)(void)=NULL;
void (*ptr_To_RX_Int_fun)(void)=NULL;

void USART_voidInit(struct gstr_USART_Config_t *USART_PRE_CONFIGRATION)
{
	
/*****************************************************USART BAUD RATE****************************************************************/

	if(USART_PRE_CONFIGRATION->SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION->SPEED_MODE== USART_NORMAL_SPEED){
		MYUBRR   = (uint16_t)  (((F_CPU / (  BUAD_RATE* 16UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION->SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION->SPEED_MODE== USART_DOUBLE_SPEED){
	   
       MYUBRR   = (uint16_t)  (((F_CPU / (  BUAD_RATE* 8UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION->SYNCH_MODE== USART_SYNCH_MODE ){
	MYUBRR   = (uint16_t) (((F_CPU / (  BUAD_RATE* 2UL))) - 1);   
   }
   	   UART_BUAD_RATE_REG_LOW_value=(uint8_t)(MYUBRR);
   	   UART_BUAD_RATE_REG_HIGH_value=(uint8_t)(MYUBRR>>8);
   /**************************************USART ENABLE RX & TX******************************************************/


    if(USART_PRE_CONFIGRATION->TX_==USART_TX_ENABLE)
	{
		SET_BIT(UART_COTR_STATUS_REGB,TXEN);
	}
	else if(USART_PRE_CONFIGRATION->TX_==USART_TX_DISABLE)
	{
	  CLR_BIT(UART_COTR_STATUS_REGB, TXEN);
	}
	if(USART_PRE_CONFIGRATION->RX_==USART_RX_ENABLE)
	{
		SET_BIT(UART_COTR_STATUS_REGB,RXEN);
	}
	else if(USART_PRE_CONFIGRATION->TX_==USART_TX_DISABLE)
	{
		 CLR_BIT(UART_COTR_STATUS_REGB, RXEN);
	}
	/*******************************************USART DATA FORMAT CHAR SIZE ***********************************************/

   if(USART_PRE_CONFIGRATION->CHAR_SIZE==USART_DATA_FORMAT_8BIT_MODE)
   {
	   UART_COTR_STATUS_REGC |=USART_DATA_FORMAT_8BIT_MODE |(1 << URSEL);
   }
   else if(USART_PRE_CONFIGRATION->CHAR_SIZE==USART_DATA_FORMAT_7BIT_MODE)
   {
	   UART_COTR_STATUS_REGC |=USART_DATA_FORMAT_8BIT_MODE;

   }
   /*******************************************USART TX & RX INTERUUPT ENABLE OR DISABLE **************************************/
   
    if(USART_PRE_CONFIGRATION->RX_INTERRUPT==USART_RX_INTERRUPT_ENABLE){
	    UART_COTR_STATUS_REGB |= (1<<RXCIE);
    }
    else if(USART_PRE_CONFIGRATION->RX_INTERRUPT==USART_RX_INTERRUPT_DISABLE){
		CLR_BIT(UART_COTR_STATUS_REGB,RXCIE);
    }
	{
		
	}
	if(USART_PRE_CONFIGRATION->TX_INTERRUPT==USART_TX_INTERRUPT_ENABLE){
		UART_COTR_STATUS_REGB |= (1<<TXCIE);

	}
	else if(USART_PRE_CONFIGRATION->TX_INTERRUPT==USART_TX_INTERRUPT_DISABLE){
		CLR_BIT(UART_COTR_STATUS_REGB,TXCIE);

	}
	else
	{
		
	}
   USART_RX_Int_CallBack_fun(USART_RX_ISR);
   USART_TX_Int_CallBack_fun(USART_TX_ISR);


}

void USART_voidTransmit( uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UART_COTR_STATUS_REGA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UART_UART_BUFFER_REG = data;
}

uint8_t USART_u8Receive( void )
{
	//return UDR;
	/*Wait for data to be received */
	while ( (UART_COTR_STATUS_REGA & (1<<RXC))==0 );
	/* Get and return received data from buffer */
	return UART_UART_BUFFER_REG;
}
void USART_voidSendPacket(volatile uint8_t *str,uint8_t Stop_Byte)
{
	 uint8_t j=0;
	
	while (str[j]!=Stop_Byte)		/* Send string till stop byte*/
	{
		USART_voidTransmit(str[j]);
		j++;
	}
  USART_voidTransmit(str[j]);

}
void USART_voidRecievePacket (uint8_t *Packet_Receive_Buffer ,uint8_t Header_Byte ,uint8_t Tail_Byte){
	  uint8_t i=0;
	  
Packet_Receive_Buffer[i]= USART_u8Receive();

	while( Packet_Receive_Buffer[i]!= Tail_Byte  ){
		if(Packet_Receive_Buffer[0]!=Header_Byte){
			break;
		}
		i++;
		Packet_Receive_Buffer[i]=USART_u8Receive();
	}

}

void USART_voidRecieveString (uint8_t *Packet_Receive_Buffer ){
	uint8_t i=0;
	
	Packet_Receive_Buffer[i]= USART_u8Receive();

	while( Packet_Receive_Buffer[i]!= 0 ){
		Packet_Receive_Buffer[i]=USART_u8Receive();
		i++;
	}
	Packet_Receive_Buffer[i]=0;
}
void USART_voidSendString (uint8_t *Packet_Send_Buffer ){
	uint32_t i=0;
	while( Packet_Send_Buffer[i]!= 0 ){
		USART_voidTransmit(Packet_Send_Buffer[i]);
		i++;
	}
	USART_voidTransmit(0);

}
void USART_voidReceiveByteIterrupt(volatile uint8_t *Byte_Address)
{
	*Byte_Address=UART_UART_BUFFER_REG;
}
void USART_RX_Int_CallBack_fun(void (*ptr_To_Fun)(void))
{
	
	ptr_To_RX_Int_fun=ptr_To_Fun;

	
}
void USART_TX_Int_CallBack_fun(void (*ptr_To_Fun)(void)){
	
	ptr_To_TX_Int_fun=ptr_To_Fun;
	
}
/*RX ISR*/
void __vector_13(void)
{
	ptr_To_RX_Int_fun();
}
/*TX ISR*/
void __vector_15(void)
{
	ptr_To_TX_Int_fun();
}