// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <__mutex_base>
#include <array>

#include "../ecs/System.h"

struct GameState;

class GameCtrlSystem: public ecs::System {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};

	enum State {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	void update() override;

	inline State getState() {
		return _state;
	}

	inline unsigned int getScore(std::size_t player) {
		return _score[player];
	}

	void onBallExit(Side side);
	void resetBall();
	void moveBall();

private:

	std::array<unsigned int, 2> _score;
	State _state;
	const unsigned int _maxScore;

};

