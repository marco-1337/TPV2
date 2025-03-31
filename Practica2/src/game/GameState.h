#pragma once

#include "../ecs/System.h"

namespace ecs {
class Manager;
}

class Texture;

class GameState {
public:
	enum StateID {
		PAUSED,
		RUNNING,
		NEWGAME,
		NEWROUND,
		GAMEOVER_LOSE,
		GAMEOVER_WIN
	};
	virtual void update() = 0;
};

class PausedState : public GameState {
public:
    void update() override;   
};

class RunningState : public GameState {
public:
	RunningState(ecs::System* pacmanSys, ecs::System* ghostSys, ecs::System* foodSys, ecs::System* immunitySys, ecs::System* renderSys, ecs::System* collisionSys);

    void update() override; 
private:
	ecs::System* _pacmanSys;
	ecs::System* _ghostSys;
	ecs::System* _foodSys;
	ecs::System* _immunitySys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;
};

class NewGameState : public GameState {
public:
    void update() override; 
};

class NewRoundState : public GameState {
public:
    void update() override;   
};

class GameOverState : public GameState {
public:
    void update() override;
	void setWin(bool win); 
private:
	Texture* gameOvertext;
};