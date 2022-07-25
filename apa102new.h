#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <spidev_lib.h>

#define SPI_CHANEL "/dev/spidev1.0"

struct APAColor{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t l;
  APAColor(uint8_t r,uint8_t g,uint8_t b,uint8_t l){
    this->r = r; this->g = g; this->b = b; this->l = l;
  }
  APAColor(){
    r = g = b = l = 0;
  }
};

class APA102 {        // The class
  private:
    APAColor * ledArray;
    APAColor * offArray;
    int ledCount;
    int spifd = 0;
    int speed = 20000000;


    void startFrame(){
      uint8_t buf[1];
      
      for(int i = 0; i < 4; i++) {
        buf[0] = 0x00;
        spi_write(spifd, buf, 1);
      }
    }

    void endFrame(){
      uint8_t buf[1];

      for(int i = 0; i < 4; i++) {
        buf[0] = 0xFF;
        spi_write(spifd, buf, 1);
      }
    }


  public:

    void init(int ledCount,int speed = 25000000){
      this->ledCount = ledCount;
      ledArray = new APAColor[ledCount];
      offArray = new APAColor[ledCount];

      spi_config_t spi_config;
      spi_config.mode=0;
      spi_config.speed=speed;
      spi_config.delay=0;
      spi_config.bits_per_word=8;
      spifd=spi_open((char*)SPI_CHANEL,spi_config);

    }

    void set(int number, uint8_t red, uint8_t green, uint8_t blue, uint8_t luminiscense ){
      ledArray[number].r = red;
      ledArray[number].g = green;
      ledArray[number].b = blue;
      ledArray[number].l = luminiscense;
    };

    void all( uint8_t red, uint8_t green, uint8_t blue , uint8_t luminiscense ){
      for (int i = 0; i < ledCount; ++i){
        ledArray[i].r = red;
        ledArray[i].g = green;
        ledArray[i].b = blue;
        ledArray[i].l = luminiscense;
      }
    };

    void show(){
      startFrame();
      uint8_t led_frame[4];
      for(int i = 0; i < ledCount; i++) {
        led_frame[0] = 0b11100000 | (0b00011111 & ledArray[i].l);
        led_frame[1] = ledArray[i].b;
        led_frame[2] = ledArray[i].g;
        led_frame[3] = ledArray[i].r;

        spi_write(spifd, led_frame, 4);
      }
      endFrame();
    };

    void end(){
      //spi_close(spifd);   // i dont know if its nesesary close on end of transmition
    }

};