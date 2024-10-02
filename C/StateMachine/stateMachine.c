#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "E4235.h"
#include "bcm2835.h"
#include <string.h>

void printnums(char output[8], int mode) {
	for(int o = 10; o < 18; o++) {
		if(output[o-10] == '1') {
			bcm2835_gpio_write(o, HIGH);
		} else {
			bcm2835_gpio_write(o, LOW);
		}
		printf("mode : %d\n", mode);
	}
}

long currentMicros() { //remember to cite
	struct timeval tp;
	
	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000000 + tp.tv_usec;
}

int main(int argc, char **argv)
{
	long anchor = currentMicros();
	long anchortwo = currentMicros();
	long anchorthree = currentMicros();
	long time = currentMicros();
	if (!bcm2835_init())
      return 1;
      
	for(int x = 10; x < 18; x++){
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_OUTP);
	}
	for(int x = 20; x < 24; x++){
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_OUTP);
	}
	for(int x = 24; x < 28; x++){
		bcm2835_gpio_fsel(x, BCM2835_GPIO_FSEL_INPT);
	}
	char Asci[4][4][8] = {{"00110001","00110010","00110011","01000001"},{"00110100","00110101","00110110","01000010"},{"00110111","00111000","00111001","01000011"},{"00101010","00110000","00100011","01000100"}};
	char Numer[4][4][8] = {{"00000001","00000010","00000011","00001010"},{"00000100","00000101","00000110","00001011"},{"00000111","00001000","00001001","00001100"},{"00101010","00000000","00100011","00001101"}};	
	char Vals[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	int xnum = 0;
	int ynum = 0;
	int ascimode = 0;
	int pressed = 0;
	int hash = 0;
	int hashpress = 0;
	int release = 0;
	int alter = 2;
	char temp = '@';
	int wave = 0;
	while(1){
		long time = currentMicros();
		//printf("%d\n", time);
		if(time - anchorthree > 500 && wave == 0){
			wave = 1;
			bcm2835_gpio_write(9, LOW);
			anchorthree = currentMicros();
		}
		else if(time - anchorthree > 500 && wave == 1){
		wave = 0;
		bcm2835_gpio_write(9, HIGH);
		anchorthree = currentMicros();
		
		for(int x = 20; x < 24; x++){
			bcm2835_gpio_write(x, HIGH);
			for(int y = 24; y < 28; y++){
				if(bcm2835_gpio_lev(y)){
					release = 0;
					if(x != 23 && y != 26){
						xnum = x-20;
						ynum = y-24;
						pressed = 1;		
					} else hashpress = 1;
				} else if(xnum == x-20 && ynum == y-24 && release == 0){
					release = 1;
					alter = 0;
					anchor = currentMicros();
				} else if(hashpress == 1 && x == 23 && y == 26){
						hash = 1;
						hashpress = 0;
				}
			}
			bcm2835_gpio_write(x, LOW);
		}
	
	if(time - anchor > 2000000 && release) {
		//printf("%c" ,temp);
		if(alter == 0 && time - anchortwo > 2000000){
			anchortwo = currentMicros();
			temp = '@';
			alter = 1;
			printnums("10000000", ascimode);
		}
		else if(alter == 1 && time - anchortwo > 500000){ 
			anchortwo = currentMicros();
			temp = Vals[xnum][ynum];
			if(ascimode == 1){
			printnums(Asci[xnum][ynum], ascimode);	
			} else {
			printnums(Numer[xnum][ynum], ascimode);
			}
			alter = 0;
		}	
	}
	if(pressed == 0){
		alter = 0;
	}
	else{
		//printf("%c, asciimode: %d\n", Vals[xnum][ynum], ascimode);	
		if (hash == 1) {
			hash = 0;
			if (ascimode == 1) {
				ascimode = 0;
			} else ascimode = 1;
			
		} else if(ascimode == 1){
			printnums(Asci[xnum][ynum], ascimode);	
		} else{
			printnums(Numer[xnum][ynum], ascimode);
			}
		//long now = currentMicros();
		//printf("%d\n", now - anchor);
		//printf("%c\n", Vals[xnum][ynum]);
		//printf("%d\n", ascimode);
		}
	}
	}
	return 0;
}

