#include "NewGameState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"


void
NewGameState::enter() {

}

void
NewGameState::leave() {

}

void
NewGameState::update() {
	auto &ihdlr = ih();

    if(!ihdlr.keyDownEvent()) {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("start_game");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
    else {
        // Resetear vidas y posición caza
        _fighter->reset_fighter();
        _fighter->reset_lives();

        // TODO: Cambiar estado a NewRound
        // Game::Instance()->setState(...)
    }

}