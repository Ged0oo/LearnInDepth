#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter a Character : ");
    char ch;
    scanf("%c", &ch);

    if (
        (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u') ||
        (ch == 'A') || (ch == 'E') || (ch == 'I') || (ch == 'O') || (ch == 'U')
        )
        printf("Vowel");
    else printf("Constant");

    return 0;
}
