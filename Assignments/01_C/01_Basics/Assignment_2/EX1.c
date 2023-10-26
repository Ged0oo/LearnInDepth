#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter a Number : ");
    int x = 0;
    scanf("%d", &x);

    if (x % 2) printf("%d Odd\n", x);
    else printf("%d Even\n", x);

    return 0;
}
