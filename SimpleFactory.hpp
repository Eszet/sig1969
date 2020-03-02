#pragma once

#include "LightFactory.hpp"

#include <ArduinoSTL.h>
#include <map>

class SimpleFactory : public LightFactory {
    std::map<enum LightId, Lightable *> _lights;
public:
    SimpleFactory();
    virtual ~SimpleFactory();
    virtual void mapPin(enum LightId id, int pin);
    Lightable * getLight(enum LightId id);
};
