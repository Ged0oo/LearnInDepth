#include <stdio.h>

void reverseSentence() 
{
    char c;
    scanf("%c", &c);

    if (c != '\n') 
    {
        reverseSentence();
        printf("%c", c);
    }
}

void main() 
{
    printf("Enter a sentence : ");
    reverseSentence();
    printf(" is the Reversed sentence\n");
}
