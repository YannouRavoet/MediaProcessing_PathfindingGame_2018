#include "healthpackview.h"
#include <qgraphicsview.h>

#include <QtMath>
#define PI 3.1415


void HealthpackView::drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height){

    QGraphicsView * graphview = window->getUi()->graphview_map2;

    //brushes
    QBrush brush(Qt::green);
    QBrush brush2(Qt::red);

    //pens
    QPen pen(Qt::black);

    // calculate upperleft corner
    //double xpos= start_x*size -20-cos(45*PI/180)*height;
    //double ypos= (start_y*size-20)*0.86602-cos(45*PI/180)*height*0.86602;
    double xpos= start_x-cos(45*PI/180)*height;
    double ypos= start_y-cos(45*PI/180)*height*0.86602;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);
    QPolygonF poly;
    poly << QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+cos(45*PI/180)*height*0.86602) << QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);
    QPolygonF front;
    front <<QPointF(xpos,ypos+size*0.86602) << QPointF(xpos+size, ypos+size*0.86602) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602)<<QPointF(xpos+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);

    QPolygonF cross1;
    cross1 << QPointF(xpos+size/2 -size/5,ypos) <<QPointF(xpos+size/2 +size/5,ypos) << QPointF(xpos+size/2 +size/5,ypos+size*0.86602) <<QPointF(xpos+size/2 -size/5,ypos+size*0.86602);


    QPolygonF cross2;
    cross2 << QPointF(xpos+size,ypos+(size/2 +size/5)*0.86602) <<QPointF(xpos+size,ypos+(size/2 -size/5)*0.86602) <<QPointF(xpos,ypos+(size/2 -size/5)*0.86602) <<QPointF(xpos,ypos+(size/2 +size/5)*0.86602);

    //no need for switch case here since the healthpack looks the same from every angle
    graphview->scene()->addPolygon(poly, pen, brush);
    graphview->scene()->addPolygon(top, pen, brush);
    graphview->scene()->addPolygon(front, pen, brush);
    graphview->scene()->addPolygon(cross1, pen, brush2);
    graphview->scene()->addPolygon(cross2, pen, brush2);


}



