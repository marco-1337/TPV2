#pragma once

#include "Component.h"

class Transform;

class ShowAtOppositeSide: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::SHOW_AT_OPPOSITE_SIDE)

	ShowAtOppositeSide();
	virtual ~ShowAtOppositeSide();
	void update() override;

protected:
	Transform *_tr;
};