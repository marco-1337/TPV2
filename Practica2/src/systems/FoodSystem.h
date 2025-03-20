#pragma once

#include <vector>

#include "../ecs/System.h"

namespace ecs {
    class Entity;
}

class FoodSystem : public ecs::System {
public:
    FoodSystem();
    virtual ~FoodSystem();
    void initSystem() override;
    void update() override;

	void receive(const Message &m) override;

private:
    std::vector<ecs::entity_t> _fruits;
};