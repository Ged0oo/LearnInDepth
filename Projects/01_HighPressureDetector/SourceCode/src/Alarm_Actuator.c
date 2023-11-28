#include "Alarm_Actuator.h"

void(*AC_State)();

void AC_init()
{
    /*
	 * Intialize Alarm_Actuator Driver
	 */
}

void Stop_Alarm()
{
    AC_State = State(AC_Alarm_OFF);
}


void Start_Alarm()
{
    AC_State = State(AC_Alarm_ON);
}


State_Define(AC_Waiting)
{
    AC_State_id = AC_Waiting;
    AC_State = State(AC_Waiting);
}


State_Define(AC_Alarm_ON)
{
    AC_State_id = AC_Alarm_ON;
    Set_Alarm_actuator(0);
    AC_State = State(AC_Waiting);
}


State_Define(AC_Alarm_OFF)
{
    AC_State_id = AC_Alarm_OFF;
    Set_Alarm_actuator(1);
    AC_State = State(AC_Waiting);
}