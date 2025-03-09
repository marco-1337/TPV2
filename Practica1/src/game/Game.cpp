// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "BounceOnBorders.h"
#include "GameInfoMsgs.h"
#include "GameState.h"
#include "Image.h"
#include "RectangleViewer.h"
#include "ShowAtOppositeSide.h"
#include "Transform.h"
#include "Manager.h"
#include "InputHandler.h"
#include "SDLUtils.h"
#include "Vector2D.h"
#include "Collisions.h"

#include "DeAcceleration.h"
#include "Health.h"
#include "FighterCtrl.h"
#include "Gun.h"

#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "PausedState.h"
#include "GameOverState.h"

#include "FighterUtils.h"
#include "AsteroidsUtils.h"

using ecs::Manager;

Game::Game() :
		_mngr(nullptr), //
		_state(nullptr) {
}

Game::~Game() {
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
	if (!SDLUtils::Init("Asteroids", 800, 600,
			"resources/config/asteroid.resources.json")) {

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

void Game::initGame(){

	sdlutils().hideCursor();

	// Create the manager
	_mngr = new Manager();

	_newgameState = new NewGameState();
	_newroundState = new NewRoundState();
	_runningState = new RunningState();
	_pausedState = new PausedState();
	_gameoverState = new GameOverState();

	// Fighter
	_fighterUtils = new FighterUtils();
	_fighterUtils->create_fighter();

	// Asteroids Utils
	_asteroidUtils = new AsteroidsUtils();

	// create game control entity
	auto gameCtrl = _mngr->addEntity();
	//_gameState = _mngr->addComponent<GameState>(gameCtrl);
	_mngr->addComponent<GameInfoMsgs>(gameCtrl);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	// reset the time before starting - so we calculate correct
	// delta-time in the first iteration
	//
	sdlutils().resetTime();
	sdlutils().virtualTimer().resetTime();

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();
		sdlutils().virtualTimer().regCurrTime();


		// refresh the input handler
		ihdlr.refresh();
		
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		
		_state->update();

		sdlutils().clearRenderer();
		_mngr->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
			
	}

}

void
Game::setState(State s)
{
	_state->leave();

		switch (s) {
			case RUNNING:
				_state = _runningState;
				break;
			case PAUSED:
				_state = _pausedState;
				break;
			case NEWGAME:
				_state = _newgameState;
				break;
			case NEWROUND:
				_state = _newroundState;
				break;
			case GAMEOVER:
				_state = _gameoverState;
				break;
			default:
				break;
		}
	_state->enter();
}