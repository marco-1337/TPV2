#include "FighterUtils.h"

#include "Manager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "DeAcceleration.h"
#include "Image.h"
#include "Health.h"
#include "FighterCtrl.h"
#include "Gun.h"
#include "ShowAtOppositeSide.h"

#include "Game.h"

#include "ecs_defs.h"

#include "SDLUtils.h"

FighterUtils::FighterUtils()
{
	_mngr = Game::Instance()->getMngr();
}

void FighterUtils::create_fighter()
{
    auto fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	auto fighterTr = _mngr->addComponent<Transform>(fighter);
	auto fighterX = (sdlutils().width() - FIGHTER_SIZE) / 2.0f;
	auto fighterY = (sdlutils().height() - FIGHTER_SIZE) / 2.0f;

	fighterTr->init(Vector2D(fighterX, fighterY), Vector2D(), FIGHTER_SIZE, FIGHTER_SIZE, 0.0f);

	_mngr->addComponent<DeAcceleration>(fighter, fighterTr);
	_mngr->addComponent<Health>(fighter);
	_mngr->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	_mngr->addComponent<FighterCtrl>(fighter);
	_mngr->addComponent<Gun>(fighter);
	_mngr->addComponent<ShowAtOppositeSide>(fighter);
}

void FighterUtils::reset_fighter()
{
	Transform* fighterTransform = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::FIGHTER));
    Vector2D& fighterTrPos = fighterTransform->getPos();

	fighterTransform->getPos() = {
		(sdlutils().width() - FIGHTER_SIZE) / 2.0f, 
		(sdlutils().height() - FIGHTER_SIZE) / 2.0f
		};
	fighterTransform->getVel() = {0, 0};
	fighterTransform->setRot(0.);

    _mngr->getComponent<Gun>(_mngr->getHandler(ecs::hdlr::FIGHTER))->reset();
}

void FighterUtils::reset_lives()
{
    _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::FIGHTER))->resetHealth();
}

int FighterUtils::update_lives(int n)
{
    auto healthComp = _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::FIGHTER));

    healthComp->setHealth(healthComp->getHealth() + n);

    return healthComp->getHealth();
}
