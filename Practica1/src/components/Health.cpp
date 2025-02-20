#include "Health.h"
#include "macros.h"
#include "SDLUtils.h"

Health::Health() {}

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

	SDL_Rect dest = build_sdlrect(*_pos, _tex->width(),_tex->height());

	_tex->render(dest, 0.);
}