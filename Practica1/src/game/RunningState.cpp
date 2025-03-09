#include "RunningState.h"

#include "Manager.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include "Collisions.h"
#include "Transform.h"
#include "Health.h"
#include "Gun.h"

#include "Game.h"

RunningState::RunningState(FighterUtils* fUtils, AsteroidsUtils* aUtils)
: _fighterUtils(fUtils)
, _asteroidsUtils(aUtils)
, _spawnFrequency(Game::Instance()->config().at("asteroids_spawn_frequency")) 
{
    _mngr = Game::Instance()->getMngr();
}

void
RunningState::enter() {
    _fighter = _mngr->getHandler(ecs::hdlr::FIGHTER);
    _asteroids = &(_mngr->getEntities(ecs::grp::ASTEROIDS));
    _lastSpawnTime = sdlutils().virtualTimer().currTime();
}

void
RunningState::leave() {

}

void
RunningState::update() {
	auto &ihdlr = ih();

    if(ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(Game::PAUSED);
        return;
    }

    if(_asteroids->size() == 0) {
        Game::Instance()->setState(Game::GAMEOVER);
        return;
    }
    
    _mngr->handleInput();

    // UPDATE ENTITIES
    _mngr->update(_fighter);

    for(auto& a : *_asteroids) 
        _mngr->update(a);
   
    // COLLISIONS
    checkCollisions();

    // RENDER ENTITIES
    _mngr->render(_fighter);

    for(auto& a : *_asteroids) 
        _mngr->render(a);
    
    // REFRESH
    _mngr->refresh();

    // ADD ASTEROIDS
    if(sdlutils().virtualTimer().currTime() >= _lastSpawnTime + 5000) {
        _asteroidsUtils->create_asteroids(1);
        _lastSpawnTime = sdlutils().virtualTimer().currTime();
    }
}

void
RunningState::checkCollisions() {
    auto fighterTr = _mngr->getComponent<Transform>(_fighter);

    for(int i = 0; i < _asteroids->size(); ++i) {
        auto aTr = _mngr->getComponent<Transform>(_asteroids->at(i));

        // Si hay colisión entre asteroide y caza
        if(Collisions::collidesWithRotation(
            fighterTr->getPos(), fighterTr->getWidth(), fighterTr->getHeight(), fighterTr->getRot(),
            aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot())) 
        {
            _fighterUtils->update_lives(-1);
            auto fighterHealth = _mngr->getComponent<Health>(_fighter);

            if(fighterHealth->getHealth() > 0) 
                Game::Instance()->setState(Game::NEWROUND);
            else
                Game::Instance()->setState(Game::GAMEOVER);
            break;
        }

        auto it = _mngr->getComponent<Gun>(_fighter)->begin();
        auto it_end = _mngr->getComponent<Gun>(_fighter)->end();

        while(it != it_end) {
            // Si hay colisión entre asteroide y bala
            if(it->used && Collisions::collidesWithRotation(
                            it->pos, it->width, it->height, it->rot,
                            aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot()))
            {
                _asteroidsUtils->split_asteroid(_asteroids->at(i));
                it->used = false;
            }
            ++it;
        }
    }
}