#include <stdio.h>
#include <stdlib>
#include <string.h>

void main(void) 
{
	char c[50];
	int i;

	printf("Enter String : ");
	fflush(stdin); fflush(stdout);
	gets(c);

	printf("Reversed String : ");
	for(i=strlen(c); i>=0; i--) printf("%c",c[i]);
	return 0;
}