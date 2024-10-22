#include <stdio.h>
#include "bcm2835.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void sec(char input[8]){
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
void min(char input[8]){
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
void hour(char input[8]){
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
void day(char input[8]){
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
void date(char input[8]){
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
void month(char input[8]){
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
void year(char input[8]){
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
	char rec[7];
	char stored[7][2];
	char bits[7][8];
	
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char binary[16][5]= {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
	for(int i = 0; i < 32; i++){
		rec[i] = *"y";
		}
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0x68);
	bcm2835_i2c_set_baudrate(100000);
	uint8_t data = bcm2835_i2c_read(rec, 7);
	for(int i = 0; i < 7; i++){
		sprintf(stored[i], "%02x", rec[i]);
		printf("%s\n", stored[i]);
		//printf("%c\n", stored[i][1]);
	}
	
	for(int i = 0; i < 7; i++){
		char swi[] = "00000000";
		for(int k = 0; k <16; k++){
			
			if(hex[k] == stored[i][0]){
				strcpy(swi, binary[k]);
			}
		}
		for(int j = 0; j < 16; j++){
			if(hex[j] == stored[i][1]){
					strcat(swi, binary[j]);
			}
		}
		//printf("%s \n", swi);
		strcpy(bits[i], swi);
	}
	
	sec(bits[0]);
	min(bits[1]);
	hour(bits[2]);
	day(bits[3]);
	month(bits[5]);
	date(bits[4]);
	year(bits[6]);
	bcm2835_i2c_end();
	bcm2835_close();
}
