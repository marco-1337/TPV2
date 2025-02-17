#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"

FighterCtrl::FighterCtrl() {}

FighterCtrl::~FighterCtrl() {}

void 
FighterCtrl::initComponent()
{
    _myTransform = ent->getMngr()mgr->getComponent<Transform>(_ent);
}

void
FighterCtrl::handleInput() {

    auto &inhdlr = ih();
    if(inhdlr.isKeyDown(SDLK_LEFT)) {
        t->setRot(e->getRotation() - 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_RIGHT)) {
        e->setRotation(o->getRotation() + 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_UP)) {
        auto &vel = o->getVel();
        auto newVel = vel + Vector2D(0, -1).rotate(o->getRotation()) * thrust;
        if(newVel.magnitude() > speedLimit) 
            newVel = newVel.normalize() * speedLimit;

        vel = newVel;
    }
}