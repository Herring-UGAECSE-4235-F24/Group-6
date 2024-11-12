/*
 * Driver.c
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

int main(int argc, char **argv)
{
	 E4235_Select(26, 1); //set GPIO 26 as output
	E4235_Select(21, 0); //set GPIO 21 as input
	
	int write[1] = {26};
	int read[1] = {21};
	
	E4235_multiwrite(write, 1, 0);
	printf("Read test: %d", E4235_multiread(read, 1));

	
	/*while(1) {
		E4235_multiwrite(write, 1, 1);
		E4235_delayMicro(10000);
		E4235_multiwrite(write, 1, 0);
		E4235_delayMicro(10000);
	}*/
	return 0;
}

