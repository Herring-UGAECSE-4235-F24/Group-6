#include <stdio.h>
#include <stdlib.h>
#include "E4235.h"

//Testing class library
//WRITE PIN = 26
//READ PIN = 21

int main(int argc, char **argv)
{
	E4235_Select(26, 1); //set GPIO 26 as output
	E4235_Select(21, 1); //set GPIO 21 as input
	
	int write[1] = {26};
	int read[1] = {21};
	
	E4235_multiwrite(read, 1, 0);
	//printf("Read test: %d", E4235_multiread(read, 1));

	
	/*while(1) {
		E4235_multiwrite(write, 1, 1);
		E4235_delayMicro(10000);
		E4235_multiwrite(write, 1, 0);
		E4235_delayMicro(10000);
	}*/
	
	return 0;
}

