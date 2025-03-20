// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Immunity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"


GhostSystem::GhostSystem() :
    _ghosts(nullptr),
    _vt(nullptr) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {

    _ghosts = &(_mngr->getEntities(ecs::grp::GHOSTS));
    _vt = &(sdlutils().virtualTimer());

    ecs::entity_t pacman = _mngr->getHandler(ecs::hdlr::PACMAN);

    _pacmanTransform = _mngr->getComponent<Transform>(pacman);
    _pacmanInmunity = _mngr->getComponent<Immunity>(pacman);
}

void GhostSystem::update() {

    tryAddGhost();
}

void GhostSystem::tryAddGhost() {
    if (_ghosts->size() < 11 && !_pacmanInmunity->_immune) {
        if (_vt->currTime() - _lastSpawnStamp >= 5000) {
            
            _lastSpawnStamp = _vt->currTime();

            ecs::entity_t ghost = _mngr->addEntity(ecs::grp::GHOSTS);

            auto gTr = _mngr->addComponent<Transform>(ghost);
            auto s = 30.0f;
            auto x = (sdlutils().width() - s) * sdlutils().rand().nextInt(0, 2);
            auto y = (sdlutils().height() - s) * sdlutils().rand().nextInt(0, 2);
            gTr->init(Vector2D(x, y), _pacmanTransform->_pos - Vector2D(x, y), s, s, 0.0f);
            _mngr->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman_sprites"), 8, 8, 32);
        }
    }
}