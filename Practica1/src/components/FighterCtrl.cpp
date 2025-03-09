#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Manager.h"
#include "SDLUtils.h"
#include "Game.h"

#include <iostream>

FighterCtrl::FighterCtrl() {}

FighterCtrl::~FighterCtrl() {}

void 
FighterCtrl::initComponent()
{
    _myTransform = Game::Instance()->getMngr()->getComponent<Transform>(_ent);
    _thrustEffect = &sdlutils().soundEffects().at("thrust");
    _thrustEffect->setVolume(10);
}

void
FighterCtrl::handleInput() {

    auto &inhdlr = ih();
    if(inhdlr.isKeyDown(SDLK_LEFT)) {
        _myTransform->setRot(_myTransform->getRot() - rotation);
    }
    else if(inhdlr.isKeyDown(SDLK_RIGHT)) {
        _myTransform->setRot(_myTransform->getRot() + rotation);
    }
    else if(inhdlr.isKeyDown(SDLK_UP)) {
        std::cout << "THRUST\n";
        auto &vel = _myTransform->getVel();
        auto newVel = vel + Vector2D(0, -1).rotate(_myTransform->getRot()) * thrust;
        if(newVel.magnitude() > speedLimit) 
            newVel = newVel.normalize() * speedLimit;

        vel = newVel;

        _thrustEffect->play();
    }
}