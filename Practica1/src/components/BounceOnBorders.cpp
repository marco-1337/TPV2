// This file is part of the course TPV2@UCM - Samir Genaim

#include "BounceOnBorders.h"

#include <cassert>
#include "Manager.h"
#include "SDLUtils.h"
#include "Transform.h"

BounceOnBorders::BounceOnBorders() :
		_tr(nullptr) {
}

BounceOnBorders::~BounceOnBorders() {
}

void BounceOnBorders::initComponent() {
	auto mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void BounceOnBorders::update() {
	auto &pos = _tr->getPos();
	auto &vel = _tr->getVel();

	// check upper/lower borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.setY(-vel.getY());
		// play some sound
		sdlutils().soundEffects().at("wall_hit").play();
	} else if (pos.getY() + _tr->getHeight() > sdlutils().height()) {
		pos.setY(sdlutils().height() - _tr->getHeight());
		vel.setY(-vel.getY());
		sdlutils().soundEffects().at("wall_hit").play();
	}
}
