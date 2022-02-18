/*
 * LCD.h
 *
 * Created: 1/22/2022 5:53:51 PM
 *  Author: Mohamed
 */ 
#include "AT32_Dio.h"
#include "delay.h"

#ifndef LCD_H_
#define LCD_H_
/************Command to LCD*******************/
#define LCD_INIT                     0x02
#define LCD_CURSER_RIGHT             0x06	/* Increment cursor (shift cursor to right automatic) */
#define LCD_CLEAR                    0x01
#define LCD_SHIFT_CURSER             0x06
#define LCD_DISPL_ON_CUR_OFF		 0x0C
#define LCD_DISPL_ON_CUR_ON          0x0E
#define LCD_CUR_PLINK				 0x0f
#define LCD_SHIFT_CURSER_LEFT        0x10
#define LCD_SHIFT_CURSER_RIGHT       0x14
#define LCD_4BIT_MODE                0x28
#define LCD_8BIT_MODE                0x38

#define LCD_DIR		DDRA			/* Define LCD data port direction */
#define LCD_PORT	PORTA			/* Define LCD data port */
#define LCD_RS		P1				/* Define Register Select pin */
#define LCD_EN		P3				/* Define Enable signal pin */
#define LCD_RW		P2				/* Define Enable signal pin */

/*****************************************************************************************************************
										Functions prototypes 
******************************************************************************************************************/
void LCD_Init (void);			/* LCD Initialize function */
void LCD_Command( uinteg8_t cmnd );
void LCD_Char( uinteg8_t data );
void LCD_String (uinteg8_t *str);		/* Send string to LCD function */
void LCD_String_xy (uinteg8_t row, uinteg8_t pos, uinteg8_t *str);	/* Send string to LCD with xy position */
void LCD_Clear();
void LCD_Integ (int s32_Value);		/* Send int to LCD function */




#endif /* LCD_H_ */