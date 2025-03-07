#pragma once

#include "GameState.h"

#include <string>

class GameOverState : public GameState {
public:
    GameOverState(ecs::Manager* mgr) : GameState(mgr) {}
    ~GameOverState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

private:
    std::string _msg;
};