#ifndef XENEMY_H
#define XENEMY_H

#include "world.h"

class XEnemy: public Enemy
{
public:
    XEnemy(int xPosition, int yPosition, float strength,unsigned int range,unsigned int children);
    void setDefeated(bool value);
    void setDefeatedWithNoSpawn(bool value);
    unsigned int getChildren() const;
    void setChildren(unsigned int value);

    unsigned int getSpawnRange() const;
    void setSpawnRange(unsigned int value);

private:
    unsigned int children;
    unsigned int spawnRange=3;
};

#endif // XENEMY_H
