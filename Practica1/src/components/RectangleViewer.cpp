// This file is part of the course TPV2@UCM - Samir Genaim

#include "RectangleViewer.h"

#include <cassert>
#include "Manager.h"
#include "macros.h"
#include "SDLUtils.h"
#include "Transform.h"

#include "Game.h"

RectangleViewer::RectangleViewer() :
		RectangleViewer(build_sdlcolor(0xffffffff), false) {
}

RectangleViewer::RectangleViewer(SDL_Color color, bool empty) :
		_tr(nullptr), //
		_empty(empty), //
		_color(color) {
}

RectangleViewer::~RectangleViewer() {
}

void RectangleViewer::initComponent() {
	auto mngr = Game::Instance()->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void RectangleViewer::render() {
	auto &pos = _tr->getPos();
	auto width = _tr->getWidth();
	auto height = _tr->getHeight();

	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(_color));
	SDL_Rect rect = build_sdlrect(pos.getX(), pos.getY(), width, height);

	if (_empty) {
		SDL_RenderDrawRect(sdlutils().renderer(), &rect);
	} else {
		SDL_RenderFillRect(sdlutils().renderer(), &rect);
	}
}
