#include "GameState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/PacManSystem.h"
#include "../ecs/Manager.h"

void
NewGameState::update() {

    if(ih().keyDownEvent()) {
        Message m;
        m.id = _m_NEW_GAME;
        Game::Instance()->getManager()->send(m);

        Game::Instance()->setState(GameState::NEWROUND);
    }
    else {
        // Mostrar mensaje
        auto &t = sdlutils().msgs().at("newgame");
        t.render((sdlutils().width() - t.width()) / 2, (sdlutils().height() - t.height()) / 2);
    }
}