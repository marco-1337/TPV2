#include "DeAcceleration.h"

#include "SDLUtils.h"
#include "Transform.h"

DeAcceleration::DeAcceleration() {}

DeAcceleration::~DeAcceleration() {}

void DeAcceleration::update() {
    auto &vel = _tr->getVel();
    vel = vel * factor;
}