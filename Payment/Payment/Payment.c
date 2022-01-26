#include "Payment.h"
ST_accountBalance_t gArr_serverData[u8_MAX_ARR_SIZE] = {{100.00,{"123456789"}},{6000.00,{"234567891"}},
                {3250.25,{"567891234"}},{1500.12,{"456789123"}},{500.00,{"258649173"}},{2100.00,{"654823719"}},
                {0.00,{"971362485"}},{1.00,{"793148625"}},{10.12,{"123123456"}},{0.55,{"456789321"}}} ;



void PAY_getCardData(void)
{
    printf("Please Enter Card Data:\n");
    printf("Please Enter the Card Holder Name:\n");
    gets(ST_cardData.cpu8_cardHolderName);
    printf("Please Enter the Primary Account Number:\n");
    gets(ST_cardData.cpu8_primaryAccountNumber);
    printf("Please card Expiry Date:\n");
    gets(ST_cardData.cpu8_cardExpirationDate);
}

void PAY_getTerminalData(void)
{
    printf("Please Enter Terminal Data:\n");
    printf("Please Enter the transaction Amount:\n");
    scanf("%f",&ST_terminalData.f32_transAmount);
    while ( getchar() != '\n' );

}
void PAY_getBalancData(void)
{

    printf("Please Enter the transaction date:\n");
    gets(ST_terminalData.cpu8_transactionDate);

}
EN_transStat_t PAY_isCardExpired(void)
{
    uint16_t u8_cardExpMM=0;
    uint16_t u8_cardExpYY=0;
    uint16_t u8_trasDateMM=0;
    uint16_t u8_trasDateYY=0;
    //12/22 12/10/2022
    u8_cardExpMM=(((ST_cardData.cpu8_cardExpirationDate[0]- '0') *10) + (ST_cardData.cpu8_cardExpirationDate[1] - '0'));
    u8_cardExpYY=(((ST_cardData.cpu8_cardExpirationDate[3]- '0') *10) + (ST_cardData.cpu8_cardExpirationDate[4] - '0'));
    u8_trasDateMM=(((ST_terminalData.cpu8_transactionDate[3]- '0') *10) + (ST_terminalData.cpu8_transactionDate[4] - '0'));
    u8_trasDateYY=(((ST_terminalData.cpu8_transactionDate[8]- '0') *10) + (ST_terminalData.cpu8_transactionDate[9] - '0'));

    if(u8_trasDateYY > u8_cardExpYY)
    {
        return DECLINED;
    }
    else
    {
        if (u8_trasDateMM > u8_cardExpMM)
            return DECLINED;
        else
        {
            return APPROVED;
            printf("%d\n",u8_cardExpMM);
            printf("%d\n",u8_cardExpYY);
            printf("%d\n",u8_trasDateMM);
            printf("%d\n",u8_trasDateYY);

        }
    }
}
EN_transStat_t PAY_isAmountAccepted(void)
{
    ST_terminalData.f32_maxTransAmount = 6000.00;
    if(ST_terminalData.f32_maxTransAmount > ST_terminalData.f32_transAmount)
        return APPROVED;
    else
         return DECLINED;
}
EN_transStat_t PAY_isBalanceAccepted(float32_t F32_Balanc)
{
    if(F32_Balanc > ST_terminalData.f32_transAmount)
        return APPROVED;
    else
         return DECLINED;
}
EN_transStat_t PAY_PanExists(void)
{
    uint8_t u8_I=0;
    uint8_t u8_comparResult=0;
    uint8_t u8_count=0;
    EN_transStat_t EN_CurrentState;
    for(u8_I=0 ; u8_I<u8_MAX_ARR_SIZE;u8_I++)
    {
        u8_comparResult=strcmp(gArr_serverData[u8_I].cpu8_primaryAccountNumber,ST_cardData.cpu8_primaryAccountNumber);
        if(u8_comparResult == 0)
        {
            EN_CurrentState=PAY_isBalanceAccepted(gArr_serverData[u8_I].f32_balance);
            return EN_CurrentState;
        }


    }
    return   DECLINED;

}

void PAY_checkApproved(EN_transStat_t EN_transState)
{
    if(EN_transState == APPROVED)
    printf("The Transaction is APPROVED\n");
    else
    printf("The Transaction is DECLINE\n");
}
