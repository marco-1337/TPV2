// This file is part of the course TPV2@UCM - Samir Genaim

#include "ImageWithFrames.h"

#include <cassert>

#include "Manager.h"
#include "macros.h"
#include "Texture.h"
#include "Transform.h"

#include "Game.h"

#include "SDLUtils.h"

#include <iostream>

ImageWithFrames::ImageWithFrames() 
:_tr(), 
_tex(), 
_rows(),
_cols(),
_currentFrame(), 
_updateFrecuency()
{ }

ImageWithFrames::ImageWithFrames(Texture *tex, int cols, int rows, Uint32 updateFrecuency) 
:_tr(), 
_tex(tex), 
_cols(cols),
_rows(rows) , 
_currentFrame(0),
_updateFrecuency(updateFrecuency)
{ 
    assert(_tex != nullptr);
    assert(_cols >= 1 && _rows >=1);
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	auto mngr = Game::Instance()->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
    _lastFrameTime = sdlutils().virtualTimer().currTime();
}

void ImageWithFrames::update() {
    if (sdlutils().virtualTimer().currTime() > _lastFrameTime + _updateFrecuency)
    {
        if (++_currentFrame >=_cols*_rows) _currentFrame = 0;
        _lastFrameTime = sdlutils().virtualTimer().currTime();
    }
}

void ImageWithFrames::render() {

	SDL_Rect dest = build_sdlrect(_tr->getPos(), _tr->getWidth(),
			_tr->getHeight());

	assert(_tex != nullptr);

    Vector2D frameOrigin = Vector2D(
        _tex->width()/_cols * (_currentFrame % _cols),
        _tex->height()/_rows * (_currentFrame / _cols)
        );

    SDL_Rect frame = build_sdlrect(frameOrigin,_tex->width() / _cols, _tex->height() / _rows);

	_tex->render(frame, dest);
}
