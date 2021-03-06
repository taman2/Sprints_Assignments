/*
 * EEEPROM.h
 *
 * Created: 1/30/2022 11:28:53 PM
 *  Author: Mohamed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "IIC_Interface.h"
#define  EEDEVADR 0b10100000
typedef enum
{
	EE_OK,
	EE_NOK
	
}enu_EE_Error_t;
/*To use this functions and work well Kindly set SCL_CLK and F_CPU at [IIC_Interface.h] file " */
enu_EE_Error_t EEInit(void);
enu_EE_Error_t EEReadByte(uinteg16_t u16_addr, uinteg8_t *u8_data);
enu_EE_Error_t EEWriteByte(uinteg16_t u16_addr, uinteg8_t u8_data);


#endif /* EEEPROM_H_ */