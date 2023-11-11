#include "CA.h"
#include "US.h"
#include "Motor.h"

void SystemSetup();

int main ()
{
	SystemSetup();
    int counter;
	
    while(1)
    {
        P_US_State();
        for(counter =1 ; counter > 0 ; counter++);
		
        P_CA_State();
        for(counter =1 ; counter > 0 ; counter++);
        
		P_Motor_State();
        for(counter =1 ; counter > 0 ; counter++);
    }
}

void SystemSetup()
{
    // Init Modules
    //Set State pointer for each block
    P_CA_State = State(CA_Waiting);
    P_US_State = State(US_Busy);
	P_Motor_State = State(Motor_Idle);
}