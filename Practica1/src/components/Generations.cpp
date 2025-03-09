#include "Generations.h"
#include "SDLUtils.h"
#include "Game.h"

Generations::Generations() {}

Generations::~Generations() {}

void
Generations::initComponent() {
    _generation = sdlutils().rand().nextInt(1, Game::Instance()->config().at("asteroids_generations"));
}

// Sets generation (0-3)
void
Generations::setGeneration(int gen) {
    assert(gen >= 0 && gen < Game::Instance()->config().at("asteroids_generations"));
    _generation = gen;
}