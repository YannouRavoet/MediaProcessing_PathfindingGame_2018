#ifndef REGENEMYVIEW_H
#define REGENEMYVIEW_H
#include "enemyview.h"

class RegEnemyView : public EnemyView
{
public:
    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
    static void drawDeadIsometric(MainWindow *window,int start_x,int start_y, double size);
};

#endif // REGENEMYVIEW_H
