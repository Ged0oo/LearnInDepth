#include <stdio.h>
#include <string.h>

void main(void)
{
	int count = 0;
	char c[50];

	printf("Enter String : ");
	fflush(stdin); fflush(stdout);
	gets(c);


	for (count = 0; c[count]; count++);

	printf("Length of string : %d", count);
	return 0;
}