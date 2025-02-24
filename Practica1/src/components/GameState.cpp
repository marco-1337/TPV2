// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"
#include "InputHandler.h"
#include "SDLUtils.h"
#include "GameState.h"
#include "Transform.h"
GameState::GameState() :
		_score(), //
		_state(NEWGAME), //
		_maxScore(5), //
		_fighterTr(nullptr) {
}

GameState::~GameState() {
}

void GameState::initComponent() {
	auto mngr = _ent->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	_fighterTr = mngr->getComponent<Transform>(fighter);
	assert(_fighterTr != nullptr);
}

void GameState::update() {
	if (_state != RUNNING) {

		auto &inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (_state) {
			case NEWGAME:
				// moveBall();
				setState(RUNNING);
				break;
			case PAUSED:
				// moveBall();
				setState(RUNNING);
				break;
			case GAMEOVER:
				setState(NEWGAME);
				setScore(0, 0);
				setScore(1, 0);
				break;
			default:
				break;
			}
		}
	}
}

// void GameState::onBallExit(Side side) {

// 	assert(_state == RUNNING); // this should be called only when game is running

// 	if (side == LEFT) {
// 		_score[1]++;
// 	} else {
// 		_score[0]++;
// 	}
// 	resetBall();
// 	if (_score[0] < _maxScore && _score[1] < _maxScore)
// 		_state = PAUSED;
// 	else
// 		_state = GAMEOVER;
// }

// void GameState::resetBall() {
// 	_fighterTr->getPos().set(sdlutils().width() / 2 - 5,
// 			sdlutils().height() / 2 - 5);
// 	_fighterTr->getVel().set(0, 0);
// }

// void GameState::moveBall() {
// 	auto &r = sdlutils().rand();

// 	int dx = 1 - 2 * r.nextInt(0, 2); // 1 or -1
// 	int dy = 1 - 2 * r.nextInt(0, 2); // 1 or -1

// 	Vector2D v(dx * r.nextInt(2, 7), dy * r.nextInt(2, 7));
// 	_fighterTr->getVel().set(v.normalize() * 2);
// }
