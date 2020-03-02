#pragma once

enum LightState { LightOff, LightOn };

struct Lightable {
    virtual void turn(enum LightState) = 0;
};
