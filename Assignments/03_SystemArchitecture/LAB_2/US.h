#ifndef __US_H__
#define __US_H__

#include "state.h"

enum
{
    US_Busy
}US_State_Id;

//prototypes
Define_State(US_Busy);

//Global pointer to next state
void (* P_US_State)();

#endf //__US_H__