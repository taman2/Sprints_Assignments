/*
 * Trafic_APP.h
 *
 * Created: 2/17/2022 11:14:00 PM
 *  Author: Mohamed
 */ 


#ifndef TRAFIC_APP_H_
#define TRAFIC_APP_H_

#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
#include "delay.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KeyPad/KeyPad.h"
#include "../MCAL/UART/UART_CONFIG.h"
#include "IIC_Interface.h"

#define BUFFER_SIZE (100)
#define ENTER_PRESSED ('\r')
#define SPACE_PRESSED (32)
#define NULL_CHAR	('\0')
#define RED_LIGH	PIN7
#define YELLO_LIGH	PIN6
#define GREEN_LIGH	PIN5
#define NCOMPLT		(0)
#define COMPLT		(1)

typedef enum
{
	_STOP,
	_START,
	_WAITING,
	_AT,
	_WAIT_NEW_STATE
}genu_TraficState_t;
uinteg8_t garr_Buffer[BUFFER_SIZE];
char_t *gpu8_StartComand;
char_t *gpu8_WaitingComand;
char_t *gpu8_StopComand;
char_t *gpu8_ATComand;
char_t *gpu8_StartInfo;
char_t *gpu8_WaitingInfo;
char_t *gpu8_StopInfo;
char_t *gpu8_ATInfo;

void check_command(uinteg8_t *pu8_buffer);
void Traffic_LightControl(void);


#endif /* TRAFIC_APP_H_ */