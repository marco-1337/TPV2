
#pragma once

#include "InputComponent.h"

class FighterCtrl : public InputComponent {
public:
	FighterCtrl();
	virtual ~FighterCtrl();
	void handleInput(Container *o) override;
};