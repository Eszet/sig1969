#include "DigitalLed.hpp"

#include <Arduino.h>

DigitalLed::DigitalLed(int pin, LedWiring wiring)
    : _pin(pin), _levelWhenOff(wiring == CommonAnode), _levelWhenOn(wiring == CommonCathode)
{
    pinMode(_pin, OUTPUT);
    turn(LightOff);
}

void DigitalLed::turn(enum LightState state)
{
    digitalWrite(_pin, state == LightOn ? _levelWhenOn : _levelWhenOff);
}
