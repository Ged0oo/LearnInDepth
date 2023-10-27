#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr1[4], arr2[4];
    
    for (int i = 0; i < 4; i++)
    {
        printf("Enter element %d in First array : ", i + 1);
        scanf("%d", &arr1[i]);
    }
    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        printf("Enter element %d in Second array : ", i + 1);
        scanf("%d", &arr2[i]);
    }
    printf("\n");

    printf("Sum of the Previous Matrices : \n");
    printf("\t%d \t %d \n\t%d \t %d\n", arr1[0] + arr2[0], arr1[1] + arr2[1], arr1[2] + arr2[2], arr1[3] + arr2[3]);

    return 0;
}
