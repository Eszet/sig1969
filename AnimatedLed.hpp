#include "Lightable.hpp"

class AnimatedLed : public Lightable {
  private:
    int _pin;
    LedWiring _wiring;
    enum { idle, animateOn, animateOff } _transition;
    int _progress;
    
  public:
    AnimatedLed(int pin, LedWiring wiring);
    void turn(enum LightState state);
    bool execute();
};
