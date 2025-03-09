#include "Follow.h"

#include "Manager.h"
#include "Transform.h"
#include "Game.h"

Follow::Follow() {

}

Follow::~Follow() {

}

void
Follow::initComponent() {
    auto game = Game::Instance();

    _myTr = game->getMngr()->getComponent<Transform>(_ent);
    auto fighter = game->getMngr()->getHandler(ecs::hdlr::FIGHTER);
    _fighterTr = game->getMngr()->getComponent<Transform>(fighter);
}

void
Follow::update() {
    auto& v = _myTr->getVel();
    v = v.rotate(v.angle( _fighterTr->getPos() - _myTr->getPos()) > 0 ? 
                    1.0f : -1.0f);
}