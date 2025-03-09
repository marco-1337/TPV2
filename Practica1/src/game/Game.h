// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "SDLUtils.h"

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
	bool init(std::string filename);

	void loadResources(std::string filename);
		
	std::unordered_map<std::string, float> _config;
	SDLUtils::map_access_wrapper<float> _configAccessWrapper;

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

	// config map
	inline auto& config() {
		return _configAccessWrapper;
	}

};
