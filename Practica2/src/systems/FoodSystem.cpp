#include "FoodSystem.h"

#include "Manager.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "Transform.h"
#include "Miraculous.h"
#include "ImageWithFrames.h"

FoodSystem::FoodSystem() : _fruits() {
}

FoodSystem::~FoodSystem() {

}

void FoodSystem::initSystem() {

}

void FoodSystem::update() {

    auto currTime = sdlutils().virtualTimer().currRealTime();

    auto fruits = _mngr->getEntities(ecs::grp::FRUITS);

    if(fruits.size() == 0) {
        Message m;
        m.id = _m_GAME_OVER;
        m.game_over_data.victory = true;
        _mngr->send(m);
    }
    else {
        for(auto& fruit: fruits) {
    
            // Update miraculous fruits if necessary
            if(_mngr->hasComponent<Miraculous>(fruit)) {
                auto miraculous = _mngr->getComponent<Miraculous>(fruit);
    
                if(miraculous->shouldUpdate(currTime)) {
                    miraculous->_miraculousState = !miraculous->_miraculousState;
                    auto texture = _mngr->getComponent<ImageWithFrames>(fruit);
    
                    if(miraculous->_miraculousState)
                        texture->setFrame(15);
                    else texture->setFrame(12);
                }
            }
        }
    }
}


void FoodSystem::receive(const Message &m) {
    switch(m.id) {
    case _m_PACMAN_FOOD_COLLISION: 
        onFruitEaten(m.pacman_food_collision_data.e);
        break;
    case _m_ROUND_START:
        createFruits();
        break;
    default:
        break;
    }
}

void FoodSystem::createFruits(int rows, int cols) {
    auto width = sdlutils().width();
    auto height = sdlutils().height();

    auto row_h = height / (rows * 2);
    auto col_w = width / (cols * 2);

    auto pos = Vector2D();

    ecs::entity_t fruit;
    Transform* fruitTr;

    for(int i = 1; i < rows * 2; i+=2) {
        for(int j = 1; j < cols * 2; j+=2) {

            fruit = _mngr->addEntity(ecs::grp::FRUITS);

            auto x = col_w * j;
            auto y = row_h * i;

            pos = Vector2D(x,y);

            fruitTr = _mngr->addComponent<Transform>(fruit);
            fruitTr->init(pos, Vector2D(), col_w, row_h, 0.f);

            _mngr->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman_sprites"), 8, 8, 12);

            int n = sdlutils().rand().nextInt(0, 10);
            if(!n) {
                n = sdlutils().rand().nextInt(10, 21); // TODO config
                int m = sdlutils().rand().nextInt(5,11);
                _mngr->addComponent<Miraculous>(fruit, n, m);
            }
        }
    }
}

void FoodSystem::onFruitEaten(ecs::entity_t fruit) {
    _mngr->setAlive(fruit, false);

	// play sound on channel 1 (if there is something playing there it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}