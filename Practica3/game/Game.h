// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>

#include "../utils/Singleton.h"

class LittleWolf;
class Networking;

class Game : public Singleton<Game> {
	friend Singleton<Game> ;
	Game();
public:
	virtual ~Game();
	bool initGame(const char *map, char *host, Uint16 port);
	void start();

	inline LittleWolf& get_littleWolf() { return *_little_wolf; }
	inline Networking& get_networking() { return *_net; }

	void setRestartTimeStamp();

private:
	bool init();
	
	LittleWolf *_little_wolf;
	Networking *_net;

	bool _restarting = false;
	void restart();

	Uint32 _restartTimeStamp;
};

