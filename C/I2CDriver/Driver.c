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
#include "E4235.h"
#include <unistd.h>
#include <string.h>
#include "bcm2835.h"

static char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
static char binary[16][5]= {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
static int sda = 0;
static int scl = 0;
static int datapin[1] = {0};

int i2c_setup(int data, int clk) {
	E4235_Select(data, 1); //set pins as output
	E4235_Select(clk, 1);
	
	int pins[2] = {data, clk}; //define array for multiwrite
	
	E4235_multiwrite(pins, 2, 0);
	
	E4235_Select(data, 0); //set pins as input, ready for i2c now
	E4235_Select(clk, 0);
	
	sda = data;
	scl = clk;
	datapin[0] = data;
	
	printf("Pins successfully initialized.\nPin %d = SDA, Pin %d = SCL\n", sda, scl);
}

void i2c_send(char byte[]){
	for(int i = 0; i <= 7; i++){
		if(byte[i] == '1'){
			E4235_Select(sda, 0);	
		}else{
			E4235_Select(sda, 1);
		}
		E4235_Select(scl, 0);
		E4235_Select(scl, 1);
	}

	E4235_Select(scl, 0);
	E4235_Select(scl, 1);
}

int i2c_write(int bytes[8]){	//writing to RTC
		
	char bin[8][8];
	char swi[] = "";
	int curr;
	int state = 0;
	for(int i = 0; i <= 7; i++){	//converting decimal numbers to binary
		curr = bytes[i];
		int k = 7;					//cite geeks4geeks
		char swi[] = "00000000";
		while(curr > 0){
			if(curr%2 == 1){
				swi[k] = '1';
			}
			curr = curr/2;
			k = k-1;
		}
		strcpy(bin[i], swi);
	}
	
	E4235_Select(sda, 1);	//SDA falling edge, start condition
	E4235_Select(scl, 1);
	
	i2c_send("11010000");	//sending slave address + Write bit
	for(int i = 0; i <= 7; i++){
		i2c_send(bin[i]);
	}
	E4235_Select(sda, 1);
	E4235_Select(scl, 0); 	//SCL is high, SDA rising edge
	E4235_Select(sda, 0);	//stop condition
	printf("The write worked");
}

void i2c_read(char thing[][8]){
	E4235_Select(sda, 1);	//SDA falling edge, start condition
	E4235_Select(scl, 1);

	i2c_send("11010000");	//sending slave address + Write bit
	
	i2c_send("00000000");	//sending address bit
	
	E4235_Select(sda, 0);	//Repeated start
	E4235_Select(scl, 0);
	E4235_Select(sda, 1);
	for (int i = 0; i < 10000; i++) {
		;
	}
	E4235_Select(scl, 1);
	i2c_send("11010001"); 	//sending slave address + Read bit
	
	for(int j = 0; j <= 6; j++){ //reading 7 bytes from RTC
		char swi[9] = "";
		for(int i = 0; i <= 8; i++){	//
			if(i < 8){
				E4235_Select(scl, 0);
				int check = bcm2835_gpio_lev(sda);
				printf("check = %d\n", check);
				if(check == 0){
					swi[i] = '0';
				}
				else if(check == 1){
					swi[i] = '1';
				}
				else{
					swi[i] = 'e';
					}
				E4235_Select(scl, 1);
			}
			if(i == 8){
				strcpy(thing[j], "");
				strcpy(thing[j], swi);
				printf("swi = %s\n", thing[j]);
				if(j < 6){
					E4235_Select(sda, 1);
				}
				else{
					E4235_Select(sda, 0);
				}
				E4235_Select(scl, 0);
				E4235_Select(scl, 1);
				E4235_Select(sda, 0);
			}
		}
	}
	E4235_Select(scl, 0); 	//SCL is high, SDA rising edge
	E4235_Select(sda, 0);	//stop condition
}
