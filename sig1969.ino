#include "ArduinoLights.hpp"
#include "Signal.hpp"

#include "Chrono.h" // install Chrono lib
#include "TimerOne.h" // install TimerOne lib

#include <ArduinoSTL.h>
#include <vector>
#include <iostream>

class BlockSignal : public Signal {
public:
    BlockSignal(LightFactory& lf) : Signal(lf)
    {
        assign(Hp0, Rt);
        assign(Hp1, Gn);
    }
};

class EntrySignal : public Signal {
public:
    EntrySignal(LightFactory& lf) : Signal(lf)
    {
        assign(Hp0, Rt);
        assign(Hp1, Gn);
        assign(Hp2, Gn);
        assign(Hp2, Ge);
    }
};

class DepartureSignal : public Signal {
public:
    DepartureSignal(LightFactory& lf) : Signal(lf)
    {
        assign(Hp0, Rt1);
        assign(Hp0, Rt2);

        assign(Hp1, Gn);

        assign(Hp2, Gn);
        assign(Hp2, Ge);

        assign(Hp0_Sh1, Rt1);
        assign(Hp0_Sh1, Ws);
    }
};

class DistantSignal : public Signal {
public:
    DistantSignal(LightFactory& lf) : Signal(lf)
    {
        assign(Vr0, Ge1);
        assign(Vr0, Ge2);

        assign(Vr1, Gn1);
        assign(Vr1, Gn2);

        assign(Vr2, Gn1);
        assign(Vr2, Ge2);
    }
};

FeatherLights o;
DepartureSignal s(o);
//DistantSignal t(o);

void timeout()
{
    const std::vector<SignalAspect> demo { Hp0, Hp1, Hp2, Hp0_Sh1  };
    static auto it = demo.begin();
    static Chrono c;

    if(c.hasPassed(1000))
    {
         c.restart();
         s.apply(it != demo.end() ? *it : *(it = demo.begin()));
         ++it;
    }
}

void setup() {
    s.apply(Hp0);
    //t.apply(Vr0);
    Timer1.initialize(200000);
    Timer1.attachInterrupt(timeout);
}

void loop() {
}
