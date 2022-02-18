/*
 * IIC_Interface.h
 *
 * Created: 1/30/2022 4:59:01 AM
 *  Author: Mohamed
 */ 


#ifndef IIC_INTERFACE_H_
#define IIC_INTERFACE_H_

#include "IIC.h"
/*   SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )

((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

TWDR =	BITRATE(TWSR)	*/

#define SCL_CLK 100000L
#define  F_CPU 8000000UL

#define  TWI_PRESCALERBITS	 TWI_PRESCALER_1
#define  TWI_MODE				     TWI_MASTER_MODE
#define	 SLAVE_ADD				   0xaa





#endif /* IIC_INTERFACE_H_ */
