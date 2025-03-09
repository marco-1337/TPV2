#include "Health.h"
#include "macros.h"
#include "SDLUtils.h"

Health::Health(){}

Health::~Health()
{
    delete _pos;
}

void
Health::initComponent()
{
    _pos = new Vector2D(10., 10.);
    _tex = &sdlutils().images().at("heart");
}

void Health::render()
{
    assert(_tex != nullptr);
    auto a = _tex->width();

    
    for(int i = 0; i < _health; ++i) {
        SDL_Rect dest = build_sdlrect(_pos->getX() * i, _pos->getY(), _tex->width(),_tex->height());
	    _tex->render(dest, 0.);   
    }
}