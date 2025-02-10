#pragma once
#include "Component.h"

class Transform;

class ShowAtOppositeSide: public ecs::Component {
public:
	ShowAtOppositeSide();
	virtual ~ShowAtOppositeSide();
	void update() override;

protected:
	Transform *_tr;
};