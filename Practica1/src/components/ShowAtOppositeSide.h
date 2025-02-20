#pragma once

#include "Component.h"

class Transform;

class ShowAtOppositeSide: public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::SHOWATOPPOSITESIDE)

	ShowAtOppositeSide();
	virtual ~ShowAtOppositeSide();
	void update() override;

protected:
	Transform *_tr;
};