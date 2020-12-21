#include "protagonistview.h"
#include "viewone.h"
#include <QtMath>
#define PI 3.1415

void ProtagonistView::drawIsometric(MainWindow *window, int start_x, int start_y, double size, double height)
{


    QBrush brush(QColor(33,95,163)); //top brush
    QBrush brush2(QColor(32,78,148)); //front brush
    QBrush brush3(QColor(37,58,126)); // poly brush
    QBrush brush4(QColor(255,255,255)); // eye color brush
    QPen pen(Qt::black);

    // calculate upperleft corner
    //double xpos= start_x*size -20-cos(45*PI/180)*height;
    //double ypos= (start_y*size-20)*0.86602-cos(45*PI/180)*height*0.86602;
    QGraphicsView * graphview = window->getUi()->graphview_map2;
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

    QPolygonF leftHorn1;
    leftHorn1 << QPointF(xpos, ypos+size*0.86602) << QPointF(xpos+size/5,ypos+size*0.86602)
              << QPointF(xpos+size/5-2*cos(45*PI/180)*size/5,ypos+size*0.86602-2*cos(45*PI/180)*size*0.86602/5);

    QPolygonF leftHorn2;
    leftHorn2<< QPointF(xpos+size/5,ypos+size*0.86602)
             << QPointF(xpos+size/5,ypos+size*0.86602-size*0.86602/5)
             << QPointF(xpos+size/5-2*cos(45*PI/180)*size/5,ypos+size*0.86602-2*cos(45*PI/180)*size*0.86602/5);

    QPolygonF rightHorn1;
    rightHorn1 << QPointF(xpos+size-size/5, ypos+size*0.86602) << QPointF(xpos+size,ypos+size*0.86602)
               << QPointF(xpos+size-2*cos(45*PI/180)*size/5,ypos+size*0.86602-2*cos(45*PI/180)*size*0.86602/5);

    QPolygonF rightHorn2;
    rightHorn2<< QPointF(xpos+size,ypos+size*0.86602)
              << QPointF(xpos+size-2*cos(45*PI/180)*size/5,ypos+size*0.86602-2*cos(45*PI/180)*size*0.86602/5)
              << QPointF(xpos+size,ypos+size*0.86602-size*0.86602/5);

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

void ProtagonistView::drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size)
{
    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(33,95,163));
    QPen pen(Qt::black);


    // calculate upperleft corner
    double xpos= start_x;
    double ypos= start_y;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);

    graphview->scene()->addPolygon(top, pen, brush);


}
