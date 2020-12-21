#include "myprotagonist.h"


MyProtagonist::MyProtagonist(int x, int y):Protagonist ()
{
    setXPos(x);
    setYPos(y);
}

bool MyProtagonist::isDead()
{
    return getHealth()<=0 or getEnergy()<=0;
}
