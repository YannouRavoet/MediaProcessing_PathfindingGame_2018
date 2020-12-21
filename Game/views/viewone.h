#ifndef VIEWONE_H
#define VIEWONE_H
#include <memory>
#include <QString>
#include "mainwindow.h"
#include <QGraphicsPixmapItem>
#include "helperclasses/myworld.h"

class ViewOne: public QGraphicsView
{
public:
    static ViewOne* getInstance();
    ~ViewOne();

    void initMap(std::vector<MyTile*> map,QString filename);
    bool initViewOne(QString filename);
    void showPath(std::vector<MyTile*> path);

    void refreshSceneImage();
    void updateScaleFactor();
    double getMap_scale() const;
    void setMap_scale(double value);


private:
    void makeProtagonistItem();
    void makeEnemy(std::shared_ptr<Enemy> enemy);
    void makeDeadEnemy(std::shared_ptr<Enemy> enemy);
    void makeHealthpack(std::shared_ptr<MyHealthpack> pack);


    ViewOne();
    static ViewOne *firstInstance;
    QImage* image=nullptr;
    QGraphicsScene* graph_scene=nullptr;
    double map_scale;
    double object_scale;

    QString protaImgFileDead = ":/img/pacmandead.png";
    QString protaImgFile = ":/img/pacman.png";
    QString protaImgFile1 = ":/img/pacmanclosed.png";
    unsigned int protaState=1;

    QString regEnemyImgFile = ":/img/ghostblue.png";
    QString pEnemyImgFile = ":/img/ghostred.png";
    QString xEnemyImgFile = ":/img/ghostyellow.png";
    QString healthpackFile = ":/img/healthpack.png";
    QString deadRegEnemyImgFile = ":/img/deadBlueGhost.png";
    QString deadPEnemyImgFile = ":/img/deadRedGhost.png";
    QString deadXEnemyImgFile = ":/img/deadGreenGhost.png";

};

#endif // VIEWONE_H
