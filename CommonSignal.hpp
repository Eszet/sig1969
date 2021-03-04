#pragma once

#include "Signal.hpp"

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
