#pragma once
#include "Component.h"

class Transform;

class DeAcceleration: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::DEACCELERATION)

	DeAcceleration();
	virtual ~DeAcceleration();
	void update() override;

protected:
    float factor = 0.995f;
	Transform *_tr;
};