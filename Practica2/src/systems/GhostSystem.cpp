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

    _lastSpawnStamp = _vt->currTime();

    _changeEnabled = false;
}

void GhostSystem::update() {

    if (!_pacmanInmunity) {
        tryAddGhost();
    }

    ecs::entity_t gEnt;
    Transform* gTr;
    int frame;

    if (_changeEnabled) {
        if (_pacmanInmunity) frame = 30;
        else frame = 32;
    }

    for (int i = 0; i < _ghosts->size(); ++i) {

        gEnt = _ghosts->at(i);

        if (_mngr->isAlive(gEnt)) {
            gTr = _mngr->getComponent<Transform>(gEnt);
            updateDirection(gTr);
            moveGhosts(gTr);

            if (_changeEnabled) {
                _mngr->getComponent<ImageWithFrames>(gEnt)->setFrame(frame);
            }
        }
    }

    _changeEnabled = false;
    
}

void
GhostSystem::updateDirection(Transform*& gTr) {
    if (sdlutils().rand().nextInt(0, 1001) <= 5) {
        gTr->_vel = (_pacmanTransform->_pos - gTr->_pos).normalize() * GHOST_SPEED;
    }
}

void 
GhostSystem::tryAddGhost() {
    if (_ghosts->size() < 11) {
        if (_vt->currTime() - _lastSpawnStamp >= 5000) {
            
            _lastSpawnStamp = _vt->currTime();

            ecs::entity_t ghost = _mngr->addEntity(ecs::grp::GHOSTS);

            auto gTr = _mngr->addComponent<Transform>(ghost);
            auto s = 30.0f;
            // Aparecer en esquina random
            auto x = (sdlutils().width() - s) * sdlutils().rand().nextInt(0, 2);
            auto y = (sdlutils().height() - s) * sdlutils().rand().nextInt(0, 2);
            gTr->init(Vector2D(x, y), (_pacmanTransform->_pos - Vector2D(x, y)).normalize() * GHOST_SPEED, s, s, 0.0f);
            _mngr->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman_sprites"), 8, 8, 32);
        }
    }
}

void
GhostSystem::moveGhosts(Transform*& gTr) {

    gTr->_pos = gTr->_pos + gTr->_vel;

    // check left/right borders
    if (gTr->_pos.getX() < 0) {
        gTr->_pos.setX(0.0f);
        gTr->_vel.set(-gTr->_pos.getX(), gTr->_pos.getY());
    } else if (gTr->_pos.getX() + gTr->_width > sdlutils().width()) {
        gTr->_pos.setX(sdlutils().width() - gTr->_width);
        gTr->_vel.set(-gTr->_pos.getX(), gTr->_pos.getY());
    }

    // check upper/lower borders
    if (gTr->_pos.getY() < 0) {
        gTr->_pos.setY(0.0f);
        gTr->_vel.set(gTr->_pos.getX(), -gTr->_pos.getY());
    } else if (gTr->_pos.getY() + gTr->_height > sdlutils().height()) {
        gTr->_pos.setY(sdlutils().height() - gTr->_height);
        gTr->_vel.set(gTr->_pos.getX(), -gTr->_pos.getY());
    }
}

void 
GhostSystem::receive(const Message &m) {
    switch (m.id) {
        case _m_PACMAN_GHOST_COLLISION:
            pacmanHitsGhost(m.pacman_ghost_collision_data.e);
            break;
        case _m_IMMUNITY_START:
            _pacmanInmunity = true;
            _changeEnabled = true;
            break;
        case _m_IMMUNITY_END:
            _pacmanInmunity = false;
            _changeEnabled = true;
            break;
        default:
            break;
    }
}

void
GhostSystem::pacmanHitsGhost(ecs::entity_t e) {
    if(_pacmanInmunity) _mngr->setAlive(e, false);
}