#ifndef BABYENEMYVIEW_H
#define BABYENEMYVIEW_H

#include "mainwindow.h"

class Babyenemyview
{
public:
    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
    static void drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size);
};

#endif // BABYENEMYVIEW_H
