#include "SimpleFactory.hpp"
#include "DigitalLed.hpp"

#include <ArduinoSTL.h>
#include <iostream>

SimpleFactory::SimpleFactory()
{
}

SimpleFactory::~SimpleFactory()
{
    for(auto l : _lights)
    { 
        delete l.second;
    }
}

void SimpleFactory::mapPin(enum LightId id, int pin)
{
    const bool isExternal = pin != 13;
    auto wiring = isExternal ? CommonAnode : CommonCathode;
    _lights[id] = new DigitalLed(pin, wiring);
}

// Default behavior of LightFactory rather?
class NullLed : public Lightable {
public:
    void turn(enum LightState)
    {
        std::cout << "Attempt to use unmapped LED.\n";
    }
};

Lightable * SimpleFactory::getLight(enum LightId id)
{
    const bool isMapped = (_lights.find(id) != _lights.end());

    static NullLed null;
    return isMapped ? _lights[id] : &null;
}
