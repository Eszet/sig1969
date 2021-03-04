#include "SimpleFactory.hpp"
#include "DigitalLed.hpp"
#include "AnimatedLed.hpp"

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

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixel(1, 40, NEO_GRB + NEO_KHZ800);

class NeoPixel : public Lightable {
  private:
    enum { idle, animateOn, animateOff } transition;
    int progress;
    
  public:
    NeoPixel()
    {
      transition = idle;
      progress = 0;
      pixel.begin();
      pixel.clear();
    }

    void turn(enum LightState state)
    {
      const auto white = pixel.Color(50, 50, 50);
      const auto black = pixel.Color(0, 0, 0);
      const auto color = (state == LightOn) ? white : black;
      pixel.setPixelColor(0, color);
      pixel.show();
    }

    bool execute() 
    { 
      return false;
    }
};

void SimpleFactory::mapPin(enum LightId id, int pin)
{
    const bool isExternal = pin != 13;
    auto wiring = isExternal ? CommonAnode : CommonCathode;
    if(pin == 40)
        _lights[id] = new NeoPixel();
    else {
      //if(pin == 3) {
        _lights[id] = new AnimatedLed(pin, wiring);
      //} else {
      //  _lights[id] = new DigitalLed(pin, wiring);
      //}      
    }
}

// Default behavior of LightFactory rather?
class NullLed : public Lightable {
public:
    void turn(enum LightState)
    {
        std::cout << "Attempt to use unmapped LED.\n";
    }

    bool execute() { return false; }
};

Lightable * SimpleFactory::getLight(enum LightId id)
{
    const bool isMapped = (_lights.find(id) != _lights.end());

    static NullLed null;
    return isMapped ? _lights[id] : &null;
}
