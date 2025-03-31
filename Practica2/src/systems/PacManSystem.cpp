// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/Immunity.h"
#include "../components/ImageWithFrames.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

#include <iostream>

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

	_mngr->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman_sprites"), 8, 8, 0);
	_mngr->addComponent<Health>(pacman, 3); // TODO config
	_mngr->addComponent<Immunity>(pacman, false);

	_lastPacmanUpdate = sdlutils().virtualTimer().currTime();
	_pacmanImageWithFrames = _mngr->getComponent<ImageWithFrames>(pacman);
}

void PacManSystem::update() {

	if (sdlutils().virtualTimer().currTime() - _lastPacmanUpdate >= PACMAN_REFRESH_RATE) {
		if(_pacmanFrame == PACMAN_END_FRAME)
			_ascendingFrames = false;
		else if (_pacmanFrame == PACMAN_START_FRAME)
			_ascendingFrames = true;

		if (_ascendingFrames) ++_pacmanFrame;
		else --_pacmanFrame;

		_pacmanImageWithFrames->setFrame(_pacmanFrame);

		_lastPacmanUpdate = sdlutils().virtualTimer().currTime();
	}

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { 
			_pmTR->_vel = Vector2D(0.0f,-3.0f).rotate(_pmTR->_rot);
			sdlutils().musics().at("pacman_chomp").play();
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { 
			_pmTR->_vel = Vector2D(0.f, 0.f);
			sdlutils().musics().at("pacman_chomp").haltMusic();
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
		sdlutils().musics().at("pacman_chomp").haltMusic();
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
		sdlutils().musics().at("pacman_chomp").haltMusic();
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
		sdlutils().musics().at("pacman_chomp").haltMusic();
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
		sdlutils().musics().at("pacman_chomp").haltMusic();
	}

}

void 
PacManSystem::receive(const Message &m) {
    switch (m.id) {
        case _m_NEW_GAME:
            resetLives();
            break;
		case _m_ROUND_START:
			resetPosition();
		    sdlutils().soundEffects().at("pacman_intro").play();
			break;
		case _m_PACMAN_FOOD_COLLISION:
			sdlutils().soundEffects().at("pacman_eat").play();
			break;
		case _m_PACMAN_GHOST_COLLISION:
			onGhostCollision();
			break;
		case _m_GAME_OVER:
			if(m.game_over_data.victory)
			    sdlutils().soundEffects().at("pacman_won").play();
        default:
            break;
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

void PacManSystem::onGhostCollision() {
	auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pmImmunity = _mngr->getComponent<Immunity>(pacman);

	if(!pmImmunity->_immune) { // If pacman has no immunity
		auto pmHealth = _mngr->getComponent<Health>(pacman);

		if(--pmHealth->_health > 0) { // Lose a life and start a new round
			sdlutils().soundEffects().at("pacman_death").play();

			Message m;
			m.id = _m_ROUND_OVER;
			_mngr->send(m);
			
			Game::Instance()->setState(GameState::NEWROUND);
		}
		else { // Lose game
			Message m;
			m.id = _m_GAME_OVER;
			m.game_over_data.victory = false;
			_mngr->send(m);
		}
	}
}