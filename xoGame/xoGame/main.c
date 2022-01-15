#include <stdio.h>
#include <stdlib.h>
#include "XO.h"


int main()
{
    uint32_t user_position=0;
    genu_GameState=PLAY;
    while(1)
    {
        check_end();
        switch(genu_Player)
        {
            case player1:
                board(player1);
                scanf(" %d",&user_position);
                if(user_position >=(0U) && user_position <= (8U))
                {
                    genu_ErrorPos=save_user_data(user_position,player1);
                    if(genu_ErrorPos == POS_VAL)
                    {
                        check_win(player1);
                        genu_Player=player2;
                        user_position=0;
                    }
                    else
                    {
                        genu_Player=player1;
                        printf("please enter valid position from 0 to 8 \n");

                    }
                }
                else
                {

                    printf("please enter valid position from 0 to 8 \n");
                    genu_Player=player1;

                }
                break;
            case player2:
                board(player2);
                scanf(" %d",&user_position);
                if(user_position >=(0U/*+ASCII*/) && user_position <= (8U/*ASCII*/))
                {
                    genu_ErrorPos=save_user_data(user_position,player2);
                    if(genu_ErrorPos == POS_VAL)
                    {
                        check_win(player2);
                        genu_Player=player1;
                    }
                    else
                    {
                        genu_Player=player2;
                        printf("please enter valid position from 0 to 8 \n");
                    }

                }
                else
                {
                    genu_Player=player2;
                    printf("please enter valid position from 0 to 8 \n");
                }
                break;
        }
    }
    return 0;
}
