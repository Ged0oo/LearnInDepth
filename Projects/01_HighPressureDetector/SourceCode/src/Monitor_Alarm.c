#include "Monitor_Alarm.h"


unsigned int MoA_Periode = 50000;


void(*MoA_State)();


void High_Pressure_Detected()
{
    MoA_State = State(MoA_Alarm_ON);
}


State_Define(MoA_Alarm_OFF)
{
    MoA_State_id = MoA_Alarm_OFF ;
    Stop_Alarm();
    MoA_State = State(MoA_Alarm_OFF);
}


State_Define(MoA_Alarm_ON)
{
    MoA_State_id = MoA_Alarm_ON ;
    Start_Alarm();
    MoA_State = State(MoA_Waiting);
}


State_Define(MoA_Waiting)
{
    MoA_State_id = MoA_Waiting ;
    Stop_Alarm();
    Delay(MoA_Periode);
    MoA_State = State(MoA_Alarm_OFF);
}