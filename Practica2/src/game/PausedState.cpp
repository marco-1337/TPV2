#include "GameState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/PacManSystem.h"
#include "../ecs/Manager.h"

void
PausedState::update() {

    if(ih().keyDownEvent()) {
        Game::Instance()->setState(GameState::RUNNING);
    }
    else {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("paused");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}