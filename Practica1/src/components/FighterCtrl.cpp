#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Manager.h"
#include "SDLUtils.h"

FighterCtrl::FighterCtrl() {}

FighterCtrl::~FighterCtrl() {}

void 
FighterCtrl::initComponent()
{
    _myTransform = _ent->getMngr()->getComponent<Transform>(_ent);

    _thrustEffect = &sdlutils().soundEffects().at("thrust");
}

void
FighterCtrl::handleInput() {

    auto &inhdlr = ih();
    if(inhdlr.isKeyDown(SDLK_LEFT)) {
        _myTransform->setRot(_myTransform->getRot() - 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_RIGHT)) {
        _myTransform->setRot(_myTransform->getRot() + 5.0f);
    }
    else if(inhdlr.isKeyDown(SDLK_UP)) {
        auto &vel = _myTransform->getVel();
        auto newVel = vel + Vector2D(0, -1).rotate(_myTransform->getRot()) * thrust;
        if(newVel.magnitude() > speedLimit) 
            newVel = newVel.normalize() * speedLimit;

        vel = newVel;

        // Esto probablemente esté mal, pero hay que probarlo
        _thrustEffect->play();
    }
}