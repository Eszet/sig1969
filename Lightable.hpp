#pragma once

enum LightState { LightOff, LightOn };

enum LedWiring { CommonAnode, CommonCathode };

struct Lightable {
    virtual void turn(enum LightState) = 0;
    virtual bool execute(void) = 0;
};
