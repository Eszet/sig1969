#pragma once

#include "Lightable.hpp"

enum LightId { Rt, Gn, Ge, Ws, Rt1, Rt2, Ge1, Ge2, Gn1, Gn2 };

struct LightFactory
{
    virtual Lightable * getLight(enum LightId id) = 0;
};
