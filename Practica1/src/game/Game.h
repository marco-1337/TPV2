// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "sdlutils.h"

#include "AsteroidsUtils.h"
#include "FighterUtils.h"

class FighterUtils;
class AsteroidUtils;

namespace ecs {
class Manager;
}

class Transform;
class GameState;

class Game : public Singleton<Game> {
private:
	friend Singleton<Game>;

	Game();
	virtual ~Game();
	bool init();

	ecs::Manager* _mngr;

	FighterUtils* _fighterUtils;
	AsteroidsUtils* _asteroidUtils;

	GameState* _state;

	GameState* _pausedState;
	GameState* _runningState;
	GameState* _newgameState;
	GameState* _newroundState;
	GameState* _gameoverState;

public:
	void initGame();
	void start();

	inline ecs::Manager* getMngr() {
		return _mngr;
	}

	inline FighterUtils* getFighterUtils() {
		return _fighterUtils;
	}

	inline AsteroidsUtils* getAsteroidUtils() {
		return _asteroidUtils;
	}

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	void setState(State s);
};
