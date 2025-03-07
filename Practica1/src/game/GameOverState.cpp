#include "GameOverState.h"

#include "Manager.h"
#include "InputHandler.h"
#include "SDLUtils.h"

void
GameOverState::enter() {
    (_mgr->getEntities(ecs::grp::ASTEROIDS).size() > 0) 
    ? _msg = "gameover" 
    : _msg = "win";
}

void
GameOverState::leave() {

}

void
GameOverState::update() {
	auto &ihdlr = ih();

    if(ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
        // TODO: cambiar a NewGameState
        // Game::Instance()->setState(...)
    }
    else {
        auto &t = sdlutils().msgs().at(_msg);
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}