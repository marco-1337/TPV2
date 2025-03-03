#pragma once

#include "GameState.h"

class NewGameState: public GameState {
public:
    NewGameState(Manager* mgr) : GameState(mgr) {}
    ~NewGameState() {}

    void enter() override;   
	virtual void leave() override;   
	virtual void update() override; 
};