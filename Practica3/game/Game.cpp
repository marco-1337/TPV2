// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLNetUtils.h"
#include "LittleWolf.h"
#include "Networking.h"

#include <iostream>

Game::Game() :
		_little_wolf(), //
		_net(nullptr)
{
}

Game::~Game() {

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

	delete _little_wolf;
	delete _net;
}

bool Game::init() {
	return true;
}

bool Game::initGame(const char *map, char *host, Uint16 port) {


	_little_wolf = new LittleWolf();

	// load a map
	_little_wolf->load(map);

	_net = new Networking();

	if (!_net->init(host, port)) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}
	std::cout << "Connected as client " << (int) _net->client_id() << std::endl;

	// initialize the SDL singleton
	if (!SDLUtils::Init("[Little Wolf: " + std::string(map) + "]",
			_little_wolf->get_xres(),
			_little_wolf->get_yres(),
			"resources/config/littlewolf.resources.json")) {

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

	_little_wolf->init(sdlutils().window(), sdlutils().renderer());

	// add some players
	_little_wolf->addPlayer(_net->client_id());
	_little_wolf->send_my_info();

	return true;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.keyDownEvent()) {

			// ESC exists the game
			if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
				exit = true;
				continue;
			}

		}

		if (!_restarting) {
			_little_wolf->update();

			// the clear is not necessary since the texture we copy to the window occupies the whole screen
			// sdlutils().clearRenderer();

			_net->update();
			_little_wolf->render();
		}
		else {
			restart();
		}


		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	_net->disconnect();
	
}

void Game::setRestartTimeStamp(){ 
	_restartTimeStamp = sdlutils().currTime(); 
	_restarting = true;
}

void Game::restart() {

	if (sdlutils().currTime() - _restartTimeStamp >= 5000){
		// To Do: render de numeritos
		Game::Instance()->get_littleWolf().bringAllToLife();
		_restarting = false;

		std::cout << "TO DO: RENDERIZAR CUENTA ATRÁS\n";
	}
}