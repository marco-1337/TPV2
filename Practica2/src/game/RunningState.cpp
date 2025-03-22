#include "GameState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/PacManSystem.h"
#include "../ecs/Manager.h"

RunningState::RunningState(ecs::System* pacmanSys, ecs::System* ghostSys, ecs::System* foodSys,
		ecs::System* immunitySys, ecs::System* renderSys, ecs::System* collisionSys): 
    _pacmanSys(pacmanSys),
    _ghostSys(ghostSys),
    _foodSys(foodSys),
    _immunitySys(immunitySys),
    _renderSys(renderSys),
    _collisionSys(collisionSys) {}

void
RunningState::update() {

    if(ih().isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(GameState::PAUSED);
    }
    else {
        _pacmanSys->update();
        _ghostSys->update();
        _foodSys->update();
        _immunitySys->update();
        _renderSys->update();
        _collisionSys->update();
    }
}