// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "../sdlutils/SDLUtils.h"

class GameState;

class Game : public Singleton<Game> {
public:
	void initGame();
	void start();
private:
	friend Singleton<Game>;

	Game();
	virtual ~Game();
	
	bool init();

	ecs::Manager* _mngr;

	//GameState* _state;

	/*
	GameState* _pausedState;
	GameState* _runningState;
	GameState* _newgameState;
	GameState* _newroundState;
	GameState* _gameoverState;
	*/

	ecs::System *_pacmanSys;
	ecs::System *_gameCtrlSys;
	ecs::System *_startsSys;
	ecs::System *_renderSys;
	ecs::System *_collisionSys;
};

