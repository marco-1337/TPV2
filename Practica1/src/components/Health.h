
#pragma once
#include "Component.h"
#include "Image.h"
#include "Vector2D.h"
#include "Texture.h"

#include <algorithm>

class Health : public ecs::Component {
public:
    __CMPID_DECL__(ecs::cmp::HEALTH)

	Health();
	virtual ~Health();

    void initComponent() override;
    void render() override;

    int getHealth() const { return _health; }
    void setHealth(int n) { _health = n; }
    void resetHealth();

    protected:

    int _health;

    Vector2D *_pos;
    Texture *_tex;
};