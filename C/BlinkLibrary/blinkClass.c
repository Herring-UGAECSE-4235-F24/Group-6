/*
 * blinkClass.c
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
#include "E4235.h"



// Blinks on RPi Plug P1 pin 32 (which is GPIO pin 12)
//#define PIN GPIO12


int main(int argc, char **argv)
{
	printf("Enter on time in ns\n");
    int onTime;
    scanf("%d", &onTime);
    printf("Enter off time in ns\n");
    int offTime;
    scanf("%d", &offTime);
	
	E4235_Select(12, 1); //set GPIO 12 as output
	
	int pins[1] = {12};
	
	while(1) {
		E4235_multiwrite(pins, 1, 1);
		E4235_delayMicro(onTime);
		E4235_multiwrite(pins, 1, 0);
		E4235_delayMicro(offTime);
	}
	return 0;
}

