#include "GameState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/PacManSystem.h"
#include "../ecs/Manager.h"

void
NewRoundState::update() {

    if(ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::Instance()->setState(GameState::RUNNING);
    }
    else {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("newround");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}