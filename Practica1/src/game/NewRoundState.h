#pragma once

#include "GameState.h"

class FighterUtils;
class AsteroidsUtils;

class NewRoundState : public GameState {
public:
    NewRoundState(FighterUtils* fUtils, AsteroidsUtils* aUtils): _fighterUtils(fUtils), _asteroidsUtils(aUtils) {}
    ~NewRoundState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    FighterUtils* _fighterUtils;
    AsteroidsUtils* _asteroidsUtils;
};