#ifndef ROBOT_CONTROL_H_
#define ROBOT_CONTROL_H_


#define APPROACHING_DISTANCE (50)
#define TURNING_DISTANCE_MAX (35)
#define TURNING_DISTANCE_MIN (30)
#define TRUE                 (1)
#define FALSE                (0)
#define STOP_DELAY           (500)

typedef enum{
	
	NO_OBSTACLES_AHEAD     = 0,
	APPROACHING_OBSTACLE   = 1,
	CLOSE_TO_OBSTACLE      = 2,
	VERY_CLOSE_TO_OBSTACLE = 3
	
	}EN_currentCarState_t;
	
EN_currentCarState_t ROBOT_getCurrentState(void);
void ROBOT_moveUpdate(void);
void ROBOT_init(void);

#endif 