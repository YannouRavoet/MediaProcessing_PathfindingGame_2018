#include "regenemyview.h"
#include <QtMath>
#define PI 3.1415


void RegEnemyView::drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height){

    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(24,21,28));
    QBrush brush2(QColor(236,32,40));
    QBrush brush3(QColor(240,150,35));
    QBrush brush4(QColor(210,94,42));
    QBrush brush5(QColor(254,253,251));
    QBrush brush6(QColor(227,204,194));
    QBrush brush7(QColor(23,19,24));
    QBrush brush8(QColor(28,27,36));
    QBrush brush9(Qt::red);
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

        //top has to be drawn before the horns adapt switch case to change position of horns etc so it can be out switch
        switch (window->getRotation()) {

        case 1:{
            graphview->scene()->addPolygon(poly, pen, brush7);
            graphview->scene()->addPolygon(front, pen, brush);
            graphview->scene()->addPolygon(top, pen, brush8);
            //horns at different position

            break;
        }
        case 2:{
            graphview->scene()->addPolygon(poly, pen, brush7);
            graphview->scene()->addPolygon(front, pen, brush);
            graphview->scene()->addPolygon(top, pen, brush8);
            //horns at different position

            break;
        }
        case 3:{
            graphview->scene()->addPolygon(poly, pen, brush7);
            graphview->scene()->addPolygon(front, pen, brush);
            graphview->scene()->addPolygon(top, pen, brush8);
            //eyes need to be drawn here but at different position

            break;
        }
        default:{
            graphview->scene()->addPolygon(poly, pen, brush7);
            graphview->scene()->addPolygon(front, pen, brush);
            graphview->scene()->addPolygon(lefteye, pen, brush2);
            graphview->scene()->addPolygon(righteye, pen, brush2);
            graphview->scene()->addPolygon(top, pen, brush8);
            graphview->scene()->addPolygon(leftHorn1, pen, brush3);
            graphview->scene()->addPolygon(leftHorn2, pen, brush4);
            graphview->scene()->addPolygon(rightHorn1, pen, brush3);
            graphview->scene()->addPolygon(rightHorn2, pen, brush4);
            break;
        }

        }



}

void RegEnemyView::drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size)
{
    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(28,27,36));
    QPen pen(Qt::black);


        // calculate upperleft corner
        double xpos= start_x;
        double ypos= start_y;
        QPolygonF top;
        top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);

        graphview->scene()->addPolygon(top, pen, brush);


}
