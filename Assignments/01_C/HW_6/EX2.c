#include <stdio.h>

void main(void) 
{
	char alph[26];
	char* ptr = alph;
	int i;

	puts("The Alphabets are :");
	for(i = 0; i<26; i++)
	{
		*(ptr + i) = 'A' + i;
		printf("%c ",*(ptr + i));
	}
}