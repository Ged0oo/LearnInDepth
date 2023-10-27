#include <stdio.h>

void main(void) 
{

	int m = 29;
	printf("Address of m : 0x%x\n",(unsigned int)&m);
	printf("Value of m : %d\n",m);

	int* ab;
	ab = &m;
	puts("Now ab is assigned with the address of m.");
	printf("Address of pointer ab : 0x%x\n",(unsigned int)ab);
	printf("Content of pointer ab : %d\n",*ab);

	m = 34;
	puts("The value of m assigned to 34 now.");
	printf("Address of pointer ab : 0x%x\n",(unsigned int)ab);
	printf("Content of pointer ab : %d\n",*ab);

	*ab = 7;
	puts("The pointer variable ab is assigned with the value 7 now.");
	printf("Address of m : 0x%x\n",(unsigned int)&m);
	printf("Value of m : %d",m);
}