#include <stdio.h>

extern float e_factorial(float);
extern float e_expo(float, int);

int main(void)
{
	printf("Calculate e^x. Enter x: ");	
	float base;
	scanf("%f", &base);
	float result = 1 + base + (e_expo(base, 2)/e_factorial(2)) + (e_expo(base, 3)/e_factorial(3)) + (e_expo(base, 4)/e_factorial(4)) + (e_expo(base, 5)/e_factorial(5));
	
	printf("e^%f = %f", base, result);
	
	return 0;
}


