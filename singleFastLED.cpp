#include "Arduino.h"
#include "singleFastLED.h"

enum modes_breath{INIT_BREATH,SCOPE_OF_BREATH_1,SCOPE_OF_BREATH_2,SCOPE_OF_BREATH_3,SCOPE_OF_BREATH_4,PAUSE_OF_BREATH_START,PAUSE_OF_BREATH_END,LOOP_BREATH,BREATH_COMPLETE};
enum modes_blink{INIT_BLINK,BLINK_COLOR1,BLINK_COLOR2,BLINK_REPEAT,PAUSE_OF_BLINK_START,PAUSE_OF_BLINK_END,LOOP_BLINK,BLINK_COMPLETE};


CRGB _leds[NUMBER_OF_LEDS];

bool singleFastLED::init(){
    FastLED.addLeds<WS2812, FastLED_PIN, RGB>(_leds, NUMBER_OF_LEDS);
  return true;
 }

void singleFastLED::begin(){
     init();
}

singleFastLED::SingleControl::SingleControl(uint8_t _ledId) : _ledId(_ledId){ }

void singleFastLED::SingleControl::setColor1(uint8_t green, uint8_t red, uint8_t blue){   
      _setRed   = red;
      _setGreen = green; 
      _setBlue  = blue;
}

void singleFastLED::SingleControl::setColor2(uint8_t green, uint8_t red, uint8_t blue){
      _setRed2    = red;
      _setGreen2  = green;
      _setBlue2   = blue;
}

void singleFastLED::SingleControl::blink_loop(){

  if(_blinkIsRun && !_stopBlink){
      if (millis() - _lastBlinkTime < TIME_DIFF_MS){return;}
      _lastBlinkTime = millis();
      _blinkCounter = _blinkCounter + TIME_DIFF_MS;
  
    switch (_blinkSwitch){

       case INIT_BLINK:{
                          _blinkCounter=0;
                          _blinkSwitch = BLINK_COLOR1;
                          break;
                        }
       case BLINK_COLOR1:{
                            if(_blinkCounter < _timeBlinkActionColor1){
                                _leds[_ledId].setRGB(_setRed,_setGreen,_setBlue);
                            }
                            else{
                                _blinkSwitch=BLINK_COLOR2;  
                            }
                            break;
                        }
       case BLINK_COLOR2:{
                            if(_blinkCounter < _timeBlinkActionColor1 +_timeBlinkActionColor2){
                                _leds[_ledId].setRGB(_setRed2,_setGreen2,_setBlue2);
                            }
                            else{
                                _blinkSwitch = BLINK_REPEAT;  
                            }
                            break;
                          }
       case BLINK_REPEAT:{
                            _blinkRepeatCounter++;
                            if(_blinkRepeatCounter < _blinkRepeatNum){
                                  _blinkSwitch = INIT_BLINK;
                            }
                            else{
                                _blinkSwitch = PAUSE_OF_BLINK_START;
                            }
                            break;
                          }
       case PAUSE_OF_BLINK_START:{
                            if(_blinkCounter < _timeBlinkActionColor1 +_timeBlinkActionColor2 + _pauseBlink){
                                if(!_oneTimeRunBlinkFlag){
                                      _oneTimeRunBlinkFlag = 1;
                                      if (_startBlinkPauseCallback){
                                            _startBlinkPauseCallback();
                                      }
    		                        }
                            }
                            else{
                                  _oneTimeRunBlinkFlag = 0;
                                  _blinkSwitch = PAUSE_OF_BLINK_END;
                                }
                                break;
                              }
       case PAUSE_OF_BLINK_END:{
                                if (_endBlinkPauseCallback){
                                      _endBlinkPauseCallback();
                                }
                                _blinkSwitch = LOOP_BLINK;
                                break;
                                }
       case LOOP_BLINK:{
                              _blinkCycleCounter++;
                              if(_blinkCycleCounter < _blinkCycleNum){
                                  _blinkRepeatCounter = 0;
                                  _blinkSwitch = INIT_BLINK;
                              }
                              else{
                                  _blinkSwitch = BLINK_COMPLETE;
                                  _blinkCycleCounter = 0;
                              }
                          break;
                        }
       case BLINK_COMPLETE:{
                            _blinkIsRun = 0;
                            if (_runCallbackBlink) { _runCallbackBlink(); }
                            break;
                            }
    }
  }
}

void singleFastLED::SingleControl::breath_loop(){

  if(_breathIsRun && !_stopBreath){
      if (millis() - _lastBreathTime < TIME_DIFF_MS) {return;}
      _lastBreathTime = millis();
       _breathCounter= _breathCounter+TIME_DIFF_MS;
  
    switch (_breathSwitch) {
             
         case INIT_BREATH:{
                             _breathCounter=0;
                            _breathCycleCounter=0;
                            _breathSwitch=SCOPE_OF_BREATH_1;
                            break;
                          }
         case SCOPE_OF_BREATH_1:{
                                  if ( _breathCounter < _timeBreathAction/4){          
                                      byte _j = map( _breathCounter, 0, _timeBreathAction/4, 0, 255);
                                      _leds[_ledId].setRGB(_setRed2,_setGreen2,_setBlue2);
                                      _leds[_ledId].fadeLightBy(_j);
                                  }
                                  else{
                                        _breathSwitch = SCOPE_OF_BREATH_2;
                                  }
                                break;
                              }
         case SCOPE_OF_BREATH_2:{
                                  if ( _breathCounter < _timeBreathAction/2){
                                        byte _j = map( _breathCounter, _timeBreathAction/4, _timeBreathAction/2, 255, 0);
                                        _leds[_ledId].setRGB(_setRed,_setGreen,_setBlue);
                                        _leds[_ledId].fadeLightBy(_j);
                                  }
                                  else{
                                          _breathSwitch = SCOPE_OF_BREATH_3;
                                  }
                                  break;
                                  }
         case SCOPE_OF_BREATH_3:{
                                  if ( _breathCounter < _timeBreathAction/2 + _timeBreathAction/4){                
                                          byte _j = map( _breathCounter, _timeBreathAction/2, _timeBreathAction/2 + _timeBreathAction/4 , 255, 0);  // rise level
                                        if(_j >= 245 ){_j= 255;}
                                        _leds[_ledId].setRGB(_setRed,_setGreen,_setBlue);
                                        _leds[_ledId].fadeLightBy(255-_j);
                                  }
                                  else{
                                        _breathSwitch = SCOPE_OF_BREATH_4;
                                  }
                                  break;
                                }
         case SCOPE_OF_BREATH_4:{
                                    if ( _breathCounter < _timeBreathAction){  
                                        byte _j = map( _breathCounter, _timeBreathAction/2 + _timeBreathAction/4, _timeBreathAction, 0, 255);
                                        if(_j <= 2 ){_j = 0;}
                                        if(_j >= 240 ){_j= 255;}
                                        _leds[_ledId].setRGB(_setRed2,_setGreen2,_setBlue2);
                                        _leds[_ledId].fadeLightBy(255 - _j);
                                    }
                                    else{
                                          _breathSwitch = PAUSE_OF_BREATH_START;
                                    }
                                    break;
                                }
         case PAUSE_OF_BREATH_START:{
                                  if( _breathCounter < _timeBreathAction + _pauseBreath){
                                      if(!_oneTimeRunBreathFlag){
                                        _oneTimeRunBreathFlag = 1;
                                        if (_startBreathPauseCallback){
                                              _startBreathPauseCallback(); 
                                        }
                                      }
                                  }
                                  else{
                                        _breathSwitch = PAUSE_OF_BREATH_END;
                                        _oneTimeRunBreathFlag = 0;
                                  }
                                  break;
                                  }
         case PAUSE_OF_BREATH_END:{
                                    if(_endBreathPauseCallback){
                                              _endBreathPauseCallback();
                                    }
                                    _breathSwitch = LOOP_BREATH;
                                  break;
                                  }
         case LOOP_BREATH:{

                                _breathCycleCounter++;
                                if(_breathCycleCounter < _breathCycleNum){
                                     _breathCounter=0;
                                    _breathSwitch=SCOPE_OF_BREATH_1;
                                }
                                else{
                                  _breathSwitch=BREATH_COMPLETE;
                                }
                                break;
                            }

             case BREATH_COMPLETE:{ 
                                      if (_runCallbackBreath) { _runCallbackBreath();}
                                      _breathIsRun=0;
                                      break;
                                }
        }
    }
}

void singleFastLED::SingleControl::update(){
    breath_loop();
    blink_loop();
}

void singleFastLED::show(){
    FastLED.show();
}

void singleFastLED::clear(){
    FastLED.clear();
}

void singleFastLED::SingleControl::off_all(){
    for (uint8_t i=0; i < _numLeds ;i++){
      _leds[i].setRGB(0,0,0);
    }
    FastLED.show();
}

void singleFastLED::SingleControl::off(){
    _leds[_ledId].setRGB(0,0,0);
    FastLED.show();
}

void singleFastLED::SingleControl::blink_stop(){
    _stopBlink  = true;
    _blinkIsRun = false;   
}

void singleFastLED::SingleControl::breath_stop(){
    _stopBreath   = true;
    _breathIsRun  = false;   
}

void singleFastLED::SingleControl::on_all(uint8_t green, uint8_t red, uint8_t blue){    
        _red   = red;
        _green = green; 
        _blue  = blue;
        for(uint8_t i=0; i < _numLeds ;i++){
          _leds[i].setRGB(_red,_green,_blue);
        }
       FastLED.show();  
}

void singleFastLED::SingleControl::on(uint8_t green, uint8_t red, uint8_t blue){
        _red    = red;
        _green  = green;
        _blue   = blue;  
        _leds[_ledId].setRGB(_green,_red,_blue);
       FastLED.show();
}


void singleFastLED::SingleControl::blink(
        uint16_t const timeColor1,
        uint16_t const timeColor2,
        byte     const numOfRepeat,
        uint16_t const pauseTime,
        uint16_t const numberOfCycles,
        void (*finishCallback)(),
        void (*runStartPauseCallbackBlink)(),
        void (*endPauseCallback)())
{
    _timeBlinkActionColor1 = timeColor1 ? max((int)TIME_DIFF_MS, (int)timeColor1) : 0;
    _timeBlinkActionColor2 =  timeColor2 ? max((int)TIME_DIFF_MS, (int)timeColor2) : 0;
    _blinkRepeatNum = numOfRepeat;
    _pauseBlink = pauseTime ? max((int)TIME_DIFF_MS, (int)pauseTime) : 0;
    _blinkCycleNum = numberOfCycles;
    _runCallbackBlink = finishCallback;
    _startBlinkPauseCallback = runStartPauseCallbackBlink;
    _endBlinkPauseCallback = endPauseCallback;
    _lastBlinkTime = 0;
    _oneTimeRunBlinkFlag = false;
    _stopBlink = 0;
    _blinkIsRun = 1;
    _blinkSwitch = INIT_BLINK;
}

void singleFastLED::SingleControl::blink(
  uint16_t const timeColor1,
  uint16_t const timeColor2,
  byte     const numOfRepeat,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles,
  void (*finishCallback)(),
  void (*runStartPauseCallbackBlink)())
{     
    _timeBlinkActionColor1 = timeColor1 ? max((int)TIME_DIFF_MS, (int)timeColor1) : 0;
    _timeBlinkActionColor2 =  timeColor2 ? max((int)TIME_DIFF_MS, (int)timeColor2) : 0;
    _blinkRepeatNum = numOfRepeat;
    _pauseBlink = pauseTime ? max((int)TIME_DIFF_MS, (int)pauseTime) : 0;
    _blinkCycleNum = numberOfCycles;
    _runCallbackBlink = finishCallback;
    _startBlinkPauseCallback = runStartPauseCallbackBlink;
    _endBlinkPauseCallback = NULL;
    _lastBlinkTime = 0;
    _oneTimeRunBlinkFlag = false;
    _stopBlink = 0;
    _blinkIsRun = 1;
    _blinkSwitch = INIT_BLINK;
}


void singleFastLED::SingleControl::blink(
  uint16_t const timeColor1,
  uint16_t const timeColor2,
  byte     const numOfRepeat,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles,
  void (*finishCallback)())
{
    _timeBlinkActionColor1 = timeColor1 ? max((int)TIME_DIFF_MS, (int)timeColor1) : 0;
    _timeBlinkActionColor2 =  timeColor2 ? max((int)TIME_DIFF_MS, (int)timeColor2) : 0;
    _blinkRepeatNum = numOfRepeat;
    _pauseBlink = pauseTime ? max((int)TIME_DIFF_MS, (int)pauseTime) : 0;
    _blinkCycleNum = numberOfCycles;
    _runCallbackBlink = finishCallback;
    _startBlinkPauseCallback = NULL;
    _endBlinkPauseCallback = NULL;
    _lastBlinkTime = 0;
    _oneTimeRunBlinkFlag = false;
    _stopBlink = 0;
    _blinkIsRun = 1;
    _blinkSwitch = INIT_BLINK;
}
void singleFastLED::SingleControl::blink(
  uint16_t const timeColor1,
  uint16_t const timeColor2,
  byte     const numOfRepeat,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles)
{
    _timeBlinkActionColor1 = timeColor1 ? max((int)TIME_DIFF_MS, (int)timeColor1) : 0;
    _timeBlinkActionColor2 =  timeColor2 ? max((int)TIME_DIFF_MS, (int)timeColor2) : 0;
    _blinkRepeatNum = numOfRepeat;
    _pauseBlink = pauseTime ? max((int)TIME_DIFF_MS, (int)pauseTime) : 0;
    _blinkCycleNum = numberOfCycles;
    _runCallbackBlink = NULL;
    _startBlinkPauseCallback = NULL;
    _endBlinkPauseCallback = NULL;
    _lastBlinkTime = 0;
    _oneTimeRunBlinkFlag = false;
    _stopBlink = 0;
    _blinkIsRun = 1;
    _blinkSwitch = INIT_BLINK;
}

void singleFastLED::SingleControl::breath(
  uint16_t const breathTime,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles,
  void (*runCallbackBreath)(),
  void (*runStartPauseCallbackBreath)(),
  void (*runEndPauseCallbackBreath)())
{
    _timeBreathAction = breathTime ? max((int)TIME_DIFF_MS, (int)breathTime) : 0;
    _pauseBreath = pauseTime ? max((int)TIME_DIFF_MS*4, (int)pauseTime) : 0;
    _breathCycleNum = numberOfCycles;
    _runCallbackBreath = runCallbackBreath;
    _startBreathPauseCallback = runStartPauseCallbackBreath;
    _endBreathPauseCallback = runEndPauseCallbackBreath;
    _lastBreathTime = 0;
    _oneTimeRunBreathFlag = false;
    _stopBreath = 0;
    _breathIsRun = 1;
    _breathSwitch=INIT_BREATH;
}


void singleFastLED::SingleControl::breath(
  uint16_t const breathTime,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles,
  void (*runCallbackBreath)(),
  void (*runStartPauseCallbackBreath)())
{
    _timeBreathAction = breathTime ? max((int)TIME_DIFF_MS, (int)breathTime) : 0;
    _pauseBreath = pauseTime ? max((int)TIME_DIFF_MS*4, (int)pauseTime) : 0;
    _breathCycleNum = numberOfCycles;
    _runCallbackBreath = runCallbackBreath;
    _startBreathPauseCallback = runStartPauseCallbackBreath;
    _endBreathPauseCallback = NULL;
    _lastBreathTime = 0;
    _oneTimeRunBreathFlag = false;
    _stopBreath = 0;
    _breathIsRun = 1;
    _breathSwitch=INIT_BREATH;
}

void singleFastLED::SingleControl::breath(
  uint16_t const breathTime,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles,
  void (*runCallbackBreath)())
{
    _timeBreathAction = breathTime ? max((int)TIME_DIFF_MS, (int)breathTime) : 0;
    _pauseBreath = pauseTime ? max((int)TIME_DIFF_MS*4, (int)pauseTime) : 0;
    _breathCycleNum = numberOfCycles;
    _runCallbackBreath = runCallbackBreath;
    _startBreathPauseCallback = NULL;
    _endBreathPauseCallback = NULL;     
    _lastBreathTime = 0;
    _oneTimeRunBreathFlag = false;
    _stopBreath = 0;
    _breathIsRun = 1;
    _breathSwitch=INIT_BREATH;
}

void singleFastLED::SingleControl::breath(
  uint16_t const breathTime,
  uint16_t const pauseTime,
  uint16_t const numberOfCycles)
{
    _timeBreathAction = breathTime ? max((int)TIME_DIFF_MS, (int)breathTime) : 0;
    _pauseBreath = pauseTime ? max((int)TIME_DIFF_MS*4, (int)pauseTime) : 0;
    _breathCycleNum = numberOfCycles;
    _runCallbackBreath = NULL;
    _startBreathPauseCallback = NULL;
    _endBreathPauseCallback = NULL;     
    _lastBreathTime = 0;
    _oneTimeRunBreathFlag = false;
    _stopBreath = 0;
    _breathIsRun = 1;
    _breathSwitch = INIT_BREATH;
}
