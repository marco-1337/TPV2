// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class StarsSystem: public ecs::System {
public:

	StarsSystem();
	virtual ~StarsSystem();
	void initSystem() override;
	void update() override;
	void addStar(unsigned int n);
	void onStarEaten(ecs::entity_t e);
	void receive(const Message &m) override;
private:
	unsigned int _starsLimit;
	unsigned int _currNumOfStars;
};

