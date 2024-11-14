/*
 * I2C.c
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

#include "Driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void sec(char input[8]){	//Read and print seconds. Each bit adds in accordance with the RTC datasheet
	int result = 0;
	if (input[1] == '1'){
		result += 40;
	} if (input[2] == '1') {
		result += 20;
	} if (input[3] == '1') {
		result += 10;
	} if (input[4] == '1') {
		result += 8;
	} if (input[5] == '1') {
		result += 4;
	} if (input[6] == '1') {
		result += 2;
	} if (input[7] == '1') {
		result += 1;
	}
	printf("Seconds: %d \n", result);
}
void min(char input[8]){	//Read and print minutes
	int result = 0;
	if (input[1] == '1'){
		result += 40;
	} if (input[2] == '1') {
		result += 20;
	} if (input[3] == '1') {
		result += 10;
	} if (input[4] == '1') {
		result += 8;
	} if (input[5] == '1') {
		result += 4;
	} if (input[6] == '1') {
		result += 2;
	} if (input[7] == '1') {
		result += 1;
	}
	printf("Minutes: %d \n", result);
}
void hour(char input[8]){	//Read and print hours. Handles the 12/24 hour clock and the AM/PM bit
	int result = 0;
	int am = 0;
	if (input[4] == '1') {
		result += 8;
	} if (input[5] == '1') {
		result += 4;
	} if (input[6] == '1') {
		result += 2;
	} if (input[7] == '1') {
		result += 1;
	}
	if (input[3] == '1') {
		result += 10;
	}
	if (input[1] == '1') {
		if (input[2] == '1') {
			am = 2;
		}else{
			am = 1;
			}
	} else if (input[2] == '1') {
		am = 0;
		result += 20;
	}
	if(am == 1){
		printf("Hours: %d am \n", result);
		}
	else if(am == 2){ 
		printf("Hours: %d pm \n", result);
		}
	else if(am == 0){
		printf("Hours: %d \n", result);
		}
}
void day(char input[8]){	//Read and print day of the week
	int result = 0;
	if (input[5] == '1') {
		result += 4;
	} if (input[6] == '1') {
		result += 2;
	} if (input[7] == '1') {
		result += 1;
	}
	result = result - 1;
	if(result == -1 || result > 6){
		printf("Day: invalid \n");
		return;
	}
	char week[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
	printf("Day: %s \n", week[result]);
}
void date(char input[8]){	//Read and print day of the month
	int result = 0;
	if (input[2] == '1') {
		result += 20;
	}
	if (input[3] == '1') {
		result += 10;
	} 
	if (input[4] == '1') {
		result += 8;
	}
	if (input[5] == '1') {
		result += 4;
	} 
	if (input[6] == '1') {
		result += 2;
	} 
	if (input[7] == '1') {
		result += 1;
	}
	printf("%d/", result);
}
void month(char input[8]){	//Read and print month
	int result = 0;
	
	if (input[0] == '1') {
		result += 0;
	}
	if (input[3] == '1') {
		result += 10;
	} 
	if (input[4] == '1') {
		result += 8;
	} 
	if (input[5] == '1') {
		result += 4;
	} 
	if (input[6] == '1') {
		result += 2;
	} 
	if (input[7] == '1') {
		result += 1;
	}
	printf("Date: %d/", result);
}
void year(char input[8]){	//Read and print year
	int result = 0;
	if (input[0] == '1'){
		result += 80;
	} if (input[1] == '1'){
		result += 40;
	} if (input[2] == '1') {
		result += 20;
	} if (input[3] == '1') {
		result += 10;
	} if (input[4] == '1') {
		result += 8;
	} if (input[5] == '1') {
		result += 4;
	} if (input[6] == '1') {
		result += 2;
	} if (input[7] == '1') {
		result += 1;
	}
	printf("%d", result);
}

int main(int argc, char **argv)
{
	int choice = 0;
	printf("Enter 0 to read and 1 to write: ");
	scanf("%d", &choice);
	if(choice > 1 | choice < 0){
		choice = 0;
	}
	if(choice == 0){
			char rec[7];	//Buffer that the RTC will read into
			char stored[7][2];	//After reading, each byte is converted into 2 hex characters
			char bits[7][8];	//These hex chars are then converted into 8 bit binary strings
			char cmds[2] = {0x0, 0x0};

			//Arrays that are used to convert the data first into hex and then binary
			char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
			char binary[16][5]= {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
			for(int i = 0; i < 32; i++){
				rec[i] = *"y";
				}
			
			
			for(int i = 0; i < 7; i++){
				sprintf(stored[i], "%02x", rec[i]);	//Converting the bytes into hex chars and storing into an array
			}
			
			for(int i = 0; i < 7; i++){
				char swi[] = "00000000";
				for(int k = 0; k <16; k++){
					if(hex[k] == stored[i][0]){
						strcpy(swi, binary[k]);		//For each hex char, add the corresponding binary values to a string
					}
				}
				for(int j = 0; j < 16; j++){
					if(hex[j] == stored[i][1]){
						strcat(swi, binary[j]);		//Adding the next 4 binary values to the string
					}
				}
				strcpy(bits[i], swi);	//Copying the string into the bits array
			}
			
			sec(bits[0]);		//Calling each method with the corresponding binary values
			min(bits[1]);		//They will process the bits to match the RTC datasheet
			hour(bits[2]);		//The methods are called in this order to print the time in a readable manner
			day(bits[3]);
			month(bits[5]);
			date(bits[4]);
			year(bits[6]);
		}
	else if(choice == 1){
		i2c_setup(21, 26);
		char bytes[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};	//Array holding bytes that will be written into RTC
		int weeknum = 0;	//Values that will represent each number in decimal. Will later be converted to hex and sent to RTC
		int monthnum = 0;
		int daynum = 0;
		int hournum = 0;
		int minnum = 0;
		int secnum = 0;
		int yearnum = 0;
		/*printf("Enter the current Month (1-12): ");
		scanf("%d", &monthnum);
		printf("Enter the current Weekday (1-7): ");
		scanf("%d", &weeknum);
		printf("Enter the current Day (1-31): ");
		scanf("%d", &daynum);
		printf("Enter the current Hour (1-24): ");
		scanf("%d", &hournum);
		printf("Enter the current Minutes (0-59): ");
		scanf("%d", &minnum);
		printf("Enter the current Seconds (0-59): ");
		scanf("%d", &secnum);
		printf("Enter the last two digits of the current Year (0-99): ");
		scanf("%d", &yearnum);
		int vals[8] = {0, secnum, minnum, hournum, weeknum, daynum, monthnum, yearnum};*/
		int vals[8] = {0, 192, 192, 20, 3, 20, 10, 98};
		i2c_write(vals);
	}
	return 0;
}

