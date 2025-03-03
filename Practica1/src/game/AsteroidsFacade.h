
class Entity;
class Manager;

class AsteroidsFacade {
public:
    AsteroidsFacade() { }
    
    virtual ~AsteroidsFacade() { }
    
    virtual void create_asteroids(int n) = 0;
    
    virtual void remove_all_asteroids() = 0;
    
    virtual void split_astroid(Entity *a) = 0;
};