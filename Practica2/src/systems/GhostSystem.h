#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include <vector>

struct Health;
struct Transform;
struct Immunity;

class GhostSystem: public ecs::System {
public:

    GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
    void receive(const Message &m) override;
private:
    const std::vector<ecs::entity_t>* _ghosts;
    Uint32 _lastSpawnStamp = 0;
    VirtualTimer* _vt;

    Transform* _pacmanTransform;
    Health* _pacmanHealth;

    bool _pacmanInmunity, _changeEnabled;

    static constexpr float GHOST_SPEED = 1.1f;

    void resetFlags();
    void tryAddGhost();
    void updateDirection(Transform*& gTr);
    void moveGhosts(Transform*& gTr);
    void killAllGhosts();

    void pacmanHitsGhost(ecs::entity_t e);
};

