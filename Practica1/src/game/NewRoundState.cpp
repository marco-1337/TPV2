#include "NewRoundState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"


void
NewRoundState::enter() {

}

void
NewRoundState::leave() {

}

void
NewRoundState::update() {
	auto &ihdlr = ih();

    if(!ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("start_round");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
    else {
        _fighter->reset_fighter();
        
        _asteroids->remove_all_asteroids();
        _asteroids->create_asteroids(10);

        // TODO: Cambiar estado a RunningState
        // Game::Instance()->setState(...)
    }

}