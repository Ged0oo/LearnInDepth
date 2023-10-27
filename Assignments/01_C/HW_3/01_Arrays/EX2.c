#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int n=0;
	printf("Enter Number of Data: ");
	fflush(stdin); fflush(stdout);
    scanf("%d",&n);
	float a[n], sum=0.0;
	
    for(int i=0 ; i<n ; i++)
	{
    	printf("%d. Enter number : ", i+1);
    	fflush(stdin); fflush(stdout);
    	scanf("%f",&a[i]);
    	sum+=a[i];
    }
    printf("Average = %0.2f",sum/n);
	return 0;
}