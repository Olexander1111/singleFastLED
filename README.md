# singleFastLED


Simplified implementation of independent FastLED Leds(WS2812) control for microcontrollers (Arduino,ESP8266/ESP32).

## How to use

Change the settings for the FastLED lib in singleFastLED.h file.

```C++
#define NUMBER_OF_LEDS 8
#define FastLED_PIN 16
```
Include the header file on your code:

```C++
#include "singleFastLED.h"
```


Then create the FastLED objects according to your needs, examples:

```C++
singleFastLED           *Fled;
singleFastLED::scLED    *Led[8];     //8 - the number of LEDs you want to control
```
In the setup function, initialize the FastLED Lib and virtual LEDs

```C++
void setup() {

  Fled = new singleFastLED();
  Fled->begin();

  Led[0] = new singleFastLED::scLED(0);
  Led[1] = new singleFastLED::scLED(1);
  .....
  .....
  Led[5] = new singleFastLED::scLED(5);
```
Now you can use the singleFastLED functions for a specific LED
```C++
  Led[0]->setColor1(0,30,30);
  Led[0]->setColor2(30,30,0);
  Led[0]->blink(100,150,3,2000,10);
}  
  
```
Don't forget to add an update function in the loop for a specific LED
```C+
void loop(){

Led[0]->update();
....
Led[5]->update();
Fled->show();
}  
```
## Finally use the following functions:
```C++
on(uint8_t green, uint8_t red, uint8_t blue);
  Example:  Led[0]->on(10,2,45);

off();
  Example:  Led[0]->off();
  
setColor1(uint8_t green, uint8_t red, uint8_t blue);
  Example:  Led[0]->setColor1(50,0,0);    //Green
  
setColor2(uint8_t green, uint8_t red, uint8_t blue);
  Example:  Led[0]->setColor2(5,5,5);     //White
  
blink(uint16_t timeColor1, uint16_t timeColor2, byte numOfRepeat, uint16_t pauseTime, uint16_t numberOfCycles);  
  Example:  
        Led[0]->setColor1(0,0,50);        //Blue
        Led[0]->setColor2(0,50,0);        //Red
        Led[0]->blink(100,150,3,2000,10); // Blue fires for 100ms, Red fires for 150ms, repeats 3 times, waits 2000ms and repeats all 10 times

breath(uint16_t actionTime, uint16_t pauseTime, uint16_t numberOfCycles);
  Example:  
        Led[0]->setColor1(0,0,50);      //Blue
        Led[0]->setColor2(0,50,0);      //Red
        Led[0]->breath(1500,1000,10);   //Blue "breath in" for 1500/4 ms, Red "breath out" for 1500/4 ms, Red "breath in" for 1500/4 ms, Blue "breath out" for 1500/4 ms, waits 1000ms and repeats all 10 times

blink_stop();
    Example:  
        Led[0]->blink_stop();       // Stop blinking     

breath_stop();
    Example:  
        Led[0]->breath_stop();      // Stop breath action     
```
