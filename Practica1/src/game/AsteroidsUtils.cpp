#include "AsteroidsUtils.h"
#include "SDLUtils.h"

#include "Entity.h"
#include "Component.h"

#include "Transform.h"
#include "Generations.h"
#include "ShowAtOppositeSide.h"
#include "ImageWithFrames.h"
#include "Follow.h"

constexpr int ROWS = 5;
constexpr int COLS = 6;
constexpr Uint32 FRAME_UPDATE_FRECUENCY = 50;

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
        e = _mgr->addEntity();

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
        
        speed = sdlutils().rand().nextInt(1,10)/10.0f;
        v = (c-p).normalize()*speed;

        g = _mgr->addComponent<Generations>(e)->getGeneration();

        scale = 10.0f+5.0f*g;

        _mgr->addComponent<Transform>(e, p, v, scale, scale, 0.0f);
        _mgr->addComponent<ShowAtOppositeSide>(e);

        if (sdlutils().rand().nextInt(0, 2))
        {
            _mgr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("asteroid_gold"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
            _mgr->addComponent<Follow>(e);
        }
        else
        {
            _mgr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("asteroid"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
            // TODO: añadir toward destination
        }
    }
}

void 
AsteroidsUtils::remove_all_asteroids() {
    for(auto& a: _mgr->getEntities(ecs::grp::ASTEROIDS)) {
        _mgr->setAlive(a, false);
    }
    _mgr->refresh();
}

void 
AsteroidsUtils::split_asteroid(ecs::entity_t a) {
    auto g = _mgr->getComponent<Generations>(a);
    _mgr->setAlive(a, false);

    if(g->getGeneration() > 1) {
        auto tr = _mgr->getComponent<Transform>(a);

        ecs::entity_t a_child;

        for(int i = 0; i < 2; ++i) {
            a_child = _mgr->addEntity();

            int r = sdlutils().rand().nextInt(0,360);    
            Vector2D pos = tr->getPos() + tr->getVel().rotate(r) * 2 * std::max(tr->getWidth(), tr->getHeight());     
            Vector2D vel = tr->getVel().rotate(r) * 1.1f;  

            int g = _mgr->addComponent<Generations>(a_child)->getGeneration();

            float scale = 10.0f+5.0f*g;

            _mgr->addComponent<Transform>(a_child, pos, vel, scale, scale, 0.0f);
            _mgr->addComponent<ShowAtOppositeSide>(a_child);

            if(_mgr->hasComponent<Follow>(a)) {
                _mgr->addComponent<ImageWithFrames>(a_child, &sdlutils().images().at("asteroid_gold"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
                _mgr->addComponent<Follow>(a_child);
            }
            else {
                _mgr->addComponent<ImageWithFrames>(a_child, &sdlutils().images().at("asteroid"), COLS, ROWS, FRAME_UPDATE_FRECUENCY);
                // TODO: añadir toward destination
            }
        }
  
    }
}