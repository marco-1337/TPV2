#pragma once
#include "Component.h"
#include "SoundEffect.h"
#include "Transform.h"

class FighterCtrl : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)

	FighterCtrl();
	virtual ~FighterCtrl();

	void initComponent() override;

	void handleInput() override;

protected:

	Transform* _myTransform = nullptr;
	SoundEffect* _thrustEffect = nullptr;

	float thrust = 0.2f;
	float speedLimit = 3.0f;
};