// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

namespace ecs {
class Manager;
}

class Transform;
class GameState;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	void checkCollisions();
	ecs::Manager *_mngr;

	Transform *_fighterTr;
	GameState *_gameState;

public:
	inline ecs::Manager* getMngr() {
		return _mngr;
	}
};

