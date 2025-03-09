#pragma once

namespace ecs {
class Manager;
}

class GameState {
public:
	GameState() {};
	virtual ~GameState() {};

	virtual void enter() = 0;   
	virtual void leave() = 0;   
	virtual void update() = 0;

protected:
	ecs::Manager* _mgr;
};

