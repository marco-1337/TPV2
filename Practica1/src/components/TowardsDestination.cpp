#include "TowardsDestination.h"
#include "Transform.h"

#include "Manager.h"
#include "SDLUtils.h"

#include "Game.h"

TowardsDestination::TowardsDestination(){}

TowardsDestination::~TowardsDestination()
{
    delete _destination;
}

void
TowardsDestination::initComponent() {
    _myTr = Game::Instance()->getMngr()->getComponent<Transform>(_ent);
    _destination = new Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()+1), 
        sdlutils().rand().nextInt(0, sdlutils().width()+1));

    assert(_myTr != nullptr);
}

void
TowardsDestination::update() {

    auto& p = _myTr->getPos();

    if ((*_destination - p).magnitude() <= MIN_DISTANCE)
    {
        delete _destination;
        _destination = new Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()+1), 
        sdlutils().rand().nextInt(0, sdlutils().width()+1));
    }

    auto& v = _myTr->getVel();
    v = v.rotate(v.angle(*_destination - p));
}