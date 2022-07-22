

#include "../HAL/keypad_interface.h"



//Keypad Information
#define R0 0
#define R1 1
#define R2 2
#define C0 3
#define C1 4
#define C2 5

#define keypadPORT PORTC_REG
#define keypadPIN PINC_REG
#define keypadDDR DDRC_REG


//Keypad functions and global variables
char getkey();
int keypadRow[] = {R0, R1, R2}; //rows of the keypad
int keypadCol[] = {C0, C1, C2};//columnd



# define   column_nums 3

# define   ROW_nums    3




 static const uint8_t g_keymap[3][3]={{'1','2','3'},
	                                  {'4','5','6'},
								      {'7','8','9'},
								                   };





void Keyad_VoidINit(void){

	// DIO_SetPortDirection(PORTD ,0b00001111);
	      /*all rows out */
	DIO_SetPinDirection(PORTC ,PIN2 ,OUTPUT);
	DIO_SetPinDirection(PORTC ,PIN3 ,OUTPUT);
	DIO_SetPinDirection(PORTC ,PIN4 ,OUTPUT);

	        /*all columns are input*/
	DIO_SetPinDirection(PORTC ,PIN5 ,INPUT);
	DIO_SetPinDirection(PORTC ,PIN6 ,INPUT);
	DIO_SetPinDirection(PORTC ,PIN7 ,INPUT);

	          /*all output high*/
	 DIO_SetPinValue(PORTC , PIN5 , HIGH);
	 DIO_SetPinValue(PORTC , PIN6 , HIGH);
	 DIO_SetPinValue(PORTC , PIN7 , HIGH);
             /*pull up for inputs*/
	 DIO_SetPinValue(PORTC , PIN2 , HIGH);
	 DIO_SetPinValue(PORTC , PIN3 , HIGH);
	 DIO_SetPinValue(PORTC , PIN4 , HIGH);
}













uint8_t KeyPad_U8Data(void)
   {
	   uint8_t Copy_Pressed_key=21;
	   uint8_t Copy_Colum;
	   uint8_t Copy_Row;
	   
	   for(Copy_Colum=0;Copy_Colum<column_nums;Copy_Colum++)
	   {
		   DIO_SetPinValue(PORTC ,Copy_Colum+5, LOW);

		  for(Copy_Row=0;Copy_Row<ROW_nums;Copy_Row++)
		  {


			  if (0==DIO_GetPinValue(PORTC,Copy_Row +2))
			  {

				 // while(0==DIO_GetPi0nValue(PORTC,Copy_Row +2));
                       TIMER0_msdelay(50);

					    if (1==DIO_GetPinValue(PORTC,Copy_Row +2))
					    	 return g_keymap[Copy_Row][Copy_Colum] ;
			  }
			   else
			   {/*for MEZRARULE */};
		  }
              DIO_SetPinValue(PORTC ,Copy_Colum+5,HIGH);
	   }
	   return Copy_Pressed_key;
   }
/*char getkey()
{
	int i, j;
	uint8_t u8_ptValue=0;
	for(i = 0; i < 3; i++)
	{
		keypadPORT = 0xff;
		CLR_BIT(keypadPORT,(PIN2+i));//send a low  to a particular row of the keypad
		for(j = 0; j < 3; j++)
		{
			u8_ptValue=DIO_GetPinValue(PORTC,(PIN5+j));
			TIMER0_msdelay(50);
			u8_ptValue=DIO_GetPinValue(PORTC,(PIN5+j));
			TIMER0_msdelay(5);
			if(u8_ptValue==0) //check if key is pressed
			{
			 //TIMER0_msdelay(50);
                while(GET_BIT(keypadPIN,(PIN5+j))==0);  //wait for key to be released
				switch(i)
				{
					case(0):
					{
						if (j == 0) return 7;
						else if (j == 1) return 8;
						else if (j == 2) return 9;
						break;
					}
					case(1):
					{
						if (j == 0) return 4;
						else if (j == 1) return 5;
						else if (j == 2) return 6;
						break;
					}
					case(2):
					{
						if (j == 0) return 1;
						else if (j == 1) return 2;
						else if (j == 2) return 3;
						break;
					}
					
				}
			}
		}
	}
	return 55;//Return 'A' if no key is pressed.
}*/