//THIS FILE IS USED TO WRITE TO THE RTC.
#include <stdio.h>
#include "bcm2835.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
int main(int argc, char **argv)
{
	if (!bcm2835_init()){  //initializing library
      return 1;
     }
    char bytes[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};	//Array holding bytes that will be written into RTC
    char fulltime[50];	//Buffer holding the entire time output from the time library
    char weeks[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};	/Arrays with weeks and months
    char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
    int weeknum = 0;	//Values that will represent each number in decimal. Will later be converted to hex and sent to RTC
    int monthnum = 0;
    int daynum = 0;
    int hournum = 0;
    int minnum = 0;
    int secnum = 0;
    int yearnum = 0;
    time_t mytime;	//Using time library to read system clock on the Pi
    mytime = time(NULL);
    printf(ctime(&mytime));	//Printing time to terminal for debugging purposes
    char week[3];	//These arrays will be used to create "substrings" of the time lib output
    char month[3];
    char day[2];
    char hour[2];
    char min[2];
    char sec[2];
    char year[4];
    strcpy(fulltime, ctime(&mytime));	//Copying time library output into fulltime
    strncpy(week, fulltime, 3);		//Copying each part of fulltime into the corresponding arrays
    strncpy(month, fulltime+4, 3);
    for(int i = 0; i < 7; i++){
		if(strcmp(week, weeks[i]) == 0){
			weeknum = i + 1;
		}
	}				//For the strings in fulltime (month and day of week), looking through the arrays 
	for(int i = 0; i < 12; i++){	//and assigning a number to weeknum and monthnum
		if(strcmp(month, months[i]) == 0){
			monthnum = i + 1;
		}
	}
    strncpy(day, fulltime+8, 2);	//Continuing to break fulltime into substrings
    strncpy(hour, fulltime+11, 2);
    strncpy(min, fulltime+14, 2);
    strncpy(sec, fulltime+17, 2);
    strncpy(year, fulltime+22, 2);
    daynum = strtol(day, (char**)NULL, 10);	//Converting the remaining strings into integers
    hournum = strtol(hour, (char**)NULL, 10);
    minnum = strtol(min, (char**)NULL, 10);
    secnum = strtol(sec, (char**)NULL, 10);
    yearnum = strtol(year, (char**)NULL, 10);
    
    if(secnum >= 40){		//These if statements use the previously found integers to 
		secnum -= 40;	//"encode" into bytes, in accordance with the RTC datasheet
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
	
    bcm2835_i2c_begin();		Starting I2C protocol, writing the encoded bytes to the RTC, and ending I2C
	bcm2835_i2c_setSlaveAddress(0x68);
	bcm2835_i2c_set_baudrate(100000);
	bcm2835_i2c_write(bytes, 8);
	bcm2835_i2c_end();
	bcm2835_close();
}

