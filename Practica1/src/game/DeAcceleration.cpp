#include "DeAcceleration.h"

#include "SDLUtils.h"
#include "Container.h"

DeAcceleration::DeAcceleration() {}

DeAcceleration::~DeAcceleration() {}

void DeAcceleration::update(Container *o) {
    auto &vel = o->getVel();
    vel = vel * factor;
}