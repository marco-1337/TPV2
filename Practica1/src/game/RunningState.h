#pragma once

#include "GameState.h"

class FighterUtils;
class AsteroidsUtils;

class RunningState : public GameState {
public:
    RunningState(ecs::Manager* mgr) : GameState(mgr) {}
    ~RunningState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    void checkCollisions();

    FighterUtils* _fighterUtils;
    AsteroidsUtils* _asteroidsUtils;
};