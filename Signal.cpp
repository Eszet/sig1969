#include "Signal.hpp"

Signal::Signal(LightFactory& lf) : _state(Off), _factory(lf)
{
}

static void turnAll(std::set<Lightable*> all, enum LightState state)
{
    for(auto light : all)
    {
        light->turn(state);
    }
}

void Signal::assign(int id, enum LightId lid)
{
    _decoder.learn(id, _factory.getLight(lid));
}

void Signal::apply(enum SignalAspect state)
{
    auto change = _decoder.computeChange(_state, state);

    turnAll(change.first, LightOff);
    // ... wait all off ...
    turnAll(change.second, LightOn);

    _state = state;
}

bool Signal::execute(void)
{
    bool result = false;
  
    for(auto light : _decoder.getAll())
    {
        if(light->execute())
            result = true;
    }

    return result;
}
