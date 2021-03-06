/*
 * KeyPad.h
 *
 * Created: 1/22/2022 8:16:38 PM
 *  Author: Mohamed
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define  F_CPU 8000000UL
#include "AT32_Dio.h"
#include "delay.h"

#define ROW_NUM			3
#define COL_NUM			3

#define ROW1_PIN         PIN2
#define ROW2_PIN         PIN3
#define ROW3_PIN         PIN4

#define COL1_PIN         PIN5
#define COL2_PIN         PIN6
#define COL3_PIN         PIN7

#define ROW1_PIN_ID         2
#define ROW2_PIN_ID         3
#define ROW3_PIN_ID         4

#define COL1_PIN_ID          5
#define COL2_PIN_ID          6
#define COL3_PIN_ID          7

#define KEYPAD_DDR       DDRC
#define _KEYPAD_PORT      _PORTC
#define  KEYPAD_PORT      PORTC
#define KEYPAD_PIN       PINC

#define KPAD_NON_KEY_PRESSED 20

/**********************************************************************************************************************
											funs
**********************************************************************************************************************/

void KeyPad_Init();
uinteg16_t Key_KeyPressed(void);
#endif /* KEYPAD_H_ */