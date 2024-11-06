#include <stdio.h>

extern float e_factorial(float); //setting up external factorial assembly function
extern float e_expo(float, int); //setting up external exponent assembly function

int main(void)
{
	printf("Calculate e^x. Enter x: ");	//printing welcome message
	float base; //initializing base for storage after input
	scanf("%f", &base); //reading base input
	float result = 1 + base + (e_expo(base, 2)/e_factorial(2)) + (e_expo(base, 3)/e_factorial(3)) + (e_expo(base, 4)/e_factorial(4)) + (e_expo(base, 5)/e_factorial(5)); //performing approximation based on the first five terms of the series
	
	printf("e^%f = %f", base, result); //printing base along with calculated result
	
	return 0;
}


