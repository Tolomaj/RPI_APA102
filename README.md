# RPI_APA102
Small c++ library to control APA102 smart leds from Raspbery Pi. (tested on Raspbery Pi 4)

Default SPI chanel is 1 (/dev/spidev1.0). You can change it in library file on line 6.
>#define SPI_CHANEL "/dev/spidev1.0"


Funkctions:

```
void init(ledCount,speed);

void set(int number, uint8_t red, uint8_t green, uint8_t blue, uint8_t luminiscense );

void all( uint8_t red, uint8_t green, uint8_t blue , uint8_t luminiscense );

void show();
```


Example:
```
#include "apa102.h"

#define LED_COUNT 61
APA102 leds;


int main(){
   leds.init(LED_COUNT,1);
   
   leds.all(255,0,0,255); // sets all leds to red
   
	 for (int i = 0; i < LED_COUNT/2; ++i){ // sets halp leds to blue
      leds.set(i,0,0,255,255);
	  }
	  leds.show();  // send changes to leds
		
    return 0;
}
```
