#include "NewGameState.h"

#include "Manager.h"
#include "SDLUtils.h"
#include "InputHandler.h"
#include "FighterUtils.h"

#include "Game.h"

void
NewGameState::enter() {

}

void
NewGameState::leave() {

}

void
NewGameState::update() {
	auto &ihdlr = ih();

    if(ihdlr.keyDownEvent()) {
        // Resetear vidas y posición caza
        _fighterUtils->reset_lives();

        Game::Instance()->setState(Game::NEWROUND);
    }
    else {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("start_game");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }

}