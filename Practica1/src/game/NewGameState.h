#pragma once

#include "GameState.h"

class FighterUtils;

class NewGameState: public GameState {
public:
    NewGameState(FighterUtils* fUtils): _fighterUtils(fUtils) {}
    ~NewGameState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    FighterUtils* _fighterUtils;
};