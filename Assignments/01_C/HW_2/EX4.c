#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter a Number : ");
    int x;
    scanf("%d", &x);

    if (x == 0) printf("You Entered Zero");
    else if (x > 0) printf("%d is Positive", x);
    else printf("%d is Negative", x);

    return 0;
}
