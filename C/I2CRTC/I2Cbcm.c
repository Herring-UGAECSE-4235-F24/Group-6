//THIS FILE IS USED TO READ FROM THE RTC AND PRINT THE TIME TO THE TERMINAL

#include <stdio.h>
#include "bcm2835.h"
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
	
	if (!bcm2835_init()){  //initializing library
      return 1;
     }
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
	bcm2835_i2c_begin();	//Initializing i2c protocol
	bcm2835_i2c_setSlaveAddress(0x68);	
	bcm2835_i2c_set_baudrate(100000);
	bcm2835_i2c_write_read_rs(cmds, 1, rec, 7);
	
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
	bcm2835_i2c_end();
	bcm2835_close();
}
