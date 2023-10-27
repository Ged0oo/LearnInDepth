#include <stdio.h>
#include <stdlib.h>

void main(void) 
{
	int n,x,location;

	printf("Enter no of elements: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	int a[n+1];
	for(int i=0; i<n; i++) scanf("%d",&a[i]);

	printf("Enter Element to Inserte : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	printf("Enter Location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);

	for(int i=n;i>=location-1;i--) a[i+1] = a[i];
	a[location-1]=x;
	for(int i=0; i<n+1; i++) printf("%d ",a[i]);

	return 0;
}