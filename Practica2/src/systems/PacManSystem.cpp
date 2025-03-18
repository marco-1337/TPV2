// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/Immunity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		_pmTR(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity

	auto pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	_pmTR = _mngr->addComponent<Transform>(pacman);
	auto s = 50.0f; // TODO config
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	_mngr->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	_mngr->addComponent<Health>(pacman, 3); // TODO config
	_mngr->addComponent<Immunity>(pacman, false);
}

void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { 
			_pmTR->_vel = Vector2D(0.0f,-3.0f).rotate(_pmTR->_rot);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { 
			_pmTR->_vel = Vector2D(0.f, 0.f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			_pmTR->_rot = _pmTR->_rot - 90.0f;
			_pmTR->_vel = _pmTR->_vel.rotate(-90.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			_pmTR->_rot = _pmTR->_rot + 90.0f;
			_pmTR->_vel = _pmTR->_vel.rotate(90.0f);
		} 

	}

	// move the pacman
	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

}

void PacManSystem::resetPosition() {
	auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
	
	auto x = (sdlutils().width() - _pmTR->_width) / 2.0f;
	auto y = (sdlutils().height() - _pmTR->_height) / 2.0f;

	_pmTR->_pos = Vector2D(x,y);
}

void PacManSystem::resetLives() {
	auto health = _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::PACMAN));
	health->_health = health->_maxHealth;
}

