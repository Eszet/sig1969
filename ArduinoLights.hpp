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
        mapPin(Ws, 40);
    }
};

class MetroLights : public SimpleFactory {
public:
    MetroLights()
    {
        mapPin(Rt, 3);
        mapPin(Gn, 5);
        mapPin(Ge, 6);
        mapPin(Rt1, 7);
        mapPin(Rt2, 8);
        mapPin(Ws, 9);
    }
};
