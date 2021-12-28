/*- INCLUDES
----------------------------------------------*/
#include "XO.h"

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
enuPlayer_t genu_Player=player1;
enuErrorPos_t genu_ErrorPos =POS_VAL;
enuGameState_t genu_GameState;
uint8_t user_input[row][col]={'0','1','2','3','4','5','6','7','8'};
uint8_t gu8_PlayCounter=0;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*- APIs IMPLEMENTATION
-----------------------------------*/
void board(enuPlayer_t player)
{
	printf("*********************XO BOARD ***********************\n");
	printf("-------------------\n");
	printf(" %c   | %c   | %c   |\n", user_input[0][0], user_input[0][1], user_input[0][2]);
	printf("-----|-----|------\n");
	printf(" %c   | %c   | %c   |\n", user_input[1][0], user_input[1][1], user_input[1][2]);
	printf("-----|-----|------\n");
	printf(" %c   | %c   | %c   |\n", user_input[2][0], user_input[2][1], user_input[2][2]);
	printf("-------------------\n");
	printf("*********************XO BOARD ***********************\n");
	if(player == player1)
    {
        printf("player1 Please select your position form 0 to 8\n");
        printf("player1 position:");
    }
    else
    {
        printf("player2 Please select your position form 0 to 8\n");
        printf("player2 position:");

    }

}

enuErrorPos_t save_user_data(uint8_t pos,enuPlayer_t player)
{
    uint8_t i=0;
    uint8_t j=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if((pos-ASCII) == ((row*i)+j) )
            {
                /*check if this position was used before */
                if(user_input[i][j]=='X' || user_input[i][j]== 'O')
                {
                    return POS_ERR;
                }
                else
                {
                    if(player == player1)
                    {

                        user_input[i][j]='X';
                        gu8_PlayCounter++;
                    }
                    else
                    {
                        user_input[i][j]='O';
                        gu8_PlayCounter++;
                    }
                    return POS_VAL;
                }
            }
            else
            {

            }
        }
    }

}
void check_win(enuPlayer_t player)
{
    uint8_t i=0;
    uint8_t j=0;
    if(player == player1)
    {
        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {

                if(user_input[i][0]== user_input[i][1] && user_input[i][1]== user_input[i][2] && user_input[i][0]=='X')
                {
                    genu_GameState=PLAYER1_WIN;
                    break;
                }
                else if(user_input[0][i]== user_input[1][i] && user_input[1][i]== user_input[2][i] && user_input[1][i]=='X')
                {
                    genu_GameState=PLAYER1_WIN;
                    break;

                }
                else if(i ==0 && j==0)
                {
                    if(user_input[i][j]== user_input[i+1][j+1] && user_input[i+1][j+1]== user_input[i+2][j+2] && user_input[i][j]=='X')
                    {
                        genu_GameState=PLAYER1_WIN;
                        break;
                    }
                    else if(user_input[i][j+2]== user_input[i+1][j+1] && user_input[i+1][j+1]== user_input[i+2][j] && user_input[i][j+2]=='X')
                    {
                        genu_GameState=PLAYER1_WIN;
                        break;
                    }
                    else
                    {

                    }
                }
            }
        }
    }
    else
    {
        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                if(user_input[i][0]== user_input[i][1] && user_input[i][1]== user_input[i][2] && user_input[i][0]=='O')
                {
                    genu_GameState=PLAYER2_WIN;
                    break;


                }
                else if(user_input[0][i]== user_input[1][i] && user_input[1][i]== user_input[2][i] && user_input[1][i]=='O')
                {
                   // printf(" /*/*/*/*/*/*/**/ PLAYER2 WIN */**/*//**/*/***/\n");
                    genu_GameState=PLAYER2_WIN;
                    break;


                }
               else if(i ==0 && j==0)
                {
                    if(user_input[i][j]== user_input[i+1][j+1] && user_input[i+1][j+1]== user_input[i+2][j+2] && user_input[i][j]=='O')
                    {
                        genu_GameState=PLAYER2_WIN;
                        break;
                    }
                    else if(user_input[i][j+2]== user_input[i+1][j+1] && user_input[i+1][j+1]== user_input[i+2][j] && user_input[i][j+2]=='O')
                    {
                        genu_GameState=PLAYER2_WIN;
                        break;
                    }
                    else
                    {

                    }
                }
             }
        }


    }
}
void check_end(void)
{

    if(gu8_PlayCounter == MAX_PLAY_NUM)
    {
        genu_GameState=DRAW;
        printf(" /*/*/*/*/*/*/**/  DRAW */**/*//**/*/***/\n");
        gu8_PlayCounter=0;
        genu_Player = player1;

    }
    if(genu_GameState != PLAY)
    {
        if(genu_GameState == PLAYER1_WIN)
        {
            board(player1);
            printf(" /*/*/*/*/*/*/**/ PLAYER1 WIN */**/*//**/*/***/\n");

        }
        else if(genu_GameState == PLAYER2_WIN)
        {
            board(player2);
            printf(" /*/*/*/*/*/*/**/ PLAYER2 WIN */**/*//**/*/***/\n");

        }
        genu_GameState = PLAY;
        uint8_t au8_i=0;
        uint8_t au8_j=0;
        uint8_t au8_count=0;
        for(au8_i=0;au8_i<row;au8_i++)
        {
            for(au8_j=0;au8_j<col;au8_j++)
            {
                if(au8_count == ((row*au8_i)+au8_j) )
                {
                     user_input[au8_i][au8_j]=au8_count+48;
                }
               au8_count++;

            }
        }
        genu_Player = player1;
        gu8_PlayCounter=0;


    }

}


