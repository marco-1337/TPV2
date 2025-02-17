
#pragma once
#include "Component.h"
#include "Image.h"
#include "Vector2D.h"
#include "Texture.h"

#include <algorithm>

class Health : public ecs::Component {
public:
	Health();
	virtual ~Health();

    void initComponent() override;
    void render() override;

    int getHealth() const { return _health; }
    void removeHealthPoint() { if (_health > 0) --_health; }
    void resetHealth() { _health = 3; }

    protected:

    int _health = 3;

    Vector2D *_pos;
    Texture *_tex;

};