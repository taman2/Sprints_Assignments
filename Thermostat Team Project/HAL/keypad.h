#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../GPIO/GPIO.h"

#define HIGH              (1)
#define LOW               (0)
#define ONE               (0x31)
#define NINE              (0x39)
#define FIRST_ROW         (2)
#define FIRST_COLUMN      (5)
#define ROWS              (4)
#define COLUMNS           (7)
#define NO_BUTTON_PRESSED (0)

void keypad_init(void);
uint8_t keypad_scan(void);


#endif