#include "AsteroidsFacade.h"

class Manager;

class AsteroidsUtils: public AsteroidsFacade
{
private:
    Manager* _mgr;
public:
    inline AsteroidsUtils(Manager* mgr): _mgr(mgr) {}
    inline ~AsteroidsUtils() {} 
};