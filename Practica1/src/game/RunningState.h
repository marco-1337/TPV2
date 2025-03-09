#pragma once

#include "SDL.h"
#include "GameState.h"

#include "ecs.h"
#include <vector>

class FighterUtils;
class AsteroidsUtils;


class RunningState : public GameState {
public:
    RunningState();
    ~RunningState() {}

    void enter() override;   
	void leave() override;   
	void update() override; 

protected:
    void checkCollisions();

    FighterUtils* _fighterUtils;
    AsteroidsUtils* _asteroidsUtils;

    ecs::entity_t _fighter;
    std::vector<ecs::entity_t> _asteroids;

    Uint32 _lastSpawnTime;
};