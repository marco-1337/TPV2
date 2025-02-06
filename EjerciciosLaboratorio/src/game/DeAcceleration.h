#pragma once

#include "PhysicsComponent.h"

class DeAcceleration: public PhysicsComponent {
public:
	DeAcceleration();
	virtual ~DeAcceleration();
	void update(Container *o) override;

protected:
    float factor = 0.995f;
};