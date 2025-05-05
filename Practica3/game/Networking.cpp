// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"
#include "network_messages.h"
#include <iostream>

#include "../sdlutils/SDLNetUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
#include "LittleWolf.h"


Networking::Networking() :
		_sock(), //
		_socketSet(), //
		_p(), //
		_srvadd(), //
		_clientId(), //
		_masterId() {
}

Networking::~Networking() {
}

bool Networking::init(char *host, Uint16 port) {

	if (SDLNet_ResolveHost(&_srvadd, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_sock = SDLNet_UDP_Open(0);
	if (!_sock) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_p = SDLNet_AllocPacket(512);
	if (!_p) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	_socketSet = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(_socketSet, _sock);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, _p, _sock, _srvadd);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(_socketSet, 3000) > 0) {
		if (SDLNet_SocketReady(_sock)) {
			if (SDLNetUtils::deserializedReceive(m0, _p, _sock) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(_p->data);
					_clientId = m1._client_id;
					_masterId = m1._master_id;
					std::cout << ">> " << (int) _masterId << std::endl;
					std::cout << ">> " << (int) _clientId << std::endl;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int) _clientId << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = _clientId;
	return (SDLNetUtils::serializedSend(m, _p, _sock, _srvadd) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	MsgWithId m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, _p, _sock) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			m1.deserialize(_p->data);
			_masterId = m1._master_id;
			handle_new_client(m1._client_id);
			break;

		case _DISCONNECTED:
			m1.deserialize(_p->data);
			_masterId = m1._master_id;
			handle_disconnet(m1._client_id);
			break;

		case _PLAYER_STATE:
			m2.deserialize(_p->data);
			handle_player_state(m2);
			break;
		
		case _CORRECT_POSITION:
			m2.deserialize(_p->data);
			handle_correct_position(m2);
			break;

		case _PLAYER_NEWROUND:
			m2.deserialize(_p->data);
			handle_player_new_round(m2);
			break;

		case _PLAYER_INFO:
			m5.deserialize(_p->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			m3.deserialize(_p->data);
			handle_shoot(m3);
			break;

		case _HIT:
			m4.deserialize(_p->data);
			handle_hit(m4);
			break;

		case _DEAD:
			m4.deserialize(_p->data);
			handle_dead(m4);
			break;

		case _SCORE:
			m4.deserialize(_p->data);
			handle_score(m4);
			break;

		case _RESTART:
			handle_restart();
			break;

		default:
			break;
		}
	}
}

void Networking::handle_new_client(Uint8 id) {
	if (id != _clientId)
	 	Game::Instance()->get_littleWolf().send_my_info();
}

void Networking::handle_disconnet(Uint8 id) {
	Game::Instance()->get_littleWolf().removePlayer(id);
}

void Networking::send_state(const LittleWolf::Point &pos) {
	PlayerStateMsg m;
	m._type = _PLAYER_STATE;
	m._client_id = _clientId;
	m.x = pos.x;
	m.y = pos.y;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::send_correct_position(uint8_t id, const LittleWolf::Point &pos) {
	PlayerStateMsg m;
	m._type = _CORRECT_POSITION;
	m._client_id = id;
	m.x = pos.x;
	m.y = pos.y;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::send_player_new_round(uint8_t id, const LittleWolf::Point &pos) {
	PlayerStateMsg m;
	m._type = _PLAYER_NEWROUND;
	m._client_id = id;
	m.x = pos.x;
	m.y = pos.y;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_player_state(const PlayerStateMsg &m) {

	Game::Instance()->get_littleWolf().update_player_state(m._client_id, m.x, m.y);
}

void Networking::handle_correct_position(const PlayerStateMsg &m) {

	Game::Instance()->get_littleWolf().update_player_pos(m._client_id, m.x, m.y);
}

void Networking::handle_player_new_round(const PlayerStateMsg &m) {
	Game::Instance()->get_littleWolf().new_round_player_state(m._client_id, m.x, m.y);
}

void Networking::send_shoot(LittleWolf::Line fov, float theta) {
	ShootMsg m;
	m._type = _SHOOT;
	m._client_id = _clientId;
	m.fov_a_x = fov.a.x;
	m.fov_a_y = fov.a.y;
	m.fov_b_x = fov.b.x;
	m.fov_b_y = fov.b.y;
	m.theta = theta;

	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_shoot(const ShootMsg &m) {

	Game::Instance()->get_littleWolf().playSFX(sdlutils().soundEffects().at("gunshot"), m._client_id);
	
	// Solo se gestionan los disparos si eres el master
	if (Game::Instance()->get_networking().is_master()) {

		LittleWolf::Line a_fov = {{m.fov_a_x, m.fov_a_y}, {m.fov_b_x, m.fov_b_y}};

		Game::Instance()->get_littleWolf().shoot(m._client_id, a_fov, m.theta);
	}

}

void Networking::send_dead(Uint8 id) {
	MsgWithId m;
	m._type = _DEAD;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::send_score(uint8_t id) {
	MsgWithId m;
	m._type = _SCORE;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::send_hit(uint8_t id) {
	MsgWithId m;
	m._type = _HIT;
	m._client_id = id;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_hit(const MsgWithId &m) {
	Game::Instance()->get_littleWolf().damagePlayer(m._client_id);
}

void Networking::handle_dead(const MsgWithId &m) {
	Game::Instance()->get_littleWolf().playSFX(sdlutils().soundEffects().at("pain"), m._client_id);

	Game::Instance()->get_littleWolf().killPlayer(m._client_id);
}

void Networking::handle_score(const MsgWithId &m) {
	Game::Instance()->get_littleWolf().scorePlayer(m._client_id);
}

void string_to_chars(std::string &str, char c_str[11]) { 
  auto i = 0u; 
  for (; i < str.size() && i < 10; i++) c_str[i] = str[i]; 
  c_str[i] = 0; 
}

void chars_to_string(std::string &str, char c_str[11]) { 
  c_str[10] = 0; 
  str = std::string(c_str); 
}


void Networking::send_my_info(const LittleWolf::Point &pos, int health, int score, Uint8 state, std::string name) {

	PlayerInfoMsg m;
	m._type = _PLAYER_INFO;
	m._client_id = _clientId;
	m.x = pos.x;
	m.y = pos.y;
	m.health = health;
	m.score = score;
	m.state = state;
	string_to_chars(name, m.name);
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_player_info(PlayerInfoMsg &m) {
	
	std::string name;
	chars_to_string(name, m.name);

	Game::Instance()->get_littleWolf().update_player_info(m._client_id, m.x, m.y, m.health, m.state, m.name);
}

void Networking::send_restart() {
	Msg m;
	m._type = _RESTART;
	SDLNetUtils::serializedSend(m, _p, _sock, _srvadd);
}

void Networking::handle_restart() {
	Game::Instance()->setRestartTimeStamp();
}