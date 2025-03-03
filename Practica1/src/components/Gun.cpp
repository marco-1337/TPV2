#include "Gun.h"

#include "Manager.h"
#include "Entity.h"
#include "Transform.h"
#include "InputHandler.h"
#include "SDLUtils.h"
#include "VirtualTimer.h"

#include <iostream>

void 
Gun::initComponent() {
    _tex = &sdlutils().images().at("bullet");
    _tr = _ent->getMngr()->getComponent<Transform>(_ent);
}

void
Gun::handleInput() {
    auto &inhdlr = ih();
    
    if(inhdlr.isKeyDown(SDLK_s) && canShoot) {
        int bw = 5;
        int bh = 20;
        auto p = _tr->getPos();
        auto w = _tr->getWidth();
        auto h = _tr->getHeight();
        auto v = _tr->getVel();
        auto r = _tr->getRot();

        Vector2D c = p + Vector2D(w / 2.0f, h / 2.0f);
        Vector2D bp = c - Vector2D(bw / 2, h / 2.0f + 5.0f + bh).rotate(r) - Vector2D(bw / 2, bh / 2);
        Vector2D bv = Vector2D(0, -1).rotate(r) * (v.magnitude() + 5.0f);
        float br = Vector2D(0, -1).angle(bv);
        shoot(bp, bv, bw, bh, br);
        canShoot = false;

        _lastShootingTime = sdlutils().virtualTimer().currTime();
    }
    if(!canShoot)
        canShoot = sdlutils().virtualTimer().currTime()  >= _lastShootingTime + 250;
}

void 
Gun::render() {
    for(auto b: _bullets) {
        assert(_tex != nullptr);
        if(b.used) {
            auto a = _tex->width();
        
            SDL_Rect dest = build_sdlrect(b.pos, b.width, b.height);
        
            _tex->render(dest, b.rot);
        }
    }
}

void
Gun::update() {
    for(auto& b: _bullets) {
        if(b.used) {
            b.pos = b.pos + b.vel;
            auto p = b.pos;
            if(p.getX() - b.width < 0 || p.getX() > sdlutils().width()
            || p.getY() - b.height < 0 || p.getY() > sdlutils().height())
                b.used = false;
        }
    }
}

void 
Gun::reset() {
    for(auto& b : _bullets)
        b.used = false;
}

void
Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {
    for(auto& b: _bullets) {
        if(!b.used) {
            b.pos = p;
            b.vel = v;
            b.width = width;
            b.height = height;
            b.rot = r;
            b.used = true;
            return;
        }
    }
}

