#ifndef BABYENEMY_H
#define BABYENEMY_H
#include "world.h"

class BabyEnemy:public Enemy
{
public:
    BabyEnemy(int xPosition, int yPosition, float strength);
};

#endif // BABYENEMY_H
