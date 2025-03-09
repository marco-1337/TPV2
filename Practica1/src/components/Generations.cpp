#include "Generations.h"
#include "SDLUtils.h"

Generations::Generations() {}

Generations::~Generations() {}

void
Generations::initComponent() {
    _generation = sdlutils().rand().nextInt(1,4);
}

// Sets generation (0-3)
void
Generations::setGeneration(int gen) {
    assert(gen >= 0 && gen < 4);
    _generation = gen;
}