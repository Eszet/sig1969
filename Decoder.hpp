#pragma once

#include "Lightable.hpp"

#include <ArduinoSTL.h>
#include <set>
#include <map>
#include <algorithm>
#include <utility>

template<bool SystematicSwitchPolicy>
class Decoder
{
    typedef Lightable *LightableRef;
    typedef std::set<LightableRef> SetOfLightableRefs;
    typedef std::map<int, SetOfLightableRefs> MapOfLightableRefs;
    SetOfLightableRefs _all;
    MapOfLightableRefs _map;
public:
    virtual void learn(int id, LightableRef const light)
    {
        _all.insert(light);
        _map[id].insert(light);
    }

    virtual std::pair<SetOfLightableRefs,SetOfLightableRefs> computeChange(int prevId, int nextId)
    {
        using std::set_difference;
        using std::inserter;

        const auto prev = _map[prevId];
        const auto next = _map[nextId];
        SetOfLightableRefs toOff, toOn;

        if(!SystematicSwitchPolicy)
        {
            set_difference(prev.begin(), prev.end(), next.begin(), next.end(), inserter(toOff, toOff.begin()));
        }
        else
        {
            set_difference(_all.begin(), _all.end(), next.begin(), next.end(), inserter(toOff, toOff.begin()));
        }
        
        if(!SystematicSwitchPolicy)
        {
            set_difference(next.begin(), next.end(), prev.begin(), prev.end(), inserter(toOn, toOn.begin()));
        }
        else
        {
            toOn = next;
        }

        return std::make_pair(toOff, toOn);
    }
};
