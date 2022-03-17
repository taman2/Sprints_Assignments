#include "./ROBOT_CONTROL/ROBOT_control.h"
#include "../ECUAL/MOTOR_CONTROL/MOTOR.h"
#include "../ECUAL/softwarePWM/softwarePWM_interface.h"
#include "../MCAL/GLOBAL_INTERRUPT/GLOBAL_INTERRUPT.h"

int main()
{
	GI_enable();
	ROBOT_init();
	
	while(1){
		
		ROBOT_moveUpdate();
	}
}


