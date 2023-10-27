#include <stdio.h>
#include <stdlib>
#include <string.h>

void main(void) 
{
	int count=0;
	char c,a[100];

	printf("Enter string : ");
	fflush(stdin); fflush(stdout);
	gets(a);

	printf("Enter Character to find its Frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);

	for(int i=0; i<strlen(a); i++)
	{
		if(a[i]==c) count++;
	}
	printf("Frequency of %c is : %d",c,count);

	return 0;
}