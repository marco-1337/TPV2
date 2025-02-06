#include "ShowAtOppositeSide.h"

#include "SDLUtils.h"
#include "Container.h"

ShowAtOppositeSide::ShowAtOppositeSide() {}

ShowAtOppositeSide::~ShowAtOppositeSide() {}

void ShowAtOppositeSide::update(Container *o) {
    auto &pos = o->getPos();
    auto width = o->getWidth();
    auto height = o->getHeight();

    if(pos.getX() + width < 0)
        pos.setX(sdlutils().width());
    else if(pos.getX() > sdlutils().width())
        pos.setX(-width);
    
    if(pos.getY() + height < 0) 
        pos.setY(sdlutils().height());
    else if(pos.getY() > sdlutils().height())
        pos.setY(-height);
}