#pragma once

#include "Component.h"

class Transform;

class Follow : public ecs::Component {
public:
    __CMPID_DECL__(ecs::cmp::FOLLOW)

    Follow();
    ~Follow();

    void initComponent() override;
    void update() override;

protected:
    Transform* _myTr = nullptr;
    Transform* _fighterTr = nullptr;
};