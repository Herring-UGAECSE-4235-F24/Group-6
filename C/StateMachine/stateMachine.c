/*
 * stateMachine.c
 * 
 * Copyright 2024  <group6-24@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "E4235.h"
#include "bcm2835.h"

void printnums(char output[8]) {
	for(int o = 10; o < 18; o++) {
		if(output[o-10] == '1') {
			bcm2835_gpio_write(o, HIGH);
		} else {
			bcm2835_gpio_write(o, LOW);
		}
	}
}

long currentMillis() { //remember to cite
	struct timeval tp;
	
	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec/1000;
}

int main(int argc, char **argv)
{
	long anchor = currentMillis();
	long anchortwo = currentMillis();
	long time = currentMillis();
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
	int release = 0;
	int alter = 0;
	while(1){
		long time = currentMillis();
		//printf("%d", time);
		for(int x = 20; x < 24; x++){
			bcm2835_gpio_write(x, HIGH);
			for(int y = 24; y < 28; y++){
				if(bcm2835_gpio_lev(y)){
						xnum = x-20;
						ynum = y-24;
						pressed = 1;
						release = 0;
				} else if(xnum == x-20 && ynum == y-24 && release == 0){
					release = 1;
					anchor = currentMillis();
					if(xnum == 3 && ynum == 2){
						hash = 0;
					}
				}
			}
			bcm2835_gpio_write(x, LOW);
		}
	if(time - anchor > 2000){
		if(alter == 0 && anchortwo - time > 2000){
			anchortwo = currentMillis();
			printf("@\n");
			alter = 1;
			printf("test");
		}
		else if(alter == 1 && anchortwo - time > 500){ 
			anchortwo = currentMillis();
			printf("%c", Vals[xnum][ynum]);
			alter = 0;
		}
			
			
	}
	if(pressed == 0){
		printf("@\n");
		printnums("10000000");
	}
	else{	
		if (xnum == 3 && ynum == 2 && hash == 0) {
			hash = 1;
			if (ascimode == 1) {
				ascimode = 0;
			} else ascimode = 1;
			
		} else if(ascimode == 1){
			printnums(Asci[xnum][ynum]);	
		} else{
			printnums(Numer[xnum][ynum]);
			}
		long now = currentMillis();
		//printf("%d\n", now - anchor);
		//printf("%c\n", Vals[xnum][ynum]);
		//printf("%d\n", ascimode);
		}
	}

	return 0;
}
