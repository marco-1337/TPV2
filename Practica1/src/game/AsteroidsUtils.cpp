#include "AsteroidsUtils.h"
#include "SDLUtils.h"

#include "Entity.h"
#include "Component.h"

#include "Transform.h"
#include "Generations.h"
#include "ShowAtOppositeSide.h"
#include "ImageWithFrames.h"
#include "Follow.h"
#include "TowardsDestination.h"

#include "Game.h"

constexpr int ROWS = 5;
constexpr int COLS = 6;
constexpr Uint32 FRAME_UPDATE_FRECUENCY = 50;

AsteroidsUtils::AsteroidsUtils()
{
    _mngr = Game::Instance()->getMngr();
}

void
AsteroidsUtils::create_asteroids(int n)
{
    int pared;

    int w = sdlutils().width(), 
        h = sdlutils().height(), 
        g;

    ecs::entity_t e;
    float speed, scale;
    Vector2D p, v;

    for (int i = 0; i < n; ++i)
    {
        e = _mngr->addEntity(ecs::grp::ASTEROIDS);

        // 0 izquierda
        // 1 arriba
        // 2 derecha
        // 3 abajo
        pared = sdlutils().rand().nextInt(0, 4);

        if (pared %2 == 0)
        {
            p.setX((pared == 0) ? 0 : w);
            p.setY(sdlutils().rand().nextInt(0, h));
        }
        else
        {            
            p.setX(sdlutils().rand().nextInt(0, w));
            p.setY((pared == 1) ? 0 : h);
        }

        Vector2D c = 
            {
                (float)w/2 + (sdlutils().rand().nextInt(-100,101)), 
                (float)h/2 + (sdlutils().rand().nextInt(-100,101))
            };
        
        speed = sdlutils().rand().nextInt(1,Game::Instance()->config().at("asteroids_speed_limit"))/10.0f;
        v = (c-p).normalize()*speed;

        g = _mngr->addComponent<Generations>(e)->getGeneration();

        scale = 10.0f+5.0f*g;

        _mngr->addComponent<Transform>(e, p, v, scale, scale, 0.0f);
        _mngr->addComponent<ShowAtOppositeSide>(e);

        if (sdlutils().rand().nextInt(0, Game::Instance()->config().at("asteroids_golden_chance")))
        {
            _mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("asteroid"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
            _mngr->addComponent<TowardsDestination>(e);
        }
        else
        {
            _mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("asteroid_gold"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
            _mngr->addComponent<Follow>(e);
        }
    }
}

void 
AsteroidsUtils::remove_all_asteroids() {
    for(auto& a: _mngr->getEntities(ecs::grp::ASTEROIDS)) {
        _mngr->setAlive(a, false);
    }
    _mngr->refresh();
}

void 
AsteroidsUtils::split_asteroid(ecs::entity_t a) {
    auto g = _mngr->getComponent<Generations>(a);
    _mngr->setAlive(a, false);

    if(g->getGeneration() > 1) {
        auto tr = _mngr->getComponent<Transform>(a);

        ecs::entity_t a_child;

        for(int i = 0; i < Game::Instance()->config().at("asteroids_split"); ++i) {
            a_child = _mngr->addEntity(ecs::grp::ASTEROIDS);

            int r = sdlutils().rand().nextInt(0,360);
            Vector2D pos = tr->getPos() + tr->getVel().rotate(r) * 2 * std::max(tr->getWidth(), tr->getHeight());     
            Vector2D vel = tr->getVel().rotate(r) * 1.1f;  

            _mngr->addComponent<Generations>(a_child)->setGeneration(g->getGeneration()-1);
            int gen = _mngr->getComponent<Generations>(a_child)->getGeneration();

            float scale = 10.0f+5.0f*gen;

            _mngr->addComponent<Transform>(a_child, pos, vel, scale, scale, 0.0f);
            _mngr->addComponent<ShowAtOppositeSide>(a_child);

            if(_mngr->hasComponent<Follow>(a)) {
                _mngr->addComponent<ImageWithFrames>(a_child, &sdlutils().images().at("asteroid_gold"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
                _mngr->addComponent<Follow>(a_child);
            }
            else {
                _mngr->addComponent<ImageWithFrames>(a_child, &sdlutils().images().at("asteroid"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
                _mngr->addComponent<TowardsDestination>(a_child);
            }
        }
  
    }
}