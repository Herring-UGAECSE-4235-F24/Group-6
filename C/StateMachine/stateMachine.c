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
#include <time.h>
#include "E4235.h"

int main(int argc, char **argv)
{
	/*for(int x = 10; x < 18; x++){
		E4235_Select(x, 1);
	}
	for(int x = 20; x < 24; x++){
		E4235_Select(x, 1);
	}
	for(int x = 24; x < 28; x++){
		E4235_Select(x, 0);
	}*/
	char Vals[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
	int xnum = 0;
	int ynum = 0;
	int pins[1] = {20};
	/*while(1){
		E4235_delayMili(10);
		for(int x = 20; x < 24; x++){
			pins[0] = x;
			E4235_multiwrite(pins, 1, 1);
			for(int y = 24; y < 28; y++){
				printf("%d\n",E4235_Read(x));
				if(E4235_Read(y) == 1){
						xnum = x-20;
						ynum = y-24;
						printf("xnum: %d ynum: %d\n", xnum, ynum);
				}
			}
			E4235_multiwrite(pins, 1, 0);
		}
		//printf("%c\n", Vals[xnum][ynum]);
	}*/
	//pins[0] = 20;
	//E4235_multiwrite(pins, 1, 1);
	E4235_Write(20, 1);
	while(1){
		printf("%d\n",E4235_Read(24));
	}
	//int pins[8] = {10,11,12,13,14,15,16,17};
	//E4235_multiwrite(pins, 8, 0);
	
	//E4235_Write(10, 1);
	return 0;
}

