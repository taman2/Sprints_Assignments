/*
 * Sprints_Atmega32.c
 *
 * Created: 1/9/2022 12:28:39 AM
 * Author : Mohamed Salah Taman
 */ 
#include "../APP/Traffic_APP/Trafic_APP.h"
int main(void)
{
	Traffic_Init();
    while (1) 
    {
		 check_command(garr_Buffer);
		 Traffic_LightControl();

	}
}

