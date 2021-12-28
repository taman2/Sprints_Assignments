#ifndef XO_H_INCLUDED
#define XO_H_INCLUDED
typedef char            uint8_t;
typedef int             int32_t;
typedef unsigned int    uint32_t;
typedef short int       uint16_t;




/*- INCLUDES -----------------------------------------------*/
#include <stdio.h>
/*- CONSTANTS ----------------------------------------------*/
#define row 3
#define col 3
#define MAX_PLAY_NUM 8
/*- PRIMITIVE TYPES ----------------------------------------*/

extern uint8_t user_input[row][col];
extern uint8_t gu8_PlayCounter;


/*- ENUMS --------------------------------------------------*/
typedef enum{
    player1=1,
    player2
}enuPlayer_t;
extern enuPlayer_t genu_Player;
typedef enum{
    POS_ERR=1,
    POS_VAL
}enuErrorPos_t;
extern enuErrorPos_t genu_ErrorPos;
typedef enum{
    PLAY=1,
    PLAYER1_WIN,
    PLAYER2_WIN,
    DRAW
}enuGameState_t;
enuGameState_t genu_GameState;

/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/
enuErrorPos_t save_user_data(uint8_t pos,enuPlayer_t player);
void board(enuPlayer_t player);
void check_win(enuPlayer_t player);
void check_end(void);


#endif // XO_H_INCLUDED
