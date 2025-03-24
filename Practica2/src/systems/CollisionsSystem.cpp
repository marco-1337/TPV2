// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

CollisionsSystem::CollisionsSystem() {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	auto &ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto n = ghosts.size();
	for (auto i = 0u; i < n; i++) {
		auto e = ghosts[i];
		if (_mngr->isAlive(e)) {

			auto eTR = _mngr->getComponent<Transform>(e);

			// Check if pacman collides with the ghosts
			if (Collisions::collides(			
					pTR->_pos, pTR->_width, pTR->_height,
					eTR->_pos, eTR->_width, eTR->_height)) {

				Message m;
				m.id = _m_PACMAN_GHOST_COLLISION;
				m.pacman_ghost_collision_data.e = e;
				_mngr->send(m);
			}
		}
	}

	auto &fruits = _mngr->getEntities(ecs::grp::FRUITS);
	n = fruits.size();
	for (auto i = 0u; i < n; i++) {
		auto e = fruits[i];
		if (_mngr->isAlive(e)) {

			auto eTR = _mngr->getComponent<Transform>(e);

			// Check if pacman collides with the ghosts
			if (Collisions::collides(			
					pTR->_pos, pTR->_width, pTR->_height,
					eTR->_pos, eTR->_width, eTR->_height)) {

				Message m;
				m.id = _m_PACMAN_FOOD_COLLISION;
				m.pacman_food_collision_data.e = e;
				_mngr->send(m);
			}
		}
	}

}

