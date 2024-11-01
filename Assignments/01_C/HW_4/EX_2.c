#include <stdio.h>

// Function to calculate the factorial of a number using recursion
unsigned long long factorial(int n) 
{
    if (n == 0 || n == 1) return 1;
    else return (n * factorial(n - 1));
}

void main() 
{
    int num;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (num < 0) printf("Factorial is not defined for negative numbers.\n");
    else 
    {
        unsigned long long fact = factorial(num);
        printf("Factorial of %d = %llu\n", num, fact);
    }
}
