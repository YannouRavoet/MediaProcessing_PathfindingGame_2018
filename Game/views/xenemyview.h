#ifndef XENEMYVIEW_H
#define XENEMYVIEW_H
#include "mainwindow.h"

class xenemyview
{
public:
    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
    static void drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size);
};

#endif // XENEMYVIEW_H
