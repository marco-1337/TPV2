#pragma once

#include "GameState.h"

class PausedState : public GameState {
public:
    PausedState() {}
    ~PausedState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 
};