// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "GameState.h"

using ecs::Manager;

Game::Game() :
		_mngr(), //
		_currentState(), //
		_pacmanSys(), //
		_ghostSys(), //
		_foodSys(), //
		_immunitySys(), //
		_renderSys(), //
		_collisionSys() {
}

Game::~Game() {

	delete _gameoverState;
	delete _newroundState;
	delete _newgameState;
	delete _runningState;
	delete _pausedState;

	delete _mngr;

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
	_ghostSys = _mngr->addSystem<GhostSystem>();
	_foodSys = _mngr->addSystem<FoodSystem>();
	_immunitySys = _mngr->addSystem<ImmunitySystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();
	_collisionSys = _mngr->addSystem<CollisionsSystem>();

	_pausedState = new PausedState();
	_runningState = new RunningState(_pacmanSys, _ghostSys, _foodSys, _immunitySys, _renderSys, _collisionSys);
	_newgameState = new NewGameState();
	_newroundState = new NewRoundState();
	_gameoverState = new GameOverState();

	_currentState = _newgameState;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	auto &vt = sdlutils().virtualTimer();
	vt.resetTime();

	// no hace falta, lo hace addSystem
	_pacmanSys->initSystem();
	_ghostSys->initSystem();
	_foodSys->initSystem();
	_immunitySys->initSystem();
	_renderSys->initSystem();
	_collisionSys->initSystem();

	while (!exit) {
		Uint32 startTime = vt.regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		_currentState->update();

		_mngr->refresh();

		sdlutils().presentRenderer();
		sdlutils().clearRenderer();

		Uint32 frameTime = vt.currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void 
Game::setState(GameState::StateID state) {

	switch (state)
	{
	case GameState::PAUSED:
		_currentState = _pausedState;
		break;
	case GameState::RUNNING:
		_currentState = _runningState;
		break;
	case GameState::NEWGAME:
		_currentState = _newgameState;
		break;
	case GameState::NEWROUND:
		_currentState = _newroundState;
		break;
	case GameState::GAMEOVER_LOSE:
		_gameoverState->setWin(false);
		_currentState = _gameoverState;
		break;
	case GameState::GAMEOVER_WIN:
		_gameoverState->setWin(true);
		_currentState = _gameoverState;
		break;
	default:
		break;
	}
}