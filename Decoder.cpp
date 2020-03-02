#include "Decoder.hpp"

#include <ArduinoSTL.h>
#include <algorithm>

template<bool SystematicSwitchPolicy>
void Decoder<SystematicSwitchPolicy>::learn(int id, LightableRef const light)
{
    _all.insert(light);
    _map[id].insert(light);
}

template<bool SystematicSwitchPolicy>
std::pair<SetOfLightableRefs,SetOfLightableRefs> Decoder<SystematicSwitchPolicy>::computeChange(int prevId, int nextId)
{
    using std::set_difference;
    using std::inserter;
    using std::make_pair;

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

    return make_pair(toOff, toOn);
}

// Explicit instantiation of class template
template class Decoder<false>;
