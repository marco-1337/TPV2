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

RunningState::RunningState(ecs::Manager* mgr) : GameState(mgr) {
    _fighter = _mgr->getHandler(ecs::hdlr::FIGHTER);
    _asteroids = _mgr->getEntities(ecs::grp::ASTEROIDS);
    _lastSpawnTime = sdlutils().virtualTimer().currTime();
}

void
RunningState::enter() {

}

void
RunningState::leave() {

}

void
RunningState::update() {
	auto &ihdlr = ih();

    if(ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        // TODO: Cambiar estado a Pause
        // Game::Instance()->setState(...)
        return;
    }

    if(_asteroids.size() == 0) {
        // TODO: Cambiar estado a GameOverState
        // Game::Instance()->setState(...)
        return;
    }
    
    // UPDATE ENTITIES
    _mgr->update(_fighter);

    for(auto& a : _asteroids) 
        _mgr->update(a);
    
   
    // COLLISIONS
    checkCollisions();


    // RENDER ENTITIES
    _mgr->render(_fighter);

    for(auto& a : _asteroids) 
        _mgr->render(a);

    
    // REFRESH
    _mgr->refresh();


    // ADD ASTEROIDS
    if(sdlutils().virtualTimer().currTime() >= _lastSpawnTime + 5000) {
        _asteroidsUtils->create_asteroids(1);
        _lastSpawnTime = sdlutils().virtualTimer().currTime();
    }
}


void
RunningState::checkCollisions() {
    auto fighterTr = _mgr->getComponent<Transform>(_fighter);

    for(int i = 0; i < _asteroids.size(); ++i) {
        auto aTr = _mgr->getComponent<Transform>(_asteroids[i]);

        // Si hay colisión entre asteroide y caza
        if(Collisions::collidesWithRotation(
            fighterTr->getPos(), fighterTr->getWidth(), fighterTr->getHeight(), fighterTr->getRot(),
            aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot())) 
        {
            _fighterUtils->update_lives(-1);
            auto fighterHealth = _mgr->getComponent<Health>(_fighter);

            if(fighterHealth->getHealth() > 0) {
                // TODO: Cambiar estado a NewRoundState
                // Game::Instance()->setState(...)
            }
            else  {
                // TODO: Cambiar estado a GameOverState
                // Game::Instance()->setState(...)
            }

            break;
        }


        auto it = _mgr->getComponent<Gun>(_fighter)->begin();
        auto it_end = _mgr->getComponent<Gun>(_fighter)->end();

        while(it != it_end) {
            // Si hay colisión entre asteroide y bala
            if(it->used && Collisions::collidesWithRotation(
                            it->pos, it->width, it->height, it->rot,
                            aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot()))
            {
                _asteroidsUtils->split_asteroid(_asteroids[i]);
                it->used = false;
            }
            ++it;
        }
    }
}