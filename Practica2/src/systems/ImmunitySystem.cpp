#include "ImmunitySystem.h"

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

ImmunitySystem::ImmunitySystem() {
    _vt = &(sdlutils().virtualTimer());
}

void
ImmunitySystem::initSystem() {
    reset();
}

void
ImmunitySystem::update() {
    if (_immunity)
    {
        if (_vt->currTime() - _immunityTimestamp >= IMMUNITY_TIME) {
            _immunity = false;
            Message m;
            m.id = _m_IMMUNITY_END;
            _mngr->send(m);
        }
    }
}

void 
ImmunitySystem::receive(const Message &m) {
    switch (m.id) {
        case _m_IMMUNITY_START:
            if (!_immunity) {
                _immunity = true;
                _immunityTimestamp = _vt->currTime();
            }
            break;
        case _m_ROUND_START:
            reset();
            break;
        default:
            break;
    }
}

void
ImmunitySystem::reset() {
    _immunityTimestamp = _vt->currTime();
    _immunity = false;
}