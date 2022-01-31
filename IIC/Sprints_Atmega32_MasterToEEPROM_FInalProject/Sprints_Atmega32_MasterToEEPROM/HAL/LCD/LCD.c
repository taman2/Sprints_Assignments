/*
 * LCD.c
 *
 * Created: 1/22/2022 5:53:35 PM
 *  Author: Mohamed Salah
 */ 
#include "LCD.h"

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_DIR = 0xFF;					/* Make LCD port direction as o/p */
	CLR_BIT(LCD_PORT,LCD_RW);
	_delay_ms(200);					/* LCD Power ON delay always >15ms */
	LCD_Command(0x03);
	_delay_ms(10);					/* LCD Power ON delay always >15ms */
	LCD_Command(0x03);
	_delay_ms(10);					/* LCD Power ON delay always >15ms */
	LCD_Command(0x03);
	_delay_ms(10);					/* LCD Power ON delay always >15ms */
	LCD_Command(0x02);				/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
}
void LCD_Command(uinteg8_t cmnd )
{
	LCD_PORT = (LCD_PORT & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_PORT &= ~ (1<<LCD_RS);		/* RS=0, command reg. */
	LCD_PORT |= (1<<LCD_EN);		/* Enable pulse */
	_delay_us(10);
	LCD_PORT &= ~ (1<<LCD_EN);

	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_PORT |= (1<<LCD_EN);
	_delay_us(10);
	LCD_PORT &= ~ (1<<LCD_EN);
	_delay_ms(10);
}

void LCD_Char( uinteg8_t data )
{
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_PORT |= (1<<LCD_RS);		/* RS=1, data reg. */
	LCD_PORT|= (1<<LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~ (1<<LCD_EN);

	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_PORT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~ (1<<LCD_EN);
	_delay_ms(2);
}


void LCD_String (uinteg8_t *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (uinteg8_t row, uinteg8_t pos, uinteg8_t *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(5);
	LCD_Command (0x80);		/* Cursor at home position */
}
void LCD_Integ (int s32_Value)		/* Send string to LCD function */
{
	uinteg8_t *str;
	itoa(s32_Value,str,10);	/* Integer to string conversion */
	LCD_String(str);
}