#pragma once

#include "ecs.h"

class AsteroidsFacade {
public:
    AsteroidsFacade() { }
    
    virtual ~AsteroidsFacade() { }
    
    virtual void create_asteroids(int n) = 0;
    
    virtual void remove_all_asteroids() = 0;
    
    virtual void split_asteroid(ecs::entity_t a) = 0;
};