#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 0, y = 0;
    printf("Enter Two Numbers : \n");
    scanf("%d %d", &x, &y);

    char ch;
    printf("Enter an Operator : ");
    scanf(" %c", &ch);

    switch (ch)
    {
        case '+' :
                printf("%d + %d = %d", x, y, x + y);
                break;

        case '-':
            printf("%d - %d = %d", x, y, x - y);
            break;

        case '*':
            printf("%d * %d = %d", x, y, x * y);
            break;

        case '/':
            if (y)  printf("%d / %d = %d", x, y, x / y);
            else printf("Can't devide by zero \n");           
            break;
    }
    return 0;
}
