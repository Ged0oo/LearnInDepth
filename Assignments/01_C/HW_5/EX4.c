#include <stdio.h>

void main(void) 
{
	int size;
	int arr[15];
	int* ptr = arr;

	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&size);

	printf("Input %d number of elements in the array\n",size);
	for(int i = 0; i<size; i++)
	{
		printf("element - %d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",ptr+i);
	}

	puts("The elements of array in reverse order are :");
	for(int i=size; i>0; i--) printf("element - %d : %d\n",i,*(ptr+i-1));
}