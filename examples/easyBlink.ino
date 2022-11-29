
#include "singleFastLED.h"

singleFastLED           *Fled;
singleFastLED::scLED    *Led[10];


void runWhenFinish(){
//run your code
}

void whenPauseStart(){
//run your code
}

void whenPauseEnd(){
//run your code
}

void setup() {
  
  Fled = new singleFastLED();
  Fled->begin();
  
  Led[0] = new singleFastLED::scLED(0);
  
  /* Breath effect
  Led[0]->setColor1(0,50,30);
  Led[0]->setColor2(0,50,30);
  Led[0]->breath(1900,390,10);
  */
  
  /*Blink effect*/
  
  Led[3]->setColor1(20,0,0);
  Led[3]->setColor2(0,0,0);
  //Led[3]->blink(30,70,3,1800,10,runWhenFinish, whenPauseStart, whenPauseEnd); //more complex option
  Led[3]->blink(100,100,5,1000,100);
  
}

void loop(){
  
  Led[0]->update();
  Fled->show();
  
}
