#include "../SERVICE/CARD_interface.h"

int main(void)
{

	CARD_init();

	
	while(1)
	{
		CARD_voidProgram() ; 
	}
}
