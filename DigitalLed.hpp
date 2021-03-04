#pragma once

#include "Lightable.hpp"

class DigitalLed : public Lightable {
    const int _levelWhenOn; 
    const int _levelWhenOff;
    int _pin;
public:
    DigitalLed(int pin, LedWiring wiring = CommonAnode);
    void turn(enum LightState state);
    bool execute(void);
};
