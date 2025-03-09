#include "PausedState.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "Game.h"

void
PausedState::enter() {
    sdlutils().virtualTimer().pause();
}

void
PausedState::leave() {
    sdlutils().virtualTimer().resume();
}

void
PausedState::update() {
	auto &ihdlr = ih();

    if(ihdlr.keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
    else {
        auto &t = sdlutils().msgs().at("resume");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}