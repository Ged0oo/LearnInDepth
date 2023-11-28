#include "Pressure_Sensor.h"


unsigned int PS_Value = 0;
unsigned int PS_Pull_Time = 100;


void (*PS_State)();


void PS_init()
{
    /*
	 * Intialize the Pressure Sensor
	 */
}


State_Define(PS_Reading)
{
    PS_State_id = PS_Reading;
    PS_Value = getPressureVal();
    Set_Pressure_Value(PS_Value);
    PS_State = State(PS_Waiting);
}


State_Define(PS_Waiting)
{
    PS_State_id = PS_Waiting;
    Delay(50000);
    PS_State = State(PS_Reading);
}