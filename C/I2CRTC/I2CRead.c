
#include <stdio.h>
#include "bcm2835.h"

void scl(){
		bcm2835_delay(250);
		bcm2835_gpio_write(3, HIGH);
		bcm2835_delay(250);
		bcm2835_gpio_write(3, LOW);
	} 
void sendnums(char output[8]) { //outputs to the logic analyzer
	for(int o = 0; o < 8; o++) {
		if(output[o] == '1') {
			bcm2835_gpio_write(2, HIGH);
		} else {
			bcm2835_gpio_write(2, LOW);
		}
		scl();
		printf("%c\n", output[o]);
	}
}
int main(int argc, char **argv)
{
	if (!bcm2835_init())  //initializing library
      return 1;
      
     
     
     bcm2835_gpio_fsel(2, BCM2835_GPIO_FSEL_OUTP);
     bcm2835_gpio_fsel(3, BCM2835_GPIO_FSEL_OUTP);
     bcm2835_gpio_write(2, HIGH);
     bcm2835_gpio_write(3, HIGH);
     
     //i2c start
     bcm2835_gpio_write(2, LOW);
     scl()
     sendnums("11010001");
	scl()
	if(bcm2835_gpio_lev(2) == 0) {
		return 0;
	}
	while(1 == 1){
		}	
}

