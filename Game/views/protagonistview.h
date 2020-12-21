#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H
#include "mainwindow.h"


class ProtagonistView
{
public:
    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
    static void drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size);

};



#endif // PROTAGONISTVIEW_H
