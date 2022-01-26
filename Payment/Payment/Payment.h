#include "DataTypes.h"


#define u8_MAX_ARR_SIZE    10



typedef struct ST_cardData_t
{
    uint8_t cpu8_cardHolderName[25] ;
    uint8_t cpu8_primaryAccountNumber[20] ;
    uint8_t cpu8_cardExpirationDate[6] ;
}ST_cardData_t;
ST_cardData_t ST_cardData;

typedef struct ST_terminalData_t
{
    float32_t f32_transAmount ;
    float32_t f32_maxTransAmount ;
    uint8_t cpu8_transactionDate[11] ;
}ST_terminalData_t;
ST_terminalData_t ST_terminalData;

typedef enum EN_transStat_t
{
    DECLINED,
    APPROVED
}EN_transStat_t;

typedef struct ST_transaction
{
    ST_cardData_t cardHolderData ;
    ST_terminalData_t transData ;
    EN_transStat_t transStat ;
}ST_transaction ;


typedef struct ST_accountBalance_t
{
    float32_t f32_balance;
    uint8_t cpu8_primaryAccountNumber[20] ;
}ST_accountBalance_t;
/********************************************************************************************************
                    funs prototypes                                                                     *
********************************************************************************************************/
void PAY_getCardData(void);
void PAY_getTerminalData(void);
void PAY_getBalancData(void);
EN_transStat_t PAY_isCardExpired(void);
EN_transStat_t PAY_isAmountAccepted(void);
EN_transStat_t PAY_isBalanceAccepted(float32_t F32_Balanc);
EN_transStat_t PAY_PanExists(void);
void PAY_checkApproved(EN_transStat_t EN_transState);
