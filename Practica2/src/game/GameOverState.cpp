#include "GameState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/PacManSystem.h"
#include "../ecs/Manager.h"

void
GameOverState::update() {

    if(ih().keyDownEvent()) {
        Game::Instance()->setState(GameState::NEWGAME);
    }
    else {
        // Mostrar mensaje
        gameOvertext->render(
            (sdlutils().width() - gameOvertext->width()) / 2, (sdlutils().height() - gameOvertext->height()) / 2);
    }
}

void
GameOverState::setWin(bool win) {
    if (win) {
        gameOvertext = &sdlutils().msgs().at("gameoverWin");
    }
    else 
        gameOvertext = &sdlutils().msgs().at("gameoverLose");
}