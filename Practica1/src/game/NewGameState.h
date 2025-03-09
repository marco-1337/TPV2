#pragma once

#include "GameState.h"

class FighterUtils;

class NewGameState: public GameState {
public:
    NewGameState() {}
    ~NewGameState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    FighterUtils* _fighterUtils;
};