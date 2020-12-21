#ifndef PENEMYVIEW_H
#define PENEMYVIEW_H
#include "enemyview.h"

class PEnemyView: public EnemyView
{
public:

    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
    static void drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size);
};

#endif // PENEMYVIEW_H
