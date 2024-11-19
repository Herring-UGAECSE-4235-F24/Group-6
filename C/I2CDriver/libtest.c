#include <stdio.h>
#include <stdlib.h>
#include "E4235.h"
//UNUSED FOR I2CDRIVER
//Testing class library

int main(int argc, char **argv)
{
	//WRITE LOW TO BOTH PINS. THEN SWITCH BETWEEN INPUT AND OUTPUT (INSTEAD OF HIGH AND LOW)
	
	E4235_Select(26, 0); //set pins as output
	E4235_Select(21, 1);
	
	int pins[1] = {26};
	
	for (int i = 0; i < 10; i++) {
		int result = E4235_multiread(pins, 1);
		printf("%d\n", result);
	}
	/*int pins[2] = {21, 26}; //define array for multiwrite
	
	E4235_multiwrite(pins, 2, 0);
	
	E4235_Select(26, 0); //set pins as input, ready for i2c now
	E4235_Select(21, 0);*/

	
	return 0;
}

