#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H
#include "endofgamescreen.h"

class VictoryScreen: public EndOfGameScreen
{
public:
    VictoryScreen();
    virtual ~VictoryScreen();

private:
    QMovie* movie;
};

#endif // VICTORYSCREEN_H
