#include <stdio.h>
#include <stdlib.h>

void main(void) 
{
	int n,key;

	printf("Enter Number of Elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	int a[n];
	for(int i=0; i<n; i++) scanf("%d",&a[i]);

	printf("Enter Key Element : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&key);
	
    for(int i=0; i<n; i++)
	{
    	if(a[i]==key) printf("Key found at location : %d", i+1);
    }
	return 0;
}