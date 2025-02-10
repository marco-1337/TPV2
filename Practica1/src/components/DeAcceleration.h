#pragma once
#include "Component.h"

class Transform;

class DeAcceleration: public ecs::Component {
public:
	DeAcceleration();
	virtual ~DeAcceleration();
	void update() override;

protected:
    float factor = 0.995f;
	Transform *_tr;
};