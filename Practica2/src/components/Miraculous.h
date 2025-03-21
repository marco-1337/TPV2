#pragma once

#include <SDL_stdinc.h>

#include "Component.h"

struct Miraculous : public ecs::Component {

    Miraculous() : _miraculousState() {
    }

    Miraculous(int n, int m) 
    : _miraculousState(false)
    , _nTime(n)
    , _mTime(m)
    , _lastUpdate()
    {}

    // void changeState() {
    //     _miraculousState = !_miraculousState;
    // }

    bool shouldUpdate(Uint32 currTime) {
        if(_miraculousState && (_lastUpdate + _mTime) > currTime ) {
            _lastUpdate = currTime;
            return true;
        }
        else if(!_miraculousState && (_lastUpdate + _nTime) > currTime) {
            _lastUpdate = currTime;
            return true;
        }
        else return false;
    }

    bool _miraculousState;
    Uint32 _nTime; // Seconds in normal state
    Uint32 _mTime; // Seconds in miraculous state

    Uint32 _lastUpdate;
};