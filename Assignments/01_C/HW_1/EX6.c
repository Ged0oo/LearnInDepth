#include <stdio.h>
#include <stdlib.h>

void SWAP(int* x, int* y)
{
    *x = *x + *y; 
    *y = *x - *y; 
    *x = *x - *y;
}

int main()
{
    printf("Enter Two Numbers : \n");
    int x = 0, y = 0;
    scanf("%d %d", &x, &y);

    printf("Before Swapping Numbers : %d %d\n", x, y);
    SWAP(&x, &y);
    printf("After Swapping Numbers : %d %d\n", x, y);

    return 0;
}
