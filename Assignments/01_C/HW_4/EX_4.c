#include <stdio.h>

double power(double base, int exponent)
{
    if (exponent == 0) return 1.0;
    else if (exponent > 0) return base * power(base, exponent - 1);
    else return 1.0 / (base * power(base, -exponent - 1));
}

void main() 
{
    double base;
    printf("Enter the base: ");
    scanf("%lf", &base);

    int exponent;
    printf("Enter the exponent: ");
    scanf("%d", &exponent);

    double result = power(base, exponent);
    printf("%.2lf ^ %d = %.2lf\n", base, exponent, result);
}