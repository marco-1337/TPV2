#include "PausedState.h"

#include "SDLUtils.h"
#include "InputHandler.h"

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
        // TODO: cambiar a RunningState
        // Game::Instance()->setState(...)
    }
    else {
        auto &t = sdlutils().msgs().at("resume");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}