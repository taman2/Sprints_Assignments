/*
 * UART.c
 *
 * Created: 10/4/2020 2:25:35 PM
 *  Author: Mohamed
 */ 


#include "../MCAL/UART/UART_CONFIG.h"


uinteg16_t  MYUBRR=0;
void (*ptr_To_TX_Int_fun)(void)=NULL;
void (*ptr_To_RX_Int_fun)(void)=NULL;

void USART_Init(struct gstr_USART_Config_t *USART_PRE_CONFIGRATION)
{
	
/*****************************************************USART BAUD RATE****************************************************************/

	if(USART_PRE_CONFIGRATION->SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION->SPEED_MODE== USART_NORMAL_SPEED){
		MYUBRR   = (uinteg16_t)  (((F_CPU / (  BUAD_RATE* 16UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION->SYNCH_MODE== USART_ASYNCH_MODE && USART_PRE_CONFIGRATION->SPEED_MODE== USART_DOUBLE_SPEED){
	   
       MYUBRR   = (uinteg16_t)  (((F_CPU / (  BUAD_RATE* 8UL))) - 1);
	}
   else if(	USART_PRE_CONFIGRATION->SYNCH_MODE== USART_SYNCH_MODE ){
	MYUBRR   = (uinteg16_t) (((F_CPU / (  BUAD_RATE* 2UL))) - 1);   
   }
   	   UART_BUAD_RATE_REG_LOW_value=(uinteg8_t)(MYUBRR);
   	   UART_BUAD_RATE_REG_HIGH_value=(uinteg8_t)(MYUBRR>>8);
   /**************************************USART ENABLE RX & TX*************************************************/


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
	/*************************USART DATA FORMAT CHAR SIZE ***********************************************/

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
		EnableGeneralInterrupt();
    }
    else if(USART_PRE_CONFIGRATION->RX_INTERRUPT==USART_RX_INTERRUPT_DISABLE){
		CLR_BIT(UART_COTR_STATUS_REGB,RXCIE);
    }
	{
		
	}
	if(USART_PRE_CONFIGRATION->TX_INTERRUPT==USART_TX_INTERRUPT_ENABLE){
		UART_COTR_STATUS_REGB |= (1<<TXCIE);
		EnableGeneralInterrupt();

	}
	else if(USART_PRE_CONFIGRATION->TX_INTERRUPT==USART_TX_INTERRUPT_DISABLE){
		CLR_BIT(UART_COTR_STATUS_REGB,TXCIE);

	}
	else
	{
		
	}
#ifdef UART_INTERRUPT
   USART_RX_Int_CallBack_fun(USART_RX_ISR);
   USART_RX_Int_CallBack_fun(USART_TX_ISR);
#endif
}

void USART_Transmit( uinteg8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UART_COTR_STATUS_REGA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

uinteg8_t USART_Receive( void )
{
	//return UDR;
	/*Wait for data to be received */
	while ( (UART_COTR_STATUS_REGA & (1<<RXC))==0 );
	/* Get and return received data from buffer */
	return UDR;
}
void USART_Send_Packet( uinteg8_t *str,uinteg8_t Stop_Byte)
{
	 uinteg8_t j=0;
	
	while (str[j]!=Stop_Byte)		/* Send string till stop byte*/
	{
		USART_Transmit(str[j]);
		j++;
	}
    USART_Transmit(Stop_Byte);

}
UART_ERROR_t USART_Recieve_Packet (uinteg8_t *Packet_Receive_Buffer ,uinteg8_t Tail_Byte){
	if(Packet_Receive_Buffer == NULL_POINTER)
	{
		return UART_NOK;
	}
	uinteg8_t i=0;  
    Packet_Receive_Buffer[i]= USART_Receive();
	while( Packet_Receive_Buffer[i]!= Tail_Byte  ){
		i++;
		Packet_Receive_Buffer[i]=USART_Receive();
	}
	
	Packet_Receive_Buffer[i]=0;
	return UART_OK;
	

}

void USART_Recieve_String (uinteg8_t *Packet_Receive_Buffer ){
	uinteg32_t i=0;
	
	Packet_Receive_Buffer[i]= USART_Receive();

	while( Packet_Receive_Buffer[i]!= 0 ){
		Packet_Receive_Buffer[i]=USART_Receive();
		i++;
	}
	
Packet_Receive_Buffer[i]=0;
}
void USART_Send_String (uinteg8_t *Packet_Send_Buffer ){
	uinteg32_t i=0;
	

	while( Packet_Send_Buffer[i]!= 0 ){
		USART_Transmit(Packet_Send_Buffer[i]);
		i++;
	}
	USART_Transmit(0);

}
void USART_Receive_Byte_Iterrupt(volatile uinteg8_t *Byte_Address)
{
	*Byte_Address=UDR;
}
void UART_ReceiveBuffer(uinteg8_t *str,uinteg32_t u32_size)
{
	
	uinteg32_t u32_i;
	for(u32_i =0; u32_i <u32_size; u32_i++)
	{
		str[u32_i]=USART_Receive();	
	}
	
}
void UART_SendBuffer(uinteg8_t *str,uinteg32_t u32_size)
{
	
	uinteg32_t u32_i;
	for(u32_i =0; u32_i <u32_size; u32_i++)
	{
		USART_Transmit(str[u32_i]);
	}
	
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
	if(ptr_To_RX_Int_fun != NULL_POINTER)
	ptr_To_RX_Int_fun();
	else{  }
}
/*TX ISR*/
void __vector_15(void)
{
	if(ptr_To_RX_Int_fun != NULL_POINTER)
	ptr_To_TX_Int_fun();
	else{   }
}