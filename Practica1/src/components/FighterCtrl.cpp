#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Manager.h"
#include "SDLUtils.h"
#include "Game.h"

#include <iostream>

FighterCtrl::FighterCtrl() :
_thrust(Game::Instance()->config().at("fighter_thrust")),
_speedLimit(Game::Instance()->config().at("fighter_speed_limit")),
_rotation(Game::Instance()->config().at("fighter_rotation"))
 {}

FighterCtrl::~FighterCtrl() {}

void 
FighterCtrl::initComponent()
{
    _myTransform = Game::Instance()->getMngr()->getComponent<Transform>(_ent);
    _thrustEffect = &sdlutils().soundEffects().at("thrust");
    _thrustEffect->setVolume(Game::Instance()->config().at("volume"));
}

void
FighterCtrl::handleInput() {

    auto &inhdlr = ih();
    if(inhdlr.isKeyDown(SDLK_LEFT)) {
        _myTransform->setRot(_myTransform->getRot() - _rotation);
    }
    else if(inhdlr.isKeyDown(SDLK_RIGHT)) {
        _myTransform->setRot(_myTransform->getRot() + _rotation);
    }
    else if(inhdlr.isKeyDown(SDLK_UP)) {
        auto &vel = _myTransform->getVel();
        auto newVel = vel + Vector2D(0, -1).rotate(_myTransform->getRot()) * _thrust;
        if(newVel.magnitude() > _speedLimit) 
            newVel = newVel.normalize() * _speedLimit;

        vel = newVel;

        _thrustEffect->play();
    }
}