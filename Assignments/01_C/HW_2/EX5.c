#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter a Character : ");
    char ch;
    scanf("%c", &ch);

    if (
        ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))
        )
        printf("%c is an Alphabet", ch);
    else printf("%c is not an Alphabet", ch);

    return 0;
}
