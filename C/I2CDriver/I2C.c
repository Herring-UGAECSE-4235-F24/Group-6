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
#include "bcm2835.h"

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
	printf("%d\n", result);
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
			i2c_setup(21, 26);
			char bits[7][8];	//These hex chars are then converted into 8 bit binary strings
			i2c_read("00000000", bits);		//Calling read, output will be put into the bits array
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
		int output[8];		//Array of ints that will be passed into the driver
		int weeknum = 0;	//Values that will represent each number in decimal. Will later be converted to hex and sent to RTC
		int monthnum = 0;
		int daynum = 0;
		int hournum = 0;
		int minnum = 0;
		int secnum = 0;
		int yearnum = 0;
		printf("Enter the current Month (1-12): ");		//Scanning user input and saving into the ints
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
		int vals[8] = {0, secnum, minnum, hournum, weeknum, daynum, monthnum, yearnum};
		
		if(secnum >= 40){		//These if statements "encode" the scanned integers 
			secnum -= 40;		//into bytes, in accordance with the RTC datasheet
			bytes[1] += 0x40;
		} if(secnum >= 20){
			secnum -= 20;
			bytes[1] += 0x20;
		} if(secnum >= 10){
			secnum -= 10;
			bytes[1] += 0x10;
		} if(secnum >= 8){
			secnum -= 8;
			bytes[1] += 0x8;
		} if(secnum >= 4){
			secnum -= 4;
			bytes[1] += 0x4;
		} if(secnum >= 2){
			secnum -= 2;
			bytes[1] += 0x2;
		} if(secnum >= 1){
			secnum -= 1;
			bytes[1] += 0x1;
		} 
		
		if(minnum >= 40){	//Encoding minutes
			minnum -= 40;
			bytes[2] += 0x40;
		} if(minnum >= 20){
			minnum -= 20;
			bytes[2] += 0x20;
		} if(minnum >= 10){
			minnum -= 10;
			bytes[2] += 0x10;
		} if(minnum >= 8){
			minnum -= 8;
			bytes[2] += 0x8;
		} if(minnum >= 4){
			minnum -= 4;
			bytes[2] += 0x4;
		} if(minnum >= 2){
			minnum -= 2;
			bytes[2] += 0x2;
		} if(minnum >= 1){
			minnum -= 1;
			bytes[2] += 0x1;
		}
			
		if(hournum >= 20){	//Encoding hours
			hournum -= 20;
			bytes[3] += 0x20;
		} if(hournum >= 10) {
			hournum -=10;	
			bytes[3] += 0x10;
		} if(hournum >= 8) {
			hournum -=8;	
			bytes[3] += 0x8;
		} if(hournum >= 4) {
			hournum -=4;	
			bytes[3] += 0x4;
		} if(hournum >= 2) {
			hournum -=2;	
			bytes[3] += 0x2;
		} if(hournum >= 1) {
			hournum -=1;	
			bytes[3] += 0x1;
		}
		
		if(weeknum >= 4){	//Encoding day of week
			weeknum -= 4;
			bytes[4] += 0x4;
		} if (weeknum >= 2) {
			weeknum -= 2;
			bytes[4] += 0x2;
		} if (weeknum >= 1) {
			weeknum -= 1;
			bytes[4] += 0x1;
		}
		
		if(daynum >= 20){	//Encoding date of month
			daynum -= 20;
			bytes[5] += 0x20;
		} if(daynum >= 10) {
			daynum -=10;	
			bytes[5] += 0x10;
		} if(daynum >= 8) {
			daynum -=8;	
			bytes[5] += 0x8;
		} if(daynum >= 4) {
			daynum -=4;	
			bytes[5] += 0x4;
		} if(daynum >= 2) {
			daynum -=2;	
			bytes[5] += 0x2;
		} if(daynum >= 1) {
			daynum -=1;	
			bytes[5] += 0x1;
		}
		
		if(monthnum >= 10) {	//Encoding month
			monthnum -=10;	
			bytes[6] += 0x10;
		} if(monthnum >= 8) {
			monthnum -=8;	
			bytes[6] += 0x8;
		} if(monthnum >= 4) {
			monthnum -=4;	
			bytes[6] += 0x4;
		} if(monthnum >= 2) {
			monthnum -=2;	
			bytes[6] += 0x2;
		} if(monthnum >= 1) {
			monthnum -=1;	
			bytes[6] += 0x1;
		}
		
		if(yearnum >= 80) {	//Encoding year
			yearnum -= 80;
			bytes[7] += 0x80;
		} if(yearnum >= 40){
			yearnum -= 40;
			bytes[7] += 0x40;
		} if(yearnum >= 20){
			yearnum -= 20;
			bytes[7] += 0x20;
		} if(yearnum >= 10){
			yearnum -= 10;
			bytes[7] += 0x10;
		} if(yearnum >= 8){
			yearnum -= 8;
			bytes[7] += 0x8;
		} if(yearnum >= 4){
			yearnum -= 4;
			bytes[7] += 0x4;
		} if(yearnum >= 2){
			yearnum -= 2;
			bytes[7] += 0x2;
		} if(yearnum >= 1){
			yearnum -= 1;
			bytes[7] += 0x1;
		}
		for(int i = 0; i < 8; i++){
				output[i] = (int)bytes[i];	//converting chars into ints for the driver
		}
		i2c_write("00000000", output);
	}
	return 0;
}

