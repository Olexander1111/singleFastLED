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
singleFastLED::scLED    *Led[10];
```
