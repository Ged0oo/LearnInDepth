#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a Number : ");
    int n=0, sum=0;
    scanf("%d", &n);

    for (int i = 0; i <= n; i++) sum += i;
    printf("Sum = %d", sum);

    return 0;
}
