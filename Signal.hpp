#pragma once

#include "LightFactory.hpp"
#include "Decoder.hpp"

enum SignalAspect {
    Off = -1,
    Hp0, // Halt
    Hp1, // Fahrt
    Hp2, // Langsamfahrt
    Hp0_Sh1, // Zughalt + Rangieren erlaubt
    Vr0, // Halt erwarten
    Vr1, // Fahrt erwarten
    Vr2 // Langsamfahrt erwarten
};

class Signal {
    SignalAspect _state;
    Decoder<false> _decoder;
    LightFactory& _factory;
public:
    Signal(LightFactory& f);
    virtual void apply(enum SignalAspect state);
protected:
    virtual void assign(int id, enum LightId lid);
};
