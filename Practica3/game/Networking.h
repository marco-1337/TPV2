// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "network_messages.h"

class Vector2D;

#include "LittleWolf.h"

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return _clientId;
	}

	bool is_master() {
		return _clientId == _masterId;
	}

	void send_state(const LittleWolf::Point &pos);
	void send_my_info(const LittleWolf::Point &pos,	int health, int score, Uint8 state, std::string name);
	void send_player_new_round(uint8_t id, const LittleWolf::Point &pos);
	
	void send_shoot(LittleWolf::Line fov, float theta);
	void send_hit(uint8_t id);
	void send_score(uint8_t id);
	void send_dead(Uint8 id);
	void send_restart();

private:

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_new_round(const PlayerStateMsg &m);
	void handle_player_info(PlayerInfoMsg &m);
	void handle_shoot(const ShootMsg &m);
	void handle_hit(const MsgWithId &m);
	void handle_dead(const MsgWithId &m);
	void handle_score(const MsgWithId &m);
	void handle_restart();

	UDPsocket _sock;
	SDLNet_SocketSet _socketSet;
	UDPpacket *_p;
	IPaddress _srvadd;
	Uint8 _clientId;
	Uint8 _masterId;
};

