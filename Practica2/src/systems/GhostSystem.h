#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include <vector>

struct Transform;
struct Immunity;

class GhostSystem: public ecs::System {
public:

    GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
private:
    const std::vector<ecs::entity_t>* _ghosts;
    Uint32 _lastSpawnStamp = 0;
    VirtualTimer* _vt;

    Transform* _pacmanTransform;
    Immunity* _pacmanInmunity;

    void tryAddGhost();
};

