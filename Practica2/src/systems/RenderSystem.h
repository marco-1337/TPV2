// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "SDL.h"

class Texture;
struct Transform;
class ImageWithFrames;

class RenderSystem: public ecs::System {
public:
	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawFrameEntity(ecs::entity_t ent);
	void drawPacMan();
	void drawGhosts();
	void drawFruits();
	void draw(Transform *tr, Texture *tex);
	void draw(const SDL_Rect& dest, float rot, Texture *tex);
	void drawFrame(Transform *tr, Texture *tex, SDL_Rect frame);
	void drawHealth();
};

