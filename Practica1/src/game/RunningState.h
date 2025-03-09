#pragma once

#include "SDL.h"
#include "GameState.h"

#include "ecs.h"
#include <vector>

class FighterUtils;
class AsteroidsUtils;

namespace ecs
{
    class Manager;
}

class RunningState : public GameState {
public:
    RunningState(FighterUtils* fUtils, AsteroidsUtils* aUtils);
    ~RunningState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    void checkCollisions();

    FighterUtils* _fighterUtils;
    AsteroidsUtils* _asteroidsUtils;

    ecs::entity_t _fighter;
    const std::vector<ecs::entity_t>* _asteroids;

    Uint32 _lastSpawnTime;

    ecs::Manager* _mngr;
};