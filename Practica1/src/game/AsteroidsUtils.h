#include "AsteroidsFacade.h"
#include "Manager.h"

class AsteroidsUtils: public AsteroidsFacade
{
public:
    AsteroidsUtils(ecs::Manager* mgr): _mgr(mgr) { }
    
    virtual ~AsteroidsUtils() { }
    
    void create_asteroids(int n) override;
    
    void remove_all_asteroids() override;
    
    void split_astroid(Entity *a) override;
protected:
    ecs::Manager* _mgr;
};