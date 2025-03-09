#include "GameOverState.h"

#include "Manager.h"
#include "InputHandler.h"
#include "SDLUtils.h"

#include "Game.h"

void
GameOverState::enter() {
    (Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size() > 0) 
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
        Game::Instance()->setState(Game::NEWGAME);
    }
    else {
        auto &t = sdlutils().msgs().at(_msg);
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}