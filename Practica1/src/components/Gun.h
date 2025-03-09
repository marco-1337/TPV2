#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "SDL.h"
#include "SoundEffect.h"

#include <array>

class Texture;
class Transform;

class Gun: public ecs::Component {
public:
    __CMPID_DECL__(ecs::cmp::GUN)

    void initComponent() override;
	void handleInput() override;
	void render() override;
	void update() override;


    struct Bullet {
        bool used = false;
        Vector2D pos;
        Vector2D vel;
        int width;
        int height;
        float rot;
    };
    constexpr static uint8_t _max_bullets = 20;

    typedef std::array<Bullet, _max_bullets> bullets_array_t;
    typedef bullets_array_t::iterator iterator;

    void reset();

    iterator begin() {
        return _bullets.begin();
    }
    iterator end() {
        return _bullets.end();
    }

private:
    void shoot(Vector2D p, Vector2D v, int width, int height, float r);
    bullets_array_t _bullets;
    Texture* _tex = nullptr;
    Transform* _tr = nullptr;
    Uint32 _lastShootingTime;
    bool canShoot = true;

	SoundEffect* _shootEffect = nullptr;
};