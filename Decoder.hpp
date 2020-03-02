#pragma once

#include "Lightable.hpp"

#include <ArduinoSTL.h>
#include <set>
#include <map>
#include <utility>

typedef Lightable *LightableRef;
typedef std::set<LightableRef> SetOfLightableRefs;
typedef std::map<int, SetOfLightableRefs> MapOfLightableRefs;

template<bool SystematicSwitchPolicy>
class Decoder
{
    SetOfLightableRefs _all;
    MapOfLightableRefs _map;
public:
    virtual void learn(int id, LightableRef const light);
    virtual std::pair<SetOfLightableRefs,SetOfLightableRefs> computeChange(int prevId, int nextId);
};
