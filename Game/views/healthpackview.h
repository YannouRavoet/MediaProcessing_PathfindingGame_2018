#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H
#include "mainwindow.h"

class HealthpackView
{
public:

    static void drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height);
};

#endif // HEALTHPACKVIEW_H
