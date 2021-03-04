#include "ArduinoLights.hpp"
#include "CommonSignal.hpp"

#include "Chrono.h" // install Chrono lib
//#include "TimerOne.h" // install TimerOne lib

#include <ArduinoSTL.h>
#include <vector>
#include <iostream>

#include <AceButton.h>
using namespace ace_button;

AceButton button[3];
void handleEvent(AceButton*, uint8_t, uint8_t);

FeatherLights o;
DepartureSignal s(o);
//DistantSignal t(o);

void timeout()
{
  const std::vector<SignalAspect> demo { Hp0, Hp1, Hp2, Hp0_Sh1  };
  static auto it = demo.begin();
  static Chrono c, d;

  if (d.hasPassed(25))
  {
      if (s.execute())
      {
        d.restart();
      } else {
        if(c.hasPassed(1000))
        {
          c.restart();
          s.apply(it != demo.end() ? *it : * (it = demo.begin()));
          ++it;
        }
      }
  }
}

#include <map>

std::map<int, SignalAspect> inputMap;

void handleEvent(AceButton* button, uint8_t eventType, uint8_t /*buttonState*/) {
  const SignalAspect aspect = (SignalAspect) button->getId();
  switch (eventType) {
    case AceButton::kEventClicked:
      std::cout << "new signal aspect: " << aspect << "\n";
      s.apply(aspect);
      break;
  }
}

void loop() {
  button[0].check();
  button[1].check();
  button[2].check();
  timeout();
}

void setup() {
  s.apply(Off);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  button[0].getButtonConfig()->setFeature(ButtonConfig::kFeatureClick);
  button[1].getButtonConfig()->setFeature(ButtonConfig::kFeatureClick);
  button[2].getButtonConfig()->setFeature(ButtonConfig::kFeatureClick);
  button[0].init(8, HIGH, Hp0);
  button[1].init(9, HIGH, Hp1);
  button[2].init(10, HIGH, Hp2);
  button[0].setEventHandler(handleEvent);
  button[1].setEventHandler(handleEvent);
  button[2].setEventHandler(handleEvent);

  s.apply(Hp0);
  //t.apply(Vr0);
  //Timer1.initialize(200000);
  //Timer1.attachInterrupt(timeout);
}
