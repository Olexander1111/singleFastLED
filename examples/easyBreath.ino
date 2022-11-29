

#include "singleFastLED.h"

singleFastLED           *Fled;
singleFastLED::scLED    *Led[10];


void runWhenDone(){
  Led[0]->setColor1(10,30,30);
  Led[0]->setColor2(0,30,10);
  Led[0]->breath(1900,30,3);
}

void runWhenPauseStart(){
//your code
}

void runWhenPauseEnd(){
//your code
}

void setup() {
  
  Fled = new singleFastLED();
  Fled->begin();
  
  Led[0] = new singleFastLED::scLED(0);
  Led[1] = new singleFastLED::scLED(1);

  

  Led[0]->setColor1(10,30,30);
  Led[0]->setColor2(0,30,10);
  Led[0]->breath(1900,30,3);
  
  Led[1]->setColor1(10,50,0);
  Led[1]->setColor2(20,50,30);
  Led[1]->breath(2900,2000,10,runWhenDone);
  
}

void loop(){
  
  Led[0]->update();
  Led[1]->update();
  Fled->show();
  
}
