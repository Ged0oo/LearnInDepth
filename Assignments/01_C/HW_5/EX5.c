#include <stdio.h>
#define area(r) 3.14*r*r

void main(void) 
{

	float r;
	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);
	printf("Area = %0.2f",area(r));
}