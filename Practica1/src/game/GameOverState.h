#pragma once

#include "GameState.h"

#include <string>

class GameOverState : public GameState {
public:
    GameOverState() {}
    ~GameOverState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

private:
    std::string _msg;
};