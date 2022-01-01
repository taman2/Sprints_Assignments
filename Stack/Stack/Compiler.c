/*- INCLUDES
----------------------------------------------*/
#include "Compiler.h"

/*- LOCAL MACROS
------------------------------------------*/
/*- LOCAL Dataypes
----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/*- GLOBAL STATIC VARIABLES
-------------------------------*/
uint32_t gu32_NormalParCont=1U;
uint32_t gu32_CurleyParCont=1U;
uint32_t gu32_ParCont=1U;
uint8_t pau8_ComMessage1[]={"Balanced\n"};
uint8_t pau8_ComMessage2[]={"Not Balanced\n"};
uint8_t pau8_ComMessage3[]={" No Parentheses \n"};


/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

uint8_t * BalancedParentheses(int8_t * pau8_Expression )
{
    if(pau8_Expression == 0)
    {
        return "error";
    }
    int32_t s32_ExpressionLength=0;
    int32_t s32_I=0;
    uint8_t u8_Data=0;
    s32_ExpressionLength = strlen(pau8_Expression);
    /*push any parentheses into stack array*/
    for(s32_I=0; s32_I<s32_ExpressionLength;s32_I++)
    {
        if(pau8_Expression[s32_I]== '('  || pau8_Expression[s32_I]== ')'
          ||pau8_Expression[s32_I]== '{' || pau8_Expression[s32_I]== '}'
          ||pau8_Expression[s32_I]== '[' ||pau8_Expression[s32_I]== ']')
        {
            StsckPush(pau8_Expression[s32_I]);
        }
        else
        {

        }
    }
    PrintStack();
    if(gstrStackConfig.status == FULL)
    {
        return "full";
    }
    else if (gstrStackConfig.status == EMPTY)
    {
        return pau8_ComMessage3;
    }
    else
    {

        for(int i=gstrStackConfig.top; i>=0 ;i--)
        {
            u8_Data= StackPop();
            if(u8_Data== ')')
            {
                gu32_NormalParCont++;
            }
            else if(u8_Data =='(')
            {
                gu32_NormalParCont--;

                if(gu32_NormalParCont == 0)
                {
                    break;
                }
                else
                {

                }
            }
            else if(u8_Data =='}')
            {
                gu32_CurleyParCont++;
            }
            else if(u8_Data =='{')
            {
                gu32_CurleyParCont--;
                if(gu32_CurleyParCont == 0U)
                {
                    break;
                }
                else
                {

                }
            }
            else if(u8_Data ==']')
            {
                gu32_ParCont++;
            }
            else if(u8_Data =='[')
            {
                gu32_ParCont--;
                if(gu32_ParCont == 0U)
                {
                    break;
                }
                else
                {

                }
            }
            else
            {

            }

        }
        if(gu32_ParCont == gu32_NormalParCont &&  gu32_NormalParCont == gu32_CurleyParCont
           &&gu32_CurleyParCont == 1U /*1 is initial value of counters*/)
        {
            return pau8_ComMessage1;
        }
        else
        {
            gu32_CurleyParCont=1U;
            gu32_NormalParCont=1U;
            gu32_ParCont=1U;
            return pau8_ComMessage2;
        }

    }
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
