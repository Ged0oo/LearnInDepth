#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "state.h"

enum
{
    Motor_Idle,
    Motor_Busy
}Motor_State_Id;

//prototypes
Define_State(Motor_Idle);
Define_State(Motor_Busy);

//Global pointer to next state
void (* P_Motor_State)();

#endif //__MOTOR_H__