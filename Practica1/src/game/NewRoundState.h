#pragma once

#include "GameState.h"

class FighterUtils;
class AsteroidsUtils;

class NewRoundState : public GameState {
public:
    NewRoundState(ecs::Manager* mgr) : GameState(mgr) {}
    ~NewRoundState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
FighterUtils* _fighter;
AsteroidsUtils* _asteroids;
};