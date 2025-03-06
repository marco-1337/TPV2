#include "RunningState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include "Collisions.h"
#include "Transform.h"
#include "Health.h"


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

    auto& asteroids = _mgr->getEntities(ecs::grp::ASTEROIDS);

    if(asteroids.size() == 0) {
        // TODO: Cambiar estado a GameOverState
        // Game::Instance()->setState(...)
        return;
    }
    
    auto fighter = _mgr->getHandler(ecs::hdlr::FIGHTER);
    _mgr->update(fighter);
    
    for(auto& a:asteroids) 
        _mgr->update(a);
    


        
    checkCollisions();


}


void
RunningState::checkCollisions() {
    auto fighterTr = _mgr->getComponent<Transform>(_mgr->getHandler(ecs::hdlr::FIGHTER));
    auto& asteroids = _mgr->getEntities(ecs::grp::ASTEROIDS);

    for(int i = 0; i < asteroids.size(); ++i) {
        auto aTr = _mgr->getComponent<Transform>(asteroids[i]);

        bool hasCollided = Collisions::collidesWithRotation(
            fighterTr->getPos(), fighterTr->getWidth(), fighterTr->getHeight(), fighterTr->getRot(),
            aTr->getPos(), aTr->getWidth(), aTr->getHeight(), aTr->getRot()
        );

        if(hasCollided) {
            _fighterUtils->update_lives(-1);
            auto fighterHealth = _mgr->getComponent<Health>(_mgr->getHandler(ecs::hdlr::FIGHTER));

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
    }
}