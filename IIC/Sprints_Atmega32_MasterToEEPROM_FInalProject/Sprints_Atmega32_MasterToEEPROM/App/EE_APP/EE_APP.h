/*
 * EE_APP.h
 *
 * Created: 2/18/2022 3:01:32 AM
 *  Author: Mohamed
 */ 


#ifndef EE_APP_H_
#define EE_APP_H_
#include "BitManipulation.h"
#include "AT32_Dio.h"
#include "Timer.h"
#include "delay.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KeyPad/KeyPad.h"
#include "../MCAL/UART/UART_CONFIG.h"
#include "IIC_Interface.h"
#include "EEPROM.h"

#define BUFFER_SIZE (100)
#define ENTER_PRESSED ('\r')
#define SPACE_PRESSED (32)
#define NULL_CHAR	('\0')
typedef enum
{
	_READ,
	_WRITE,
	_OK,
	_WAITE
}genu_EE_APPState_t;
genu_EE_APPState_t genu_EE_APPState;
void check_command(uinteg8_t *pu8_buffer);
void EE_APPControl(void);
uinteg8_t stringToBinary(uinteg8_t *pu8_str);



#endif /* EE_APP_H_ */