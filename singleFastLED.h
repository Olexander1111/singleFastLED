
#pragma once
#include "Arduino.h"

#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_INTERRUPT_RETRY_COUNT 1
#include <FastLED.h>

#define TIME_DIFF_MS 15
#define NUMBER_OF_LEDS 8
#define FastLED_PIN D0


class singleFastLED {

   class SingleControl
                    {
        public:
                  SingleControl(uint8_t _ledId);
                  ~SingleControl();

                  void breath(uint16_t actionTime, uint16_t pauseTime,
		              uint16_t numberOfCycles, void (*finishCallback)(),
		              void (*startPauseCallback)(),
		              void (*endPauseCallback)());
                  void breath(uint16_t actionTime, uint16_t pauseTime,
		              uint16_t numberOfCycles, void (*finishCallback)(),
		              void (*startPauseCallback)());
                  void breath(uint16_t actionTime, uint16_t pauseTime,
		              uint16_t numberOfCycles, void (*finishCallback)());
                  void breath(uint16_t actionTime, uint16_t pauseTime,
		              uint16_t numberOfCycles);

                  void blink(uint16_t const timeColor1,uint16_t const timeColor2,
		              byte const numOfRepeat,uint16_t const pauseTime,
		              uint16_t const numberOfCycles, void (*finishCallback)(),
		              void (*startPauseCallback)(),
		              void (*endPauseCallback)());
                  void blink(uint16_t const timeColor1,uint16_t const timeColor2,
		              byte const numOfRepeat,uint16_t const pauseTime,
		              uint16_t const numberOfCycles, void (*finishCallback)(),
		              void (*startPauseCallback)());
                  void blink(uint16_t const timeColor1,uint16_t const timeColor2,
		              byte const numOfRepeat,uint16_t const pauseTime,
		              uint16_t const numberOfCycles, void (*finishCallback)());
                  void blink(uint16_t const timeColor1,uint16_t const timeColor2,
		              byte const numOfRepeat,uint16_t const pauseTime,
		              uint16_t const numberOfCycles);
                  
                  void setColor1(uint8_t green, uint8_t red, uint8_t blue);
                  void setColor2(uint8_t green, uint8_t red, uint8_t blue);        
                  void on(uint8_t green, uint8_t red, uint8_t blue);
                  void on_all(uint8_t green, uint8_t red, uint8_t blue);
                  void off_all();
                  void off();
                  void stop();
                  void update();
                  void blink_loop();
                  void breath_loop();

        private:
                  bool          _breathIsRun;
                  bool          _stopBreath;
                  bool          _oneTimeRunBreathFlag;
                  uint8_t       _breathSwitch;
                  uint16_t      _timeBreathAction;
                  uint16_t      _pauseBreath;
                  uint16_t      _breathCounter,_breathCycleNum,_breathCycleCounter;
                  unsigned long _lastBreathTime;
                  void          (*_startBreathPauseCallback)();
                  void          (*_endBreathPauseCallback)();
                  void          (*_runCallbackBreath)();

                  bool          _blinkIsRun;
                  bool          _stopBlink;
                  bool          _oneTimeRunBlinkFlag;
                  uint8_t       _blinkSwitch;
                  uint16_t      _timeBlinkActionColor1;
                  uint16_t      _timeBlinkActionColor2;
                  uint16_t      _pauseBlink;
                  uint16_t      _blinkCounter,_blinkCycleNum,_blinkCycleCounter,_blinkRepeatCounter,_blinkRepeatNum;
                  unsigned long _lastBlinkTime;
                  void          (*_startBlinkPauseCallback)();
                  void          (*_endBlinkPauseCallback)();
                  void          (*_runCallbackBlink)();

                  uint8_t       _setRed, _setGreen, _setBlue;
                  uint8_t       _setRed2, _setGreen2, _setBlue2;
                  uint8_t       _red, _green, _blue;           
                  uint8_t       _ledId;                  
                  uint16_t      _numLeds = NUMBER_OF_LEDS; };

public:

  typedef SingleControl scLED;
  singleFastLED(){};
  ~singleFastLED();

  virtual void begin();
  virtual bool init();
  virtual void show();
  virtual void clear();

private:
  byte    _dataPin;
  uint8_t _numLeds;
};
