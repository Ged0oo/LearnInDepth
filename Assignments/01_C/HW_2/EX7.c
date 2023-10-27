#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a Number : ");
    int n=0, prod=1;
    scanf("%d", &n);

    if (n < 0) printf("Error, Negative Number\n");
    else
    {
        for (int i = 1; i <= n; i++) prod *= i;
        printf("Product = %d", prod);
    }

    return 0;
}
