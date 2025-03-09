#pragma once

#include "AsteroidsFacade.h"
#include "Manager.h"

class AsteroidsUtils: public AsteroidsFacade
{
public:
    AsteroidsUtils();
    
    virtual ~AsteroidsUtils() { }
    
    void create_asteroids(int n) override;
    
    void remove_all_asteroids() override;
    
    void split_asteroid(ecs::entity_t a) override;
protected:
    ecs::Manager* _mngr;
};