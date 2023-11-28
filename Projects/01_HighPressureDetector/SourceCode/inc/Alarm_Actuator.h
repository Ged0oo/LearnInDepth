#ifndef __ALARM_ACTUATOR_H__
#define __ALARM_ACTUATOR_H__

#include "State.h"

enum 
{
    AC_Waiting   ,
    AC_Alarm_OFF ,
    AC_Alarm_ON  
}AC_State_id;


void AC_init();


State_Define(AC_Waiting);
State_Define(AC_Alarm_OFF);
State_Define(AC_Alarm_ON);


extern void(*AC_State)();


#endif //__ALARM_ACTUATOR_H__