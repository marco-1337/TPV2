
#pragma once
#include "Component.h"



class FighterCtrl : public ecs::Component {
public:
	FighterCtrl();
	virtual ~FighterCtrl();
	void handleInput(Container *o) override;

protected:
	float thrust = 0.2f;
	float speedLimit = 3.0f;
};