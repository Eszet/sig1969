#include "AnimatedLed.hpp"

#include "Arduino.h"

AnimatedLed::AnimatedLed(int pin, LedWiring wiring) :
    _pin(pin), 
    _wiring(wiring),
    _transition(idle),
    _progress(0)    
{
    pinMode(_pin, OUTPUT);
}

void AnimatedLed::turn(enum LightState state)
{
    _transition = (state == LightOn) ? animateOn : animateOff;
    _progress = 0;
}

bool AnimatedLed::execute(void)
{
  const bool busy = (_transition != idle);

  if (busy)
  {
    static const int stepsOn[] = { 30, 60, 100 };
    static const int stepsOff[] = { 100, 60, 30, 20, 15, 10, 6, 4, 3, 2, 1, 0 };
    long value;
  
    if (_transition == animateOn)
    {
      value = map(stepsOn[_progress++], 0, 100, 0, 255);
  
      if (_progress == sizeof(stepsOn)/sizeof(stepsOn[0]))
      {
        _progress = 0;
        _transition = idle;
      }
    }
    else 
    {
      value = map(stepsOff[_progress++], 0, 100, 0, 255);
  
      if (_progress == sizeof(stepsOff)/sizeof(stepsOff[0]))
      {
        _progress = 0;
        _transition = idle;
      }
    }

    if (_wiring == CommonCathode)
    {
      analogWrite(_pin, value);
    }
    else
    {
      analogWrite(_pin, 255 - value);
    }
  }
  
  return busy;
}
