#include <stdio.h>

int isPrime(int num) 
{
    if (num <= 1) return 0;

    for (int i = 2; i * i <= num; i++) 
    {
        if (num % i == 0) return 0;
    }

    return 1;
}

void main() 
{
    int start, end;
    printf("Enter two numbers (intervals) : \n");
    scanf("%d %d", &start, &end);

    if (start < 2) start = 2;
    printf("Prime numbers between %d and %d are : ", start, end);
    
	for (int i = start; i <= end; i++)
    {
        if (isPrime(i)) printf("%d ", i);
    }
    printf("\n");
}
