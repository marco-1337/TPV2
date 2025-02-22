// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "BounceOnBorders.h"
#include "GameInfoMsgs.h"
#include "GameState.h"
#include "Image.h"
// #include "PaddleAICtrl.h"
// #include "PaddleKBCtrl.h"
// #include "PaddleMouseCtrl.h"
#include "RectangleViewer.h"
// #include "StopOnBorders.h"
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

using ecs::Manager;

Game::Game() :
		_mngr(nullptr), //
		_fighterTr(nullptr), //
		_gameState(nullptr) {
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

void Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Asteroids", 800, 600,
			"resources/config/asteroid.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return;

	}
	sdlutils().hideCursor();

	// Create the manager
	_mngr = new Manager();

	// Fighter
	auto fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	_fighterTr = _mngr->addComponent<Transform>(fighter);
	auto fighterSize = 15.0f;
	auto fighterX = (sdlutils().width() - fighterSize) / 2.0f;
	auto fighterY = (sdlutils().height() - fighterSize) / 2.0f;

	_fighterTr->init(Vector2D(fighterX, fighterY), Vector2D(), fighterSize, fighterSize, 0.0f);

	_mngr->addComponent<DeAcceleration>(fighter);
	_mngr->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	_mngr->addComponent<Health>(fighter);
	_mngr->addComponent<FighterCtrl>(fighter);
	_mngr->addComponent<Gun>(fighter);

/*
	_mngr = new Manager();

	// create the ball entity
	//
	auto ball = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::BALL, ball);

	_ballTr = _mngr->addComponent<Transform>(ball);
	auto ballSize = 15.0f;
	auto ballX = (sdlutils().width() - ballSize) / 2.0f;
	auto ballY = (sdlutils().height() - ballSize) / 2.0f;
	_ballTr->init(Vector2D(ballX, ballY), Vector2D(), ballSize, ballSize, 0.0f);

	_mngr->addComponent<Image>(ball, &sdlutils().images().at("tennis_ball"));
	_mngr->addComponent<BounceOnBorders>(ball);

	// create the left paddle
	auto leftPaddle = _mngr->addEntity(ecs::grp::PADDLES);

	auto leftPaddleTr = _mngr->addComponent<Transform>(leftPaddle);
	auto leftPaddleWidth = 10.0f;
	auto leftPaddleHeight = 50.0f;
	auto leftPaddleX = 5.f;
	auto leftPaddleY = (sdlutils().height() - leftPaddleHeight) / 2.0f;
	leftPaddleTr->init(Vector2D(leftPaddleX, leftPaddleY), Vector2D(),
			leftPaddleWidth, leftPaddleHeight, 0.0f);

	_mngr->addComponent<StopOnBorders>(leftPaddle);
	_mngr->addComponent<RectangleViewer>(leftPaddle,
			build_sdlcolor(0xff0000ff));
//	mngr_->addComponent<PaddleKBCtrl>(leftPaddle);
//	mngr_->addComponent<PaddleMouseCtrl>(leftPaddle);
	_mngr->addComponent<PaddleAICtrl>(leftPaddle);

	// create the right paddle
	auto rightPaddle = _mngr->addEntity(ecs::grp::PADDLES);

	auto rightPaddleTr = _mngr->addComponent<Transform>(rightPaddle);
	auto rightPaddleWidth = 10.0f;
	auto rightPaddleHeight = 50.0f;
	auto rightPaddleX = sdlutils().width() - rightPaddleWidth - 5.0f;
	auto rightPaddleY = (sdlutils().height() - rightPaddleHeight) / 2.0f;
	rightPaddleTr->init(Vector2D(rightPaddleX, rightPaddleY), Vector2D(),
			rightPaddleWidth, rightPaddleHeight, 0.0f);

	_mngr->addComponent<StopOnBorders>(rightPaddle);
	_mngr->addComponent<RectangleViewer>(rightPaddle,
			build_sdlcolor(0x00ff00ff));

//	mngr_->addComponent<PaddleKBCtrl>(rightPaddle);
	_mngr->addComponent<PaddleMouseCtrl>(rightPaddle);
//	mngr_->addComponent<PaddleAICtrl>(rightPaddle);

*/
	// create game control entity
	auto gameCtrl = _mngr->addEntity();
	_gameState = _mngr->addComponent<GameState>(gameCtrl);
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

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();
		
		// refresh the input handler
		ihdlr.refresh();
		
		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		
		// AQUI SE JODE TODO
		_mngr->update();
		_mngr->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		_mngr->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
			
	}

}

void Game::checkCollisions() {
	if (_gameState->getState() != GameState::RUNNING)
		return;

/*
	bool ballCollidesWithPaddle = false;

	auto &ballPos = _ballTr->getPos();
	auto ballWidth = _ballTr->getWidth();
	auto ballHeight = _ballTr->getHeight();

	for (auto e : _mngr->getEntities(ecs::grp::PADDLES)) {
		auto paddleTr_ = _mngr->getComponent<Transform>(e);
		ballCollidesWithPaddle = Collisions::collides(paddleTr_->getPos(),
				paddleTr_->getWidth(), paddleTr_->getHeight(), ballPos,
				ballWidth, ballHeight);

		if (ballCollidesWithPaddle)
			break;
	}

	if (ballCollidesWithPaddle) {

		// change the direction of the ball, and increment the speed
		auto &vel = _ballTr->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (_ballTr->getPos().getX() < 0)
		_gameState->onBallExit(GameState::LEFT);
	else if (_ballTr->getPos().getX() + _ballTr->getWidth()
			> sdlutils().width())
		_gameState->onBallExit(GameState::RIGHT);
*/
}
