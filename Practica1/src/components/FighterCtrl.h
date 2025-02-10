
#pragma once

#include "InputComponent.h"

class FighterCtrl : public InputComponent {
public:
	FighterCtrl();
	virtual ~FighterCtrl();
	void handleInput(Container *o) override;

protected:
	float thrust = 0.2f;
	float speedLimit = 3.0f;
};