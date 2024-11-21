#include <stdio.h>
#include "E4235.h"
#include <unistd.h>
#include <string.h>

static int sda = 0;		//data pin
static int scl = 0;		//clk pin

int i2c_setup(int data, int clk) {	//should be run on startup. configures the pins and leaves them floating
	E4235_Select(data, 1); //set pins as output
	E4235_Select(clk, 1);
	
	int pins[2] = {data, clk}; //define array for multiwrite
	
	E4235_multiwrite(pins, 2, 0);
	
	E4235_Select(data, 0); //set pins as input, ready for i2c now
	E4235_Select(clk, 0);
	
	sda = data;		//assigning pin values
	scl = clk;
	
	printf("Pins successfully initialized.\nPin %d = SDA, Pin %d = SCL\n", sda, scl);
}

void i2c_send(char byte[]){		//sends a byte to the RTC using a string
	for(int i = 0; i <= 7; i++){	//looks through each bit
		if(byte[i] == '1'){
			E4235_Select(sda, 0);	//if the bit is 1, set data high
		}else{
			E4235_Select(sda, 1);	//if the bit is 0, set data low
		}
		E4235_Select(scl, 0);		//toggle clock for next bit
		E4235_Select(scl, 1);
	}

	E4235_Select(scl, 0);			//toggle clock for acknowledge bit
	E4235_Select(scl, 1);
}

int i2c_write(char address[8], int bytes[8]){	//writing to RTC. first parameter is starting address
		
	char bin[8][8];		//array of strings that will be written to RTC
	char swi[] = "";	//current string that will be added to bin
	int curr;			//current bit
	
	for(int i = 0; i <= 7; i++){	//converting decimal numbers to binary
		curr = bytes[i];			//converts the ints inputted into strings of 1s and 0s
		int k = 7;					
		char swi[] = "00000000";	
		while(curr > 0){			//binary conversion code adapted from geeks4geeks
			if(curr%2 == 1){		//geeksforgeeks.org/program-decimal-binary-conversion
				swi[k] = '1';
			}
			curr = curr/2;
			k = k-1;
		}
		strcpy(bin[i], swi);		//copy into array
	}
	strcpy(bin[0], address);	//copying address into first byte
	E4235_Select(sda, 1);	//SDA falling edge, start condition
	E4235_Select(scl, 1);
	
	i2c_send("11010000");	//sending slave address + Write bit
	for(int i = 0; i <= 7; i++){	
		i2c_send(bin[i]);	//writing each byte to RTC
	}
	E4235_Select(sda, 1);	//setting data high for stop
	E4235_Select(scl, 0); 	//SCL is high, SDA rising edge
	E4235_Select(sda, 0);	//stop condition
}

void i2c_read(char address[8], char thing[][8]){	//reading from RTC and storing result in array. first parameter is starting address
	E4235_Select(sda, 1);	//SDA falling edge, start condition
	E4235_Select(scl, 1);

	i2c_send("11010000");	//sending slave address + Write bit
	
	i2c_send(address);	//sending address byte. read will start from here
	
	E4235_Select(sda, 0);	//Repeated start for read mode
	E4235_Select(scl, 0);
	E4235_Select(sda, 1);
	for (int i = 0; i < 10000; i++) {	//Delay needed for RTC to handle clock and data
		;
	}
	E4235_Select(scl, 1);
	i2c_send("11010001"); 	//sending slave address + Read bit
	
	for(int j = 0; j <= 6; j++){ //reading 7 bytes from RTC
		char swi[9] = "";		//string for current byte
		for(int i = 0; i <= 8; i++){	
			if(i < 8){					//reading current byte
				E4235_Select(scl, 0);	//setting clock to high
				int check = E4235_Read(sda);	//reading data set by RTC
				if(check == 0){			//reading each bit
					swi[i] = '0';
				}
				else if(check == 1){
					swi[i] = '1';
				}
				E4235_Select(scl, 1);	//setting clock to low for next byte
			}
			if(i == 8){					//byte has been read
				strcpy(thing[j], "");	
				strcpy(thing[j], swi);
				if(j < 6){				//before final byte, data is low for ACK
					E4235_Select(sda, 1);
				}
				else{					//otherwise, data is high for NACK
					E4235_Select(sda, 0);
				}
				E4235_Select(scl, 0);	//toggle clock to end ACK/NACK
				E4235_Select(scl, 1);	
				E4235_Select(sda, 0);	//setting data to input to read byte
			}
		}
	}
	E4235_Select(sda, 1);	//setting data high for stop
	E4235_Select(scl, 0); 	//SCL is high, SDA rising edge
	E4235_Select(sda, 0);	//stop condition
}
