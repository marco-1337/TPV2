#include "AsteroidsUtils.h"
#include "SDLUtils.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

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

        // to do añadir asteroide con esa informacion
        _mgr->addComponent<Transform>(e, p, speed, scale, scale, 0.0);

        _mgr->addComponent<ShowAtOppositeSide>(e);

        if (sdlutils().rand().nextInt(0, 2))
        {

        }
        else
        {

        }
    }
}