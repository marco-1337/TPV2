#include "FoodSystem.h"

#include "Manager.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "Transform.h"
#include "Miraculous.h"
#include "ImageWithFrames.h"
#include "Game.h"

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

        Game::Instance()->setState(GameState::GAMEOVER_WIN);
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
    case _m_NEW_GAME:
        createFruits();
        break;
    case _m_ROUND_OVER:
        resetCounters();
        break;
    case _m_GAME_OVER:
        killAllFruits();
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

            auto x = col_w * j - col_w/4;
            auto y = row_h * i - row_h/4;

            pos = Vector2D(x,y);

            fruitTr = _mngr->addComponent<Transform>(fruit);
            fruitTr->init(pos, Vector2D(), col_w/2, row_h/2, 0.f);

            _mngr->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman_sprites"), 8, 8, 12);

            int n = sdlutils().rand().nextInt(0, 10);
            if(!n) {
                n = sdlutils().rand().nextInt(10, 21); // TODO config
                int m = sdlutils().rand().nextInt(5,11);
                _mngr->addComponent<Miraculous>(fruit, n * 1000, m * 1000);
            }
        }
    }
}

void FoodSystem::onFruitEaten(ecs::entity_t fruit) {
    if(_mngr->hasComponent<Miraculous>(fruit)) {
        auto miraculous = _mngr->getComponent<Miraculous>(fruit);
        if(miraculous->_miraculousState) {
            Message m;
            m.id = _m_IMMUNITY_START;
            _mngr->send(m);
        }
    }

    _mngr->setAlive(fruit, false);

	// play sound on channel 1 (if there is something playing there it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

void FoodSystem::killAllFruits() {
    auto fruits = _mngr->getEntities(ecs::grp::FRUITS);
    for (int i = 0; i < fruits.size(); ++i) _mngr->setAlive(fruits[i], false);
}

void FoodSystem::resetCounters() {
    auto fruits = _mngr->getEntities(ecs::grp::FRUITS);
    for (int i = 0; i < fruits.size(); ++i) {
        if (_mngr->hasComponent<Miraculous>(fruits[i])) {
            auto miraculous = _mngr->getComponent<Miraculous>(fruits[i]);
            miraculous->reset();

            _mngr->getComponent<ImageWithFrames>(fruits[i])->setFrame(12);
        }
    }
}