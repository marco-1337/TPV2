#pragma once

#include "FighterFacade.h"

namespace ecs {
    class Manager;
}

class FighterUtils: public FighterFacade
{
public:
    FighterUtils();
    inline ~FighterUtils() {}

    void create_fighter() override;
    void reset_fighter() override;
    void reset_lives() override;
    int update_lives(int n) override;
    
private:
    ecs::Manager* _mngr;
    static constexpr float FIGHTER_SIZE = 45.0f;
};