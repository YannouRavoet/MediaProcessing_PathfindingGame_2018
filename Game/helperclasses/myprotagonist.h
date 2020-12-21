#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include "world.h"
#include <QObject>

class MyProtagonist: public Protagonist
{
    Q_OBJECT
public:
    MyProtagonist(int x, int y);
    bool isDead();
};

#endif // MYPROTAGONIST_H
