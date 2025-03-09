// This file is part of the course TPV2@UCM - Samir Genaim

#include "PaddleKBCtrl.h"

#include "Manager.h"
#include "InputHandler.h"
#include "Transform.h"

#include "Game.h"

PaddleKBCtrl::PaddleKBCtrl() :
		_tr(), //
		_up(SDL_SCANCODE_UP), //
		_down(SDL_SCANCODE_DOWN), //
		_stop(SDL_SCANCODE_LEFT), //
		_speed(10.0f) //
{
}

PaddleKBCtrl::~PaddleKBCtrl() {
}

void PaddleKBCtrl::initComponent() {
	auto mngr = Game::Instance()->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void PaddleKBCtrl::update() {
	auto &ihdlr = ih();

	auto &vel = _tr->getVel();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(_up)) {
			vel.setY(-_speed);
		} else if (ihdlr.isKeyDown(_down)) {
			vel.setY(_speed);
		} else if (ihdlr.isKeyDown(_stop)) {
			vel.setY(0.0f);
		}
	}
}
