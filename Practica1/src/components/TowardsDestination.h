#pragma once

#include "Component.h"

class Transform;
class Vector2D;

class TowardsDestination : public ecs::Component {
public:
    __CMPID_DECL__(ecs::cmp::TOWARDS_DESTINATION)

    TowardsDestination();
    ~TowardsDestination();

    void initComponent() override;
    void update() override;

protected:
    Transform* _myTr = nullptr;
    Vector2D* _destination;
    
    static constexpr float MIN_DISTANCE = 10.0;
};