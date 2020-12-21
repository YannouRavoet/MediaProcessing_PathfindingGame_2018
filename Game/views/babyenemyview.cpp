#include <QtMath>
#include "babyenemyview.h"
#define PI 3.1415


void Babyenemyview::drawIsometric(MainWindow *window, int start_x, int start_y, double size, double height)
{

    QGraphicsView * graphview = window->getUi()->graphview_map2;
    QBrush brush(QColor(252,142,172)); //top brush
    QBrush brush2(QColor(252,142,172)); //front brush
    QBrush brush3(QColor(209,112,121)); // poly brush
    QBrush brush4(QColor(135,206,235)); // eye color brush
    QPen pen(Qt::black);

    // calculate upperleft corner
    double xpos= start_x-cos(45*PI/180)*height;
    double ypos= start_y-cos(45*PI/180)*height*0.86602;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);
    QPolygonF poly;
    poly << QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+cos(45*PI/180)*height*0.86602) << QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);
    QPolygonF front;
    front <<QPointF(xpos,ypos+size*0.86602) << QPointF(xpos+size, ypos+size*0.86602) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602)<<QPointF(xpos+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);

    QPolygonF lefteye;
    lefteye << QPointF(xpos+size/5 ,ypos+size*0.86602+cos(45*PI/180)*(size/5)*0.86602)
            <<QPointF(xpos+2*size/5 ,ypos+size*0.86602+cos(45*PI/180)*(size/5)*0.86602)
           <<QPointF(xpos+2*size/5+2*cos(45*PI/180)*size/5 ,ypos+size*0.86602+cos(45*PI/180)*(3*size/5)*0.86602)
          << QPointF(xpos+size/5+2*cos(45*PI/180)*size/5,ypos+size*0.86602+cos(45*PI/180)*(3*size/5)*0.86602);


    QPolygonF righteye;
    righteye << QPointF(xpos-size/5+size ,ypos+size*0.86602+cos(45*PI/180)*(size/5)*0.86602)
             <<QPointF(xpos-2*size/5 +size ,ypos+size*0.86602+cos(45*PI/180)*(size/5)*0.86602)
            <<QPointF(xpos-2*size/5+2*cos(45*PI/180)*size/5 +size ,ypos+size*0.86602+cos(45*PI/180)*(3*size/5)*0.86602)
           << QPointF(xpos-size/5+2*cos(45*PI/180)*size/5+size,ypos+size*0.86602+cos(45*PI/180)*(3*size/5)*0.86602);

    switch (window->getRotation()) {
        case 1:{
            //map turned 90°
            graphview->scene()->addPolygon(poly, pen, brush3);
            graphview->scene()->addPolygon(front, pen, brush3);

            break;
        }
        case 2:{
            //map turend 180°
            graphview->scene()->addPolygon(poly, pen, brush3);
            graphview->scene()->addPolygon(front, pen, brush3);
            break;
        }
        case 3:{
            //map turned 270°
            graphview->scene()->addPolygon(poly, pen, brush2);
            graphview->scene()->addPolygon(front, pen, brush3);
            //eyes need to be drawn here but at other location
            //graphview->scene()->addPolygon(lefteye, pen, brush4);
            //graphview->scene()->addPolygon(righteye, pen, brush4);
            break;
        }
        default:{
            //no rotation in map
            graphview->scene()->addPolygon(poly, pen, brush3);

            graphview->scene()->addPolygon(front, pen, brush2);
            graphview->scene()->addPolygon(lefteye, pen, brush4);
            graphview->scene()->addPolygon(righteye, pen, brush4);

            break;
        }
    }
    graphview->scene()->addPolygon(top, pen, brush);
}

void Babyenemyview::drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size)
{
    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(252,142,172));
    QPen pen(Qt::black);


    // calculate upperleft corner
    double xpos= start_x;
    double ypos= start_y;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);

    graphview->scene()->addPolygon(top, pen, brush);


}
