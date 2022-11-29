

#include "singleFastLED.h"

singleFastLED           *Fled;
singleFastLED::scLED    *Led[10];


void runWhenDone(){
  Led[0]->setColor1(10,3,30);
  Led[0]->setColor2(0,30,0);
  Led[0]->breath(1900,30,3);
}

void runWhenPauseStart(){
  Led[0]->setColor1(10,3,30);
  Led[0]->setColor2(0,30,0);
  Led[0]->breath(900,0,1);
}

void runWhenPauseEnd(){
  Led[0]->setColor1(10,3,30);
  Led[0]->setColor2(0,30,0);
  Led[0]->breath(400,0,2);
}

void setup() {
  
  Fled = new singleFastLED();
  Fled->begin();
  
  Led[0] = new singleFastLED::scLED(0);
  Led[1] = new singleFastLED::scLED(1);

  

  Led[0]->setColor1(10,30,30);
  Led[0]->setColor2(0,30,10);
  Led[0]->breath(1900,30,3);
  
  Led[1]->setColor1(10,0,20);
  Led[1]->setColor2(0,50,30);
  Led[1]->breath(1400,2300,10,runWhenDone,runWhenPauseStart,runWhenPauseEnd);
  
}

void loop(){
  
  Led[0]->update();
  Led[1]->update();
  Fled->show();
  
}
