#include "NewRoundState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"

#include "Game.h"

void
NewRoundState::enter() {

}

void
NewRoundState::leave() {

}

void
NewRoundState::update() {
	auto &ihdlr = ih();

    if(ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("start_round");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
    else {
        _fighterUtils->reset_fighter();
        
        _asteroidsUtils->remove_all_asteroids();
        _asteroidsUtils->create_asteroids(10);

        Game::Instance()->setState(Game::RUNNING);
    }
}