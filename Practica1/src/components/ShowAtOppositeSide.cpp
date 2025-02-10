#include "ShowAtOppositeSide.h"
#include "SDLUtils.h"
#include "Transform.h"

// TODO

ShowAtOppositeSide::ShowAtOppositeSide() {}

ShowAtOppositeSide::~ShowAtOppositeSide() {}

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