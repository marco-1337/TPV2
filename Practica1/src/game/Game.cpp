// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "JSON.h"

#include "GameState.h"
#include "Image.h"
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
		_configAccessWrapper(_config, "Config Table"),
		_mngr(nullptr), 
		_state(nullptr) {
}

Game::~Game() {
	delete _mngr;

	delete _fighterUtils;
	delete _asteroidUtils;
	delete _pausedState;
	delete _runningState;
	delete _newgameState;
	delete _newroundState;
	delete _gameoverState;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init(std::string filename) {

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

	loadResources(filename);

	return true;
}

void Game::loadResources(std::string filename) {
	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue *jValue = root["config"];

	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_config.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					float value = static_cast<float>(vObj["value"]->AsNumber());
					_config.emplace(key, value);
				} else {
					throw "'config' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'config' is not an array in '" + filename + "'";
		}
	}
}


void Game::initGame(){

	sdlutils().hideCursor();

	// Create the manager
	_mngr = new Manager();

	// Fighter
	_fighterUtils = new FighterUtils();
	_fighterUtils->create_fighter();

	// Asteroids Utils
	_asteroidUtils = new AsteroidsUtils();

	_newgameState = new NewGameState(_fighterUtils);
	_newroundState = new NewRoundState(_fighterUtils, _asteroidUtils);
	_runningState = new RunningState(_fighterUtils, _asteroidUtils);
	_pausedState = new PausedState();
	_gameoverState = new GameOverState();

	_state = _newgameState;
	_state->enter();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	// reset the time before starting - so we calculate correct
	// delta-time in the first iteration
	//

	auto &vt = sdlutils().virtualTimer();
	vt.resetTime();

	while (!exit) {
		Uint32 startTime = vt.regCurrTime();

		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		sdlutils().clearRenderer();
		
		_state->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = vt.currRealTime() - startTime;
		if (frameTime < 10) SDL_Delay(10 - frameTime);
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