
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
    void resetHealth() { _health = DEFAULT_HEALTH; }

    protected:

    int _health = DEFAULT_HEALTH;

    Vector2D *_pos;
    Texture *_tex;

private:
    static constexpr int DEFAULT_HEALTH = 3;

};