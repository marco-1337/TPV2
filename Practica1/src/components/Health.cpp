#include "Health.h"
#include "macros.h"

Health::Health(Texture* texture): _tex(texture)
{
    _pos = new Vector2D(10., 10.);
}

Health::~Health()
{
    delete _pos;
}

void Health::render()
{
    auto a = _tex->width();

	SDL_Rect dest = build_sdlrect(*_pos, _tex->width(),_tex->height());

	assert(_tex != nullptr);
	_tex->render(dest, 0.);
}