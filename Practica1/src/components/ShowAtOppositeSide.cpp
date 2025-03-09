#include "ShowAtOppositeSide.h"
#include "SDLUtils.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"

#include "Game.h"

ShowAtOppositeSide::ShowAtOppositeSide() {}

ShowAtOppositeSide::~ShowAtOppositeSide() {}

void
ShowAtOppositeSide::initComponent() {
    _tr = Game::Instance()->getMngr()->getComponent<Transform>(_ent);
}

void ShowAtOppositeSide::update() {
    auto &pos = _tr->getPos();
    auto width = _tr->getWidth();
    auto height = _tr->getHeight();

    if(pos.getX() + width < 0)
        pos.setX(sdlutils().width());
    else if(pos.getX() > sdlutils().width())
        pos.setX(-width);
    
    if(pos.getY() + height < 0) 
        pos.setY(sdlutils().height());
    else if(pos.getY() > sdlutils().height())
        pos.setY(-height);
}