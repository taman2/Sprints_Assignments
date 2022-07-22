#include "../LIB/STD_types.h"
#include "../MCAL/USART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/TIMERS/TIMERS.h"
#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../ECUAL/LCD/LCD.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../SERVICE/ATM_interface.h"
#include <string.h>


#define FALSE   				 (0)
#define TRUE	   				 (1)

int main(void )
{
	uint8_t u8_maxBalValid       = u8_BALANCE_NOT_VALID ;
	uint8_t u8_firstLogin        = TRUE;
	uint8_t u8_noExit            = TRUE;
	uint8_t u8_flag              = TRUE;
	uint8_t u8_chooseState       = FALSE;
	uint8_t u8_recExist          = FALSE;
	uint8_t u8_noChoice          = FALSE;
	uint8_t u8_panValid          = FALSE;
	uint8_t u8_balValid          = FALSE;
	uint8_t u8_adminMode         = FALSE;
	uint8_t u8_accessGranted     = FALSE;
	uint8_t u8_inputBalValid	 = u8_BALANCE_NOT_VALID;
	uint8_t u8_adminChoice		 = u8_INTIAL_VAL ;
	uint8_t u8_digitsCount           = u8_INTIAL_VAL;
	uint8_t u8_panValidity           = ATM_FALSE ;
	uint8_t u8_pinValidity           = ATM_FALSE;
	uint16_t u16_recordNum             = u8_INTIAL_VAL;
	uint16_t u16_searchingPanRecordnum = u8_INTIAL_VAL ;
	uint8_t u8_keyPadReturnASCII       = u8_KEYPAD_NOT_PRESSED;
	uint8_t u8_accBalValidty           = u8_BALANCE_NOT_VALID ;
	uint8_t pu8_atmPANBuffer[u8_PAN_MAX_SIZE];
	uint8_t pu8_atmPINBuffer[u8_PIN_SIZE];
	uint8_t	pu8_enteredUserBal[u8_MAX_BALANCE_MAX_SIZE] ;
	uint8_t pu8_userAccBal[u8_BALANCE_MAX_SIZE] ;
	uint8_t pu8_atmDataBuffer[10] ;
	uint8_t pu8_newRecPan[u8_PAN_MAX_SIZE];
	uint8_t pu8_newRecBal[u8_BALANCE_MAX_SIZE];
	uint8_t pu8_tempRecBal[u8_BALANCE_MAX_SIZE];
	uint8_t pu8_maxBalance[u8_MAX_BALANCE_MAX_SIZE];
	uint8_t pu8_arr[3];

	ATM_modes mode = ADMIN;
	ATM_Init();
	ATM_voidStoreRecNum(u16_recordNum);
	EEPROM_u8WriteNeededPartBlock(u8_MAX_BALANCE_PAGE_NUM,u8_MAX_BALANCE_BYTE_NUM, u8_MAX_BALANCE, u8_MAX_BALANCE_MAX_SIZE);
	while (1)
	{
		if(u8_firstLogin)
		{
			u16_recordNum = ATM_u16GetRecNum(pu8_arr);
			DIO_SetPinValue(PORTD,PIN2,GET_BIT(u16_recordNum,8));
			DIO_SetPinValue(PORTD,PIN3,GET_BIT(u16_recordNum,9));
			DIO_SetPinValue(PORTD,PIN4,GET_BIT(u16_recordNum,10));
			DIO_SetPinValue(PORTD,PIN5,GET_BIT(u16_recordNum,11)); 
			if(u16_recordNum == u8_EMPTY)
			{
				TERMINAL_display(PROG_FIRST_STATE_STR);
			}
		}
		else if(TRUE == u8_chooseState)
		{
		   TERMINAL_display(ADMIN_MODE_STR);
		   TERMINAL_display(USER_MODE_STR);
		   u8_noChoice = TRUE;
		   u8_chooseState = FALSE;
		}
		
		while (u8_noChoice)
		{
			TERMINAL_display(CHOICE_STR);
			TERMINAL_command(pu8_atmDataBuffer,10);
			
			if(strcmp(pu8_atmDataBuffer,ADMIN_STR) == u8_EQUAL_STR)
			{
				mode = ADMIN;
				u8_noChoice = FALSE;
			}
			else if(strcmp(pu8_atmDataBuffer,USER_STR) == u8_EQUAL_STR)
			{
				mode = USER;
				u8_noChoice = FALSE;
			}
			else
			{
				TERMINAL_display(WRONG_CHOICE_STR);
			}
		}
		
		switch(mode)
		{
			case USER:
			
			do{              
				        if(u8_flag == TRUE)
						{
							ATM_voidlcdUserInterface();
						}
						u8_flag = FALSE;
						u8_keyPadReturnASCII = KeyPad_U8Data();			
						if(u8_keyPadReturnASCII == '1')
						{
							u8_noExit = TRUE;
							u8_flag = TRUE;
						}
						else if (u8_keyPadReturnASCII == '2')
						{
							u8_noExit = TRUE;
							u8_flag = TRUE;	
						}
						else if (u8_keyPadReturnASCII == '3') 
						{
								u8_noExit = FALSE;
								u8_flag   = TRUE;
								u8_chooseState = TRUE;
								LCD_command(DISPLAY_CLEAR);
								break;
						}
						
						if(u8_keyPadReturnASCII == '1')
						{
							LCD_command(DISPLAY_CLEAR);
							LCD_printString(LCD_ENTER_CARD_STR);
				
							do{
								u8_keyPadReturnASCII = KeyPad_U8Data();

							  }while(u8_keyPadReturnASCII != u8_CARD_PRESSED);
				
							LCD_command(DISPLAY_CLEAR);
							LCD_printString(PROCESS_WAIT_STR);
							DIO_SetPinValue(PORTD,PIN7,HIGH);
							SPI_slaveReceiveString(pu8_atmPANBuffer,u8_PAN_MAX_SIZE);
							DIO_SetPinValue(PORTD,PIN7,LOW);
							u8_panValidity = ATM_panValidity(pu8_atmPANBuffer,&u16_searchingPanRecordnum);
							TERMINAL_display("\r\n");
							TERMINAL_display(pu8_atmPANBuffer);
							TERMINAL_display("\r\n");
							if(u8_panValidity)
							{
								DIO_SetPinValue(PORTD,PIN7,HIGH);
								SPI_slaveReceiveString(pu8_atmPINBuffer,u8_PIN_SIZE) ;
								DIO_SetPinValue(PORTD,PIN7,LOW);
								LCD_command(DISPLAY_CLEAR) ;
								LCD_printString(LCD_REQUIRE_PIN_STR);
								LCD_newLine();
								u8_pinValidity = ATM_u8PinAccessGrant(pu8_atmPINBuffer) ;

								if(u8_pinValidity)
								{
									u8_inputBalValid = ATM_u8checkBalanceValidity(pu8_enteredUserBal);

									if(u8_inputBalValid == u8_BALANCE_VALID )
									{
										u8_accBalValidty = ATM_u8checkAccounBal(pu8_enteredUserBal,pu8_userAccBal,u16_searchingPanRecordnum) ;
										LCD_command(DISPLAY_CLEAR);
										DIO_SetPinValue(PORTD,PIN6,HIGH);
										LCD_printString("End of Trans.");
										TIMER0_msdelay(2000);
										DIO_SetPinValue(PORTD,PIN6,LOW);
										if(u8_accBalValidty == u8_BALANCE_VALID)
										{
											ATM_voidUpdateBalance(pu8_userAccBal,pu8_enteredUserBal,u16_searchingPanRecordnum);
										}
										
										
									}
									else
									{
										LCD_command(DISPLAY_CLEAR);
										LCD_printString((uint8_t*)"balance entered");
										LCD_newLine();
										LCD_printString((uint8_t*)"incorrect ");
										TIMER0_msdelay(2000) ;
										LCD_command(DISPLAY_CLEAR);
										DIO_SetPinValue(PORTD,PIN6,HIGH);
										LCD_printString("End of Trans.");
										TIMER0_msdelay(2000);
										DIO_SetPinValue(PORTD,PIN6,LOW);											
									}
								}
								else
								{
									LCD_command(DISPLAY_CLEAR) ;
									LCD_printString((uint8_t*)"PIN Entered") ;
									LCD_newLine() ;
									LCD_printString((uint8_t*)"NOT VALID") ;
									TIMER0_msdelay(2000);
									DIO_SetPinValue(PORTD,PIN6,HIGH);
									LCD_command(DISPLAY_CLEAR);
									LCD_printString("End of Trans.");
									TIMER0_msdelay(2000);
									DIO_SetPinValue(PORTD,PIN6,LOW);
								}
							}
							else
							{
								LCD_command(DISPLAY_CLEAR) ;
								LCD_printString((uint8_t*)"card not");
								LCD_newLine();
								LCD_printString((uint8_t*)"recognized");
								TIMER0_msdelay(2000);
								TIMER0_msdelay(10);
								DIO_SetPinValue(PORTD,PIN6,HIGH);
								LCD_command(DISPLAY_CLEAR);
								LCD_printString("End of Trans.");
								TIMER0_msdelay(2000);
								DIO_SetPinValue(PORTD,PIN6,LOW);
							}
						}
						else if (u8_keyPadReturnASCII == '2')
						{
							ATM_voidShowTemp() ;
						}
						
				}while(u8_noExit);
						break;
					
			case ADMIN:
			            u8_noChoice   = TRUE;
						u8_firstLogin = FALSE;
						u8_adminMode  = TRUE;
						u8_accessGranted = ACCESS_grant();
						
						while(u8_adminMode && u8_accessGranted)
						{	
							TERMINAL_display(NEW_LINE);
						    TERMINAL_display(NEW_REC_STR);
							TERMINAL_display(MAX_BAL_STR);
							TERMINAL_display(EXIT_STR);
							TERMINAL_display(CHOICE_STR);
							
						    u8_adminChoice = USART_u8Receive();
						
						    if(u8_adminChoice == NEW_REC)
						    {	
								do 
								{
									TERMINAL_display(NEW_LINE);
									TERMINAL_display(REQUIRE_PAN_STR);
									u8_panValid = TERMINAL_u8getInput(pu8_newRecPan, u8_PAN_MAX_SIZE, u8_PAN_MIN_SIZE);
									if (!u8_panValid)
									{
										TERMINAL_display(WRONG_PAN_STR);
									}
								} while(!u8_panValid);
								
								u16_recordNum = ATM_u16GetRecNum(pu8_arr);
								
								EEPROM_u8WriteNeededPartBlock(u16_recordNum, u8_PAN_BYTE_NUM, pu8_newRecPan, u8_PAN_MAX_SIZE);
						
								do
								{
									TERMINAL_display(ENTER_BAL_STR);
									u8_balValid = TERMINAL_u8getInput(pu8_tempRecBal,u8_BALANCE_MAX_SIZE, u8_BALANCE_MIN_SIZE);
									u8_digitsCount = ATM_u8getArrCount(pu8_tempRecBal);
									if(!u8_balValid)
									{
										TERMINAL_display(WRONG_MAX_BAL_STR);
									}
								}while (!u8_balValid);
								
								ATM_voidstoreBalance(pu8_newRecBal,pu8_tempRecBal,u8_digitsCount);
								u16_recordNum = ATM_u16GetRecNum(pu8_arr);
								EEPROM_u8WriteNeededPartBlock(u16_recordNum, u8_BALANCE_BYTE_NUM, pu8_newRecBal, u8_BALANCE_MAX_SIZE);
								u16_recordNum++;
								ATM_voidStoreRecNum(u16_recordNum);
								u8_recExist = TRUE;
								
							}
						    else if(u8_adminChoice == SET_MAX_BAL)
						    {
								TERMINAL_display(NEW_LINE);
							    TERMINAL_display(REQUIRE_MAX_BAL_STR);
							    do
							    {
							    	u8_maxBalValid =  TERMINAL_u8getInput(pu8_maxBalance,u8_MAX_BALANCE_MAX_SIZE, u8_MAX_BALANCE_MIN_SIZE);
							    	if(!u8_maxBalValid)
							    	{
										TERMINAL_display(WRONG_MAX_BAL_STR);
										TERMINAL_display(REQUIRE_MAX_BAL_STR);
							    	}
							    }while(!u8_maxBalValid);
								
							    EEPROM_u8WriteNeededPartBlock(u8_MAX_BALANCE_PAGE_NUM,u8_MAX_BALANCE_BYTE_NUM, pu8_maxBalance, u8_MAX_BALANCE_MAX_SIZE);
						    }
						    else if(u8_adminChoice == EXIT && u8_recExist)
						    {
								u8_adminMode     = FALSE;
								u8_accessGranted = FALSE;
								u8_flag          = TRUE;
								u8_chooseState   = TRUE;
						    }
							else if (u8_adminChoice == EXIT && u8_recExist == FALSE)
							{
								TERMINAL_display(NO_REC_TO_EXIT_STR);
							}
							else 
							{
								TERMINAL_display(WRONG_CHOICE_STR);
							}
						}
						break;
		}
	}
	return 0;
}
