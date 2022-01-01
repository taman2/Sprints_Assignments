/*- INCLUDES
----------------------------------------------*/
#include "Stack.h"

/*- LOCAL MACROS
------------------------------------------*/
/*- LOCAL Dataypes
----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
strStackConfig_t gstrStackConfig;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void StackCreat(uint32_t u32_Capacity)
{
    uint8_t u8_i=0;
    gstrStackConfig.top=-1;
    gstrStackConfig.capacity=u32_Capacity;
    gstrStackConfig.status=EMPTY;
    for(u8_i=0;u8_i<u32_Capacity;u8_i++)
    {
        gstrStackConfig.arr[u8_i]=0;
    }
}
void StsckPush(uint8_t u8_data)
{
    gstrStackConfig.top++;
    if(gstrStackConfig.top >(gstrStackConfig.capacity-1))
    {
        gstrStackConfig.status=FULL;
    }
    else
    {
        gstrStackConfig.arr[gstrStackConfig.top]=u8_data;
        printf("%c pushed to stack\n", u8_data);
        gstrStackConfig.status=AVAILABLE;

    }
}
uint8_t StackPop(void)
{
    if(gstrStackConfig.top <=(-1))
    {
        gstrStackConfig.status=EMPTY;
    }
    else
    {
        gstrStackConfig.top--;
        gstrStackConfig.status=AVAILABLE;
        return (gstrStackConfig.arr[gstrStackConfig.top+1]);
    }
    return 0;
}
void PrintStack(void)
{
    printf("stack capacity=%d\n",gstrStackConfig.capacity);
    printf("stack top=%d\n",gstrStackConfig.top);
    switch( gstrStackConfig.status)
    {
        case AVAILABLE:
            printf("stack status is AVAILABLE\n");
            break;
        case FULL:
            printf("NOTE !!!!!!! stack status is FULL !!!!!!!!!!!\n");
            break;
        case EMPTY:
            printf("stack status is EMPTY\n");
            break;

    }
}


/*- APIs IMPLEMENTATION
-----------------------------------*/
