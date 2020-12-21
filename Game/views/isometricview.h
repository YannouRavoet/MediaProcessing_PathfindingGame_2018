#ifndef ISOMETRICVIEW_H
#define ISOMETRICVIEW_H
#include "mainwindow.h"

class isometricView
{
public:
    virtual ~isometricView();
    static isometricView* getInstance(MainWindow* window); //called in MainWindow constructor because the Controller MainWindow element is still being initialised at that point
    static isometricView* getInstance();

    std::vector<MyTile*> loadImageMap();

    void draw_wall(double start_x, double start_y, double size,float height,QGraphicsScene* scene,int rotation);

    void draw_map(QGraphicsScene* scene,std::vector<MyTile*> worldToDraw);

    void transform_to_isometric();

    void draw_world();


    std::vector<std::shared_ptr<MyHealthpack> > calculate_visible_healthpacks(std::vector<MyTile *> map, std::vector<std::shared_ptr<MyHealthpack> > healthpacks);
    std::vector<std::shared_ptr<Enemy> > calculate_visible_enemies(std::vector<MyTile *> map, std::vector<std::shared_ptr<Enemy> > enemies);
    void FocusOnProtagonist();
private:
    isometricView(MainWindow* window);
    static isometricView* instance;
    QGraphicsScene* scene;
};

#endif // ISOMETRICVIEW_H
