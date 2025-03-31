// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include "SDL.h"

struct Transform;
class ImageWithFrames;

class PacManSystem: public ecs::System {
public:

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	void receive(const Message &m) override;

	void resetPacman();
	void resetLives();
	void setImmune(bool val);
	void onGhostCollision();
private:
	Transform *_pmTR;

	const int PACMAN_START_FRAME = 0;
	const int PACMAN_END_FRAME = 3; 
	const Uint32 PACMAN_REFRESH_RATE = 40;
	bool _ascendingFrames = true;

	int _pacmanFrame = 0;
	Uint32 _lastPacmanUpdate;

	ImageWithFrames* _pacmanImageWithFrames;
};

