#pragma once

#include <SDL_stdinc.h>

#include "Component.h"

struct Miraculous : public ecs::Component {

    Miraculous() : _miraculousState() {
    }

    Miraculous(int n, int m) 
    : _miraculousState(false)
    , _n(n)
    , _m(m)
    , _lastUpdate()
    {}

    // void changeState() {
    //     _miraculousState = !_miraculousState;
    // }

    bool _miraculousState;
    Uint32 _n; // Seconds in normal state
    Uint32 _m; // Seconds in miraculous state

    Uint32 _lastUpdate;
};