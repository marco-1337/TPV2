#pragma once

#include "GameState.h"

class PausedState : public GameState {
public:
    PausedState(ecs::Manager* mgr) : GameState(mgr) {}
    ~PausedState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 
};