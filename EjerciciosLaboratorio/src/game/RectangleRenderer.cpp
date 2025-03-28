// This file is part of the course TPV2@UCM - Samir Genaim

#include "RectangleRenderer.h"

#include "macros.h"
#include "SDLUtils.h"
#include "Container.h"

RectangleRenderer::RectangleRenderer() :
		RectangleRenderer(build_sdlcolor(0xffffffff)) {

}

RectangleRenderer::RectangleRenderer(SDL_Color color) :
		_color(color) {
}

RectangleRenderer::~RectangleRenderer() {
}

void RectangleRenderer::render(Container *o) {

	auto &pos = o->getPos();
	auto width = o->getWidth();
	auto height = o->getHeight();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(_color));

	SDL_Rect rect = build_sdlrect(pos.getX(), pos.getY(), width, height);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);

}
