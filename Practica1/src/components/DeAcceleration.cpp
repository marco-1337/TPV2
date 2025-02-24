#include "DeAcceleration.h"

#include "SDLUtils.h"
#include "Transform.h"

DeAcceleration::DeAcceleration(Transform* tr): _tr(tr) {}

DeAcceleration::~DeAcceleration() {}

void DeAcceleration::update() {
    auto &vel = _tr->getVel();
    vel = vel * factor;
}