#pragma once

#include "../ecs/Component.h"

struct Health : public ecs::Component {

    Health() : _maxHealth(), _health(_maxHealth) {
    }

    Health(int max) : _maxHealth(max), _health(max) {
    }

    void init(int max) {
        _maxHealth = max;
        _health = max;
    }

    int _maxHealth;
    int _health;
};