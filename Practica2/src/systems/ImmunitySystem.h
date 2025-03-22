#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

#include <vector>

class VirtualTimer;

struct Health;
struct Transform;
struct Immunity;

class ImmunitySystem: public ecs::System {
public:
    ImmunitySystem();
    ~ImmunitySystem(){}
	void initSystem() override;
    void receive(const Message &m) override;
    void update() override;
private:
    bool _immunity;
    Uint32 _immunityTimestamp;
    VirtualTimer* _vt;

    const Uint32 IMMUNITY_TIME = 10000;

    void reset();
};

