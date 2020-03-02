#pragma once

#include "SimpleFactory.hpp"

class FeatherLights : public SimpleFactory {
public:
    FeatherLights()
    {
        mapPin(Rt, 3);
        mapPin(Gn, 5);
        mapPin(Ge, 6);
        mapPin(Rt1, 3);
        mapPin(Rt2, 9);
        mapPin(Ws, 13);
    }
};
