#include <stdio.h>
#include <string.h>

void main(void)
{
	char str[20], rev[20];	
	char* p_str = str;
	char* p_rev = rev;
	int i,j;

	printf("Input a string : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",str);

	for(i = strlen(str) - 1,j = 0; i >= 0; i-- , j++) *(p_rev + j) = *(p_str + i) ;
	*(p_rev + j) = '\0';
	puts(p_rev);
}