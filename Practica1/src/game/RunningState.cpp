#include "RunningState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"


void
RunningState::enter() {

}

void
RunningState::leave() {

}

void
RunningState::update() {
    auto& a = _mgr->getEntities(ecs::grp::ASTEROIDS);

    if(a.size() == 0) {
        // TODO: Cambiar estado a GameOverState
        // Game::Instance()->setState(...)
        return;
    }

	auto &ihdlr = ih();

    if(ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        // TODO: Cambiar estado a Pause
        // Game::Instance()->setState(...)
        return;
    }
    
    auto fighter = _mgr->getHandler(ecs::hdlr::FIGHTER);
    _mgr->update(fighter);
    
    auto asteroids = _mgr->getEntities(ecs::grp::ASTEROIDS);
    for(auto& a:asteroids)
        _mgr->update(a);



}