#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"
#include "Payment.h"

int main()
{
    EN_transStat_t EN_transStat = APPROVED;
   uint8_t gu8_UserInput='y';

    while(gu8_UserInput=='y')
    {
        PAY_getCardData();
        PAY_getTerminalData();
        EN_transStat = PAY_isAmountAccepted();
        if(EN_transStat == DECLINED)
        {
            printf("The Transaction is DECLINE\n");
            printf("Do you want to continue (y/n)?:\n");
            scanf(" %c",&gu8_UserInput);
        }
        else
        {
            PAY_getBalancData();
            EN_transStat = PAY_isCardExpired();
            if(EN_transStat == APPROVED)
            {
                EN_transStat = PAY_PanExists();
                if(EN_transStat == APPROVED)
                {
                    PAY_checkApproved(EN_transStat);
                }
                else
                {
                    PAY_checkApproved(EN_transStat);
                }
            }
            else
            {
                PAY_checkApproved(EN_transStat);
            }
            printf("Do you want to continue (y/n)?:\n");
            scanf(" %c",&gu8_UserInput);
        }
         while ( getchar() != '\n' );  // repeatedly read characters from input stream;
    }

    return 0;
}
