#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter Three Numbers : \n");
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);

    if (x > y)
    {
        if (x > z) printf("%d is the Greatest\n", x);
        else printf("%d is the Greatest\n", z);
    }
    else if (y>z) printf("%d is the Greatest\n", y);
    else printf("%d is the Greatest\n", z);

    return 0;
}
