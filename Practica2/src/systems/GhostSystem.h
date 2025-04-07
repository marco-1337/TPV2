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

    static constexpr int FIRST_NORMAL_FRAME = 32;
    static constexpr int FIRST_VULNERABLE_FRAME = 48;
    static constexpr int ANIM_FRAME_QUANTITY = 8;

    static constexpr Uint32 FRAME_DURATION = 200;

    int _currentFrame = 0;
    Uint32 _lastFrameUpdated;

    void resetFlags();
    void tryAddGhost();
    void updateDirection(Transform*& gTr);
    void moveGhosts(Transform*& gTr);
    void killAllGhosts();

    void pacmanHitsGhost(ecs::entity_t e);
};

