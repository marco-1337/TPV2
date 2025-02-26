#include "Follow.h"

#include "Manager.h"
#include "Transform.h"


Follow::Follow() {

}

Follow::~Follow() {

}

void
Follow::initComponent() {
    _myTr = _ent->getMngr()->getComponent<Transform>(_ent);
    auto fighter = _ent->getMngr()->getHandler(ecs::hdlr::FIGHTER);
    _fighterTr = _ent->getMngr()->getComponent<Transform>(fighter);
}

void
Follow::update() {
    auto& v = _myTr->getVel();
    v = v.rotate(v.angle( _fighterTr->getPos() - _myTr->getPos()) > 0 ? 
                    1.0f : -1.0f);
}