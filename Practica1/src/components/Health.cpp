#include "Health.h"
#include "macros.h"
#include "SDLUtils.h"
#include "Game.h"

Health::Health() : _health(Game::Instance()->config().at("fighter_health"))
{}

Health::~Health()
{
    delete _pos;
}

void
Health::initComponent()
{
    _pos = new Vector2D(10., 10.);
    _tex = &sdlutils().images().at("heart");

    assert(_tex != nullptr);
}

void Health::render()
{
    assert(_tex != nullptr);
    
    for(int i = 0; i < _health; ++i) {
        SDL_Rect dest = build_sdlrect(_pos->getX() +  _tex->width()/4 * i, _pos->getY(), _tex->width()/4,_tex->height()/4);
	    _tex->render(dest, 0.);   
    }
}

void Health::resetHealth() {
    _health = Game::Instance()->config().at("fighter_health");
}