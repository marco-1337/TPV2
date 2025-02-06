#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Container.h"

FighterCtrl::FighterCtrl() {}

FighterCtrl::~FighterCtrl() {}

void
FighterCtrl::handleInput(Container* o) {
    auto &inhdlr = ih();
    if(inhdlr.isKeyDown(SDLK_LEFT)) {
        o->setRotation(o->getRotation() - 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_RIGHT)) {
        o->setRotation(o->getRotation() + 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_UP)) {
        auto &vel = o->getVel();
        auto newVel = vel + Vector2D(0, -1).rotate(o->getRotation()) * thrust;
        if(newVel.magnitude() > speedLimit) 
            newVel = newVel.normalize() * speedLimit;

        vel = newVel;
    }
}