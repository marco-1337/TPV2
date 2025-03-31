// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "GameState.h"

class Game : public Singleton<Game> {
public:
	void initGame();
	void start();

	void setState(GameState::StateID);

	inline ecs::Manager* getManager() { return _mngr; }

private:
	friend Singleton<Game>;

	Game();
	virtual ~Game();
	
	bool init();

	ecs::Manager* _mngr;

	GameState* _currentState;

	PausedState* _pausedState;
	RunningState* _runningState;
	NewGameState* _newgameState;
	NewRoundState* _newroundState;
	GameOverState* _gameoverState;

	ecs::System* _pacmanSys;
	ecs::System* _ghostSys;
	ecs::System* _foodSys;
	ecs::System* _immunitySys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;
};

