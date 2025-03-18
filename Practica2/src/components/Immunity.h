#pragma once

#include "../ecs/Component.h"

struct Immunity : public ecs::Component {

    Immunity() : _immune() {
    }

    Immunity(bool value) : _immune(value) {
    }

    void init(bool value) {
        _immune = value;
    }

    bool _immune;
};