# singleFastLED


Simplified implementation of independent FastLED Leds control for microcontrollers ESP8266/ESP32.

## How to use

Include the header file on your code:

```C++
#include "singleFastLED.h"
```
Then create the FastLED objects according to your needs, examples:

```C++
singleFastLED           *Fled;
singleFastLED::scLED    *Led[10];     //10 - the number of LEDs you want to control
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

Now you can use the singleFastLED functions for a specific LED

  Led[0]->setColor1(10,20,30);
  Led[0]->setColor2(10,20,30);
  Led[0]->blink(1900,90,1800);
  
  Led[1]->on(10,2,45);    
  
}  



void loop(){

Led[0]->update();
Fled->show();
}  
  
```

You can use also the following functions to get more complex control:
