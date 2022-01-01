#include <stdio.h>
#include <stdlib.h>
#include "Compiler.h"
#include "DataTypes.h"

#define  BUFFER_SIZE 50
int8_t   gas8_Buffer[BUFFER_SIZE];
uint8_t *gpu8_UserExpression=0;
uint8_t *gpu8_CompilerMessage=0;
uint8_t  gu8_UserInput='y';

int main()
{
    while(gu8_UserInput=='y')
    {
        StackCreat(10);
        printf(" Test cases for stack FUNCTIONS \n");
        printf(" 1- > stack capacity \n 2- <= stack capacity; 3- capacity +1 \n");
        printf(" Test cases for compiler  FUNCTIONS \n");
        printf(" 1- (()) balanced \n 2-((()) is not balanced  3- ()())()( not balanced 4- {2+5}(15+4) balanced \n\n\n");
        PrintStack();
        printf("Please enter your expression:");
        gets(gas8_Buffer);
        gpu8_CompilerMessage= BalancedParentheses(gas8_Buffer);
        printf("\n\n\n\n");
        printf(" """"Expression Is %s ",gpu8_CompilerMessage);
        printf("\n\n\n\n");
        PrintStack();
        printf("Please enter y to continue:");
        scanf(" %c",&gu8_UserInput);
        /*clear buffer elements */
        for(int32_t s32_I=0;s32_I<BUFFER_SIZE;s32_I++)
        {
            gas8_Buffer[s32_I]=0;
        }
        while ( getchar() != '\n' );  // repeatedly read characters from input stream;
    }

    return 0;
}
