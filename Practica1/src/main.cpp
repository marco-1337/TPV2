// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "game/Game.h"

int main(int, char**) {

	try {
		bool init = Game::Init("resources/config/asteroid.config.json");
		assert(init == true);
		Game::Instance()->initGame();
		Game::Instance()->start();
	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	Game::Instance()->Release();

	return 0;
}

