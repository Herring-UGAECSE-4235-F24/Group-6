/*
 * ClassLibraryTest.c
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
#include "E4235.h"


int main(int argc, char **argv)
{
	E4235_KYBdeblock(1);
	printf("Hello World from Group 6!!\n");
	printf("Testing class library.");
	
	int test = 0;
	while(test == 0) {
		scanf("%d", &test);
	}
	printf("%d", test);
}

