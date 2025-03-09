#pragma once

#include "Component.h"

class Generations : public ecs::Component {
public:
__CMPID_DECL__(ecs::cmp::GENERATIONS)

    Generations();
    ~Generations();

    void initComponent() override;

    inline int getGeneration() const {
        return _generation;
    }

    void setGeneration(int gen);

protected:
    int _generation;
};