#include "xenemyview.h"
#include <QtMath>
#define PI 3.1415

void xenemyview::drawIsometric(MainWindow *window, int start_x, int start_y, double size, double height)
{


    QGraphicsView * graphview = window->getUi()->graphview_map2;
    QBrush brush(QColor(109,30,102)); //top brush
    QBrush brush2(QColor(55,18,52)); //front brush
    QBrush brush3(QColor(65,6,60)); // poly brush
    QBrush brush4(QColor(205,127,50)); // eye color brush
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

void xenemyview::drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size)
{
    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(109,30,102));
    QPen pen(Qt::black);


        // calculate upperleft corner
        double xpos= start_x;
        double ypos= start_y;
        QPolygonF top;
        top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);

        graphview->scene()->addPolygon(top, pen, brush);


}
