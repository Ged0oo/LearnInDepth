#include "Main_Algorithm.h"


unsigned int MA_Pressure_Value = 0 ;
unsigned int MA_Pressure_Threshold = 20 ;


void (*MA_State)();


void Set_Pressure_Value(int Pressure_Value)
{
    MA_Pressure_Value = Pressure_Value ;
    MA_State = State(MA_High_Pressure_Detect);
}


State_Define(MA_High_Pressure_Detect)
{
    MA_State_id = MA_High_Pressure_Detect ;

    if(MA_Pressure_Value <= MA_Pressure_Threshold)
    {
        MA_State = State(MA_High_Pressure_Detect);
    }
    else
    {
        High_Pressure_Detected();
        MA_State = State(MA_High_Pressure_Detect);
    }
}