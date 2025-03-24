// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include <iostream>

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {

}

void RenderSystem::update() {
	drawPacMan();
	drawGhosts();
}

void RenderSystem::drawPacMan() {
	auto e = _mngr->getHandler(ecs::hdlr::PACMAN);
	drawFrameEntity(e);
}

void RenderSystem::drawGhosts() {
	auto ghosts = _mngr->getEntities(ecs::grp::GHOSTS);

	for (int i = 0; i < ghosts.size(); ++i) {
		drawFrameEntity(ghosts[i]);
	}
}

void RenderSystem::drawFrameEntity(ecs::entity_t ent) {
	auto tr = _mngr->getComponent<Transform>(ent);
	ImageWithFrames* frameComp = _mngr->getComponent<ImageWithFrames>(ent);
	auto rectPos = frameComp->getFrameSrcPos();
	SDL_Rect frame = {rectPos.first, rectPos.second, frameComp->_frameWidth, frameComp->_frameHeight};
	auto tex = frameComp->_tex;
	drawFrame(tr, tex, frame);
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}


void RenderSystem::drawFrame(Transform *tr, Texture *tex, SDL_Rect frame) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(frame, dest, tr->_rot);
}