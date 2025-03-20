// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/StarsSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "GameState.h"

using ecs::Manager;

Game::Game() :
		_mngr(), //
		//_state(), //
		_pacmanSys(), //
		_gameCtrlSys(), //
		_startsSys(), //
		_renderSys(), //
		_collisionSys() {
}

Game::~Game() {
	delete _mngr;

	/*
	delete _pausedState;
	delete _runningState;
	delete _newgameState;
	delete _newroundState;
	delete _gameoverState;
	*/

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan 2", 800, 600,
			"resources/config/resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;
	}

	return true;
}

void Game::initGame() {

	// Create the manager
	_mngr = new Manager();

	// add the systems
	_pacmanSys = _mngr->addSystem<PacManSystem>();
	_startsSys = _mngr->addSystem<StarsSystem>();
	_gameCtrlSys = _mngr->addSystem<GameCtrlSystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();
	_collisionSys = _mngr->addSystem<CollisionsSystem>();

	std::cout << "[Game.cpp | initGame()] TO DO: Inicializar todos los estados \n";
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	auto &vt = sdlutils().virtualTimer();
	vt.resetTime();

	while (!exit) {
		Uint32 startTime = vt.currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		_pacmanSys->update();
		_startsSys->update();
		_gameCtrlSys->update();
		_collisionSys->update();

		_mngr->refresh();

		sdlutils().clearRenderer();
		_renderSys->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = vt.currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}