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



#endif /* EEEPROM_H_ */