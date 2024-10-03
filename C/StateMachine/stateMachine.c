#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "bcm2835.h" //we used the bcm library for the whole project due to issues with the class lib

void printnums(char output[8]) { //outputs to the logic analyzer
	for(int o = 10; o < 18; o++) {
		if(output[o-10] == '1') {
			bcm2835_gpio_write(o, HIGH);
		} else {
			bcm2835_gpio_write(o, LOW);
		}
	}
}

long currentMicros() { 		//Our timer function that finds the amount of microseconds that have passed since program start.
				//Based on code from Dave's Brain: davekb.com/browse_programming_tips:c_get_current_time_in_milliseconds:txt
	struct timeval tp;
	
	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000000 + tp.tv_usec; //adds seconds passed to the usec value to track time precisely
}

int main(int argc, char **argv)
{
	if (!bcm2835_init())  //initializing library
      return 1;
      
     for(int x = 9; x < 18; x++){	//initializing output pins & clock
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_OUTP);
	}
	for(int x = 20; x < 24; x++){	//initializing x keypad pins
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_OUTP);
	}
	for(int x = 24; x < 28; x++){	//initializing y keypad pins
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_INPT);
	}
	
	starting:;	//label used to restart the program when * is pressed
	
	// we call our time function to get numbers that can be subtracted and compared
	long anchor = currentMicros(); //used to count 2 seconds since the button was released
	long anchortwo = currentMicros(); //used to alternate between * and the previous value
	long anchorthree = currentMicros(); //used for the clock
	long time = currentMicros();  //used throughout the program to track the current time
	
	//2D string arrays, one for each mode. these will be output to the LA
	char Asci[4][4][8] = {{"00110001","00110010","00110011","01000001"},{"00110100","00110101","00110110","01000010"},{"00110111","00111000","00111001","01000011"},{"00101010","00110000","00100011","01000100"}};
	char Numer[4][4][8] = {{"00000001","00000010","00000011","00001010"},{"00000100","00000101","00000110","00001011"},{"00000111","00001000","00001001","00001100"},{"00101010","00000000","00100011","00001101"}};	

	int xnum = 0;	//x & y values of most recently pressed key
	int ynum = 0;	
	int ascimode = 0;	//current mode, 1 for ascii
	
	int pressed = 0;	//used to exit the initial "waiting mode"
	int hash = 0;		//set if modes are about to be switched
	int hashpress = 0;	//set if hash was the last button pressed
	int release = 0;	//set once a button is released
	int alter = 2;	//flag used to alternate after button is released
	
	int wave = 0; //state of the clock
	
	while(1){	//main loop of program
		time = currentMicros();		//updating time
		if(time - anchorthree > 500 && wave == 0){ //changing clock value every 0.5ms
			wave = 1;
			bcm2835_gpio_write(9, LOW);
			anchorthree = currentMicros();
		}
		else if(time - anchorthree > 500 && wave == 1){ //state of LA only changes on rising edge
		wave = 0;
		bcm2835_gpio_write(9, HIGH);
		anchorthree = currentMicros();
		
		for(int x = 20; x < 24; x++){	//iterating through the keypad
			bcm2835_gpio_write(x, HIGH);
			for(int y = 24; y < 28; y++){
				if(bcm2835_gpio_lev(y)){	//if key is pressed:
					release = 0;
					if (x == 23 & y == 24) {	//restart if * is pressed
						goto starting;
					} else if(x == 23 && y == 26){	//if hash is pressed set flag
						hashpress = 1;		
					} else {				//otherwise set vars to output
						xnum = x-20;
						ynum = y-24;
						pressed = 1;
						}
				} else if(xnum == x-20 && ynum == y-24 && release == 0){ //tracking if most recently pressed key is still pressed
					release = 1;
					alter = 0;
					anchor = currentMicros();
				} else if(hashpress == 1 && x == 23 && y == 26){	//tracking if hash has been released
						hash = 1;
						hashpress = 0;
				}
			}
			bcm2835_gpio_write(x, LOW);
		}
	if(pressed == 0){	//prints '@' until a key is pressed
		alter = 0;
		printnums("01000000");
	} else if(time - anchor > 2000000 && release) {		//if key was released 2 secs ago:
		if(alter == 0 && time - anchortwo > 2000000){	//prints '@' for 0.5 seconds
			anchortwo = currentMicros();
			alter = 1;
			printnums("01000000");
		}
		else if(alter == 1 && time - anchortwo > 500000){ //prints key for 2 seconds
			anchortwo = currentMicros();
			if(ascimode == 1){		//uses one of the two arrays based on current mode
			printnums(Asci[xnum][ynum]);	
			} else {
			printnums(Numer[xnum][ynum]);
			}
			alter = 0;
		}	
	}
	else {
		if (hash == 1) {	//if hash was released, switch mode
			hash = 0;
			if (ascimode == 1) {
				ascimode = 0;
			} else ascimode = 1;
			
		} else if(ascimode == 1){	//if another key was pressed in the last 2 seconds, simply output to the LA
			printnums(Asci[xnum][ynum]);	
		} else{
			printnums(Numer[xnum][ynum]);
			}
		}
	}
	}
	return 0;
}

