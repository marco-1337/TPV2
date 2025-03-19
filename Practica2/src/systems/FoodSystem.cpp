#include "FoodSystem.h"

#include "Manager.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "Transform.h"
#include "Miraculous.h"

FoodSystem::FoodSystem() : _fruits() {
}

FoodSystem::~FoodSystem() {

}

void FoodSystem::initSystem() {

    int row = 6, col = 8; // TODO config
    auto width = sdlutils().width();
    auto height = sdlutils().height();

    auto row_h = height / (row * 2);
    auto col_w = width / (col * 2);

    auto pos = Vector2D();

    ecs::entity_t fruit;
    Transform* fruitTr;

    for(int i = 1; i < row * 2; i+=2) {
        for(int j = 1; j < col * 2; j+=2) {

            fruit = _mngr->addEntity(ecs::grp::FRUITS);

            auto x = col_w * j;
            auto y = row_h * i;

            pos = Vector2D(x,y);

            fruitTr = _mngr->addComponent<Transform>(fruit);
            fruitTr->init(pos, Vector2D(), col_w, row_h, 0.f);

            // _mngr->addComponent<FramedImage>(fruit, ...);

            int n = sdlutils().rand().nextInt(0, 10);
            if(!n) {
                n = sdlutils().rand().nextInt(10, 21); // TODO config
                int m = sdlutils().rand().nextInt(5,11);
                _mngr->addComponent<Miraculous>(fruit, n, m);
            }
        }
    }
}

void FoodSystem::update() {
    for(auto& fruit: _mngr->getEntities(ecs::grp::FRUITS)) {
        if(_mngr->hasComponent<Miraculous>(fruit)) {
            
        }
    }
}

