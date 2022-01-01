#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/*- INCLUDES -----------------------------------------------*/
#include "DataTypes.h"
/*- CONSTANTS ----------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
typedef enum{
    EMPTY=1,
    FULL,
    AVAILABLE
}enuStackStatus_t;
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct{
uint8_t arr[100];
int32_t top;
uint32_t capacity;
enuStackStatus_t status;
}strStackConfig_t;
extern strStackConfig_t gstrStackConfig;

/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS -------------------------------*/
void StackCreat(uint32_t u8_Capacity);
void StsckPush(uint8_t u8_data);
uint8_t StackPop(void);
void PrintStack(void);
#endif // STACK_H_INCLUDED
