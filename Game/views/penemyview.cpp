#include "penemyview.h"
#include <QtMath>
#define PI 3.1415

void PEnemyView::drawIsometric(MainWindow *window,int start_x,int start_y, double size,double height){

    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(123,197,131)); //top brush
    QBrush brush2(QColor(10,69,56)); //front brush
    QBrush brush3(QColor(17,158,74)); // poly brush
    QBrush brush4(QColor(255,255,255)); // eye color brush

    /*QBrush brush5(QColor(254,253,251));
    QBrush brush6(QColor(227,204,194));
    QBrush brush7(QColor(23,19,24));*/
    QBrush brush8(Qt::yellow);
    QBrush brush9(Qt::magenta);
    QPen pen(Qt::black);


    //notes for rotation:
    //top plane can remain the same never changes (horns might but not top plane)
    //planes take different location (if 4 planes) alwyas change points to the next one
    //a.k.amake 4 planes and draw in different order => results in rotation
    //coordinates will have to change to since they stay at one point


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
    QPolygonF back;
    back << QPointF(xpos,ypos) << QPointF(xpos+size, ypos) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+cos(45*PI/180)*height*0.86602) <<QPointF(xpos + cos(45*PI/180)*height,ypos+cos(45*PI/180)*0.86602);
    QPolygonF leftSide;
    leftSide <<QPointF(xpos,ypos) <<QPointF(xpos + cos(45*PI/180)*height,ypos+cos(45*PI/180)*0.86602)<< QPointF(xpos+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602)<<QPointF(xpos,ypos+size*0.86602);

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

    //todo make it not code duplication( or less by changing the brushes) see other views
    switch (window->getRotation()) {

        case 1:
            graphview->scene()->addPolygon(poly, pen, brush3);
            graphview->scene()->addPolygon(top, pen, brush);
            graphview->scene()->addPolygon(front, pen, brush3);
            //eyes are not visible and not drawn for efficientie
        break;

        case 2:
            graphview->scene()->addPolygon(poly, pen, brush3);
            graphview->scene()->addPolygon(top, pen, brush);
            graphview->scene()->addPolygon(front, pen, brush3);
            //eyes are not visible and are not drawn for efficientie purposes

        break;

        case 3:
            graphview->scene()->addPolygon(poly, pen, brush2);
            graphview->scene()->addPolygon(top, pen, brush);
            graphview->scene()->addPolygon(front, pen, brush3);
            //eyes should be drawn here but at different locations
        break;

        default:
            graphview->scene()->addPolygon(poly, pen, brush3);
            graphview->scene()->addPolygon(top, pen, brush);
            graphview->scene()->addPolygon(front, pen, brush2);
            graphview->scene()->addPolygon(lefteye, pen, brush4);
            graphview->scene()->addPolygon(righteye, pen, brush4);
        break;

    }

}

void PEnemyView::drawDeadIsometric(MainWindow *window, int start_x, int start_y, double size)
{
    QGraphicsView * graphview = window->getUi()->graphview_map2;

    QBrush brush(QColor(123,197,131));
    QPen pen(Qt::black);


    // calculate upperleft corner
    double xpos= start_x;
    double ypos= start_y;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);

    graphview->scene()->addPolygon(top, pen, brush);


}
