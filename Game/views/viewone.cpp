#include <QImage>
#include "viewone.h"
#include "controller.h"
#include "pathfinding.h"
#include "helperclasses/myprotagonist.h"
#include "helperclasses/xenemy.h"
#include "helperclasses/babyenemy.h"


ViewOne * ViewOne::firstInstance;

ViewOne::ViewOne()
{
    image = new QImage();
}

ViewOne* ViewOne::getInstance()
{
    if(firstInstance== nullptr)
        firstInstance=new ViewOne();
    return firstInstance;
}

ViewOne::~ViewOne()
{
    graph_scene->clear();
    delete image;
    delete graph_scene;
}

void ViewOne::initMap(std::vector<MyTile*> map, QString filename)
{
    delete image;
    image = new QImage(filename);
    for(MyTile* tile: map)
    {
        int grayValue = int(tile->getValue()*255);
        unsigned int colourValue = qRgb(grayValue,grayValue,grayValue);
        QColor color = QColor::fromRgb(colourValue);
        image->setPixelColor(tile->getXPos(),tile->getYPos(),color);
    }
    return;
}
bool ViewOne::initViewOne(QString filename){
    MyWorld* world = Controller::getInstance()->getWorld();
    MainWindow* window = Controller::getInstance()->getWindow();
    std::vector<std::shared_ptr<Enemy>> enemies = world->getEnemies();
    std::vector<std::shared_ptr<MyHealthpack>> healthpacks = world->getHealthpacks();
    /*SCENE*/
    graph_scene = new QGraphicsScene();
    window->getUi()->graphview_map->setScene(graph_scene);
    /*MAP IMAGE*/
    initMap(world->getMap(),filename);
    return true;
}

void ViewOne::makeProtagonistItem()
{
    QGraphicsPixmapItem* protagonistItem;
    if(Controller::getInstance()->getWorld()->getProta()->isDead())
        protagonistItem = new QGraphicsPixmapItem(QPixmap(protaImgFileDead));
    else{
        switch(protaState++%2){//switch case for more complex animations
            case 0:
                protagonistItem = new QGraphicsPixmapItem(QPixmap(protaImgFile));
            break;
            case 1:
                protagonistItem = new QGraphicsPixmapItem(QPixmap(protaImgFile1));
            break;
        }
    }
    int x = Controller::getInstance()->getWorld()->getProta()->getXPos();
    int y = Controller::getInstance()->getWorld()->getProta()->getYPos();
    protagonistItem->setFlag(QGraphicsItem::ItemIsFocusable);
    protagonistItem->setFocus();
    protagonistItem->setScale(object_scale/128);
    protagonistItem->setZValue(3);
    double xOffset = x*128*map_scale/object_scale;
    double yOffset = y*128*map_scale/object_scale;
    double maxxOffset = Controller::getInstance()->getWorld()->getCols()*128*map_scale/object_scale-128;
    double maxyOffset = Controller::getInstance()->getWorld()->getRows()*128*map_scale/object_scale-128;
    protagonistItem->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    graph_scene->addItem(protagonistItem);
    Controller::getInstance()->getWindow()->getUi()->graphview_map->ensureVisible(protagonistItem,10,10);
    return;
}
void ViewOne::makeEnemy(std::shared_ptr<Enemy> enemy)
{
    QGraphicsPixmapItem* newEnemyItem;
    if(dynamic_cast<PEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(pEnemyImgFile));
    else if(dynamic_cast<XEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(xEnemyImgFile));
    else if(dynamic_cast<BabyEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(xEnemyImgFile));
    else if(dynamic_cast<Enemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(regEnemyImgFile));
    else
        return;
    if(dynamic_cast<BabyEnemy*>(enemy.get()))
        newEnemyItem->setScale(object_scale/512);
    else
        newEnemyItem->setScale(object_scale/256);
    newEnemyItem->setZValue(2);
    if(dynamic_cast<BabyEnemy*>(enemy.get())){

        double xOffset = enemy->getXPos()*512*map_scale/object_scale;
        double yOffset = enemy->getYPos()*512*map_scale/object_scale;
        double maxxOffset = Controller::getInstance()->getWorld()->getCols()*512*map_scale/object_scale-512;
        double maxyOffset = Controller::getInstance()->getWorld()->getRows()*512*map_scale/object_scale-512;
        newEnemyItem->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    }
    else{
        double xOffset = enemy->getXPos()*256*map_scale/object_scale;
        double yOffset = enemy->getYPos()*256*map_scale/object_scale;
        double maxxOffset = Controller::getInstance()->getWorld()->getCols()*256*map_scale/object_scale-256;
        double maxyOffset = Controller::getInstance()->getWorld()->getRows()*256*map_scale/object_scale-256;
        newEnemyItem->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    }
    graph_scene->addItem(newEnemyItem);
    return;
}
void ViewOne::makeDeadEnemy(std::shared_ptr<Enemy> enemy)
{
    QGraphicsPixmapItem* newEnemyItem;
    if(dynamic_cast<PEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(deadPEnemyImgFile));
    else if(dynamic_cast<XEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(deadXEnemyImgFile));
    else if(dynamic_cast<BabyEnemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(deadXEnemyImgFile));
    else if(dynamic_cast<Enemy*>(enemy.get()))
        newEnemyItem = new QGraphicsPixmapItem(QPixmap(deadRegEnemyImgFile));
    else
        return;
    if(dynamic_cast<BabyEnemy*>(enemy.get()))
        newEnemyItem->setScale(object_scale/512);
    else
        newEnemyItem->setScale(object_scale/256);
    newEnemyItem->setZValue(2);
    if(dynamic_cast<BabyEnemy*>(enemy.get())){
        double xOffset = enemy->getXPos()*512*map_scale/object_scale;
        double yOffset = enemy->getYPos()*512*map_scale/object_scale;
        double maxxOffset = Controller::getInstance()->getWorld()->getCols()*512*map_scale/object_scale-512;
        double maxyOffset = Controller::getInstance()->getWorld()->getRows()*512*map_scale/object_scale-512;
        newEnemyItem->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    }
    else{
        double xOffset = enemy->getXPos()*256*map_scale/object_scale;
        double yOffset = enemy->getYPos()*256*map_scale/object_scale;
        double maxxOffset = Controller::getInstance()->getWorld()->getCols()*256*map_scale/object_scale-256;
        double maxyOffset = Controller::getInstance()->getWorld()->getRows()*256*map_scale/object_scale-256;
        newEnemyItem->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    }
    graph_scene->addItem(newEnemyItem);
    return;
}
void ViewOne::makeHealthpack(std::shared_ptr<MyHealthpack> pack)
{
    QGraphicsPixmapItem* newHealthpack = new QGraphicsPixmapItem(QPixmap(healthpackFile));
    newHealthpack->setZValue(2);
    newHealthpack->setScale(object_scale/128);

    double xOffset = pack->getX()*128*map_scale/object_scale;
    double yOffset = pack->getY()*128*map_scale/object_scale;
    double maxxOffset = Controller::getInstance()->getWorld()->getCols()*128*map_scale/object_scale-128;
    double maxyOffset = Controller::getInstance()->getWorld()->getRows()*128*map_scale/object_scale-128;
    newHealthpack->setOffset(std::min(xOffset,maxxOffset),std::min(yOffset,maxyOffset));
    graph_scene->addItem(newHealthpack);
    return;
}
void ViewOne::showPath(std::vector<MyTile*> path)
{
    initMap(Controller::getInstance()->getWorld()->getMap(),Controller::getInstance()->getMapfile());
    for(MyTile* tile: path){
        if(tile==Controller::getInstance()->getPathfinding()->getStart())
            image->setPixelColor(tile->getXPos(),tile->getYPos(),QColor(102,229,119,120));
        else if(tile==Controller::getInstance()->getPathfinding()->getDest())
            image->setPixelColor(tile->getXPos(),tile->getYPos(),QColor(248,16,16,120));
        else
            image->setPixelColor(tile->getXPos(),tile->getYPos(),QColor(105,184,221,120));
    }
    refreshSceneImage();
}

void ViewOne::refreshSceneImage()
{
    MainWindow* window = Controller::getInstance()->getWindow();
    graph_scene->clear();
    QGraphicsPixmapItem *mapItem = new QGraphicsPixmapItem (QPixmap::fromImage(*image));
    mapItem->setZValue(1);
    mapItem->setPos(0,0);
    mapItem->setScale(map_scale);
    graph_scene->addItem(mapItem);
    makeProtagonistItem();
    for(std::shared_ptr<Enemy> enemy: Controller::getInstance()->getWorld()->getEnemies())
    {
        if(enemy->getDefeated()==true)
            makeDeadEnemy(enemy);
        else
            makeEnemy(enemy);
    }
    for(std::shared_ptr<MyHealthpack> pack: Controller::getInstance()->getWorld()->getUnusedHealthpacks())
        makeHealthpack(pack);
    graph_scene->setSceneRect(0,0,image->width()*map_scale,image->height()*map_scale);
    graph_scene->update();
    window->getUi()->graphview_map->update();

}
void ViewOne::updateScaleFactor()
{
    MainWindow* window = Controller::getInstance()->getWindow();
    double newWidth = window->getUi()->graphview_map->width();
    double newHeight = window->getUi()->graphview_map->height();
    double scalex_factor = (newHeight)/image->height();
    double scaley_factor = (newWidth)/image->width();
    map_scale = std::max(2.0,std::min(scalex_factor,scaley_factor));
    object_scale = std::max(16.0,map_scale);

    refreshSceneImage(); //after scaling you should refresh the scene image
}
double ViewOne::getMap_scale() const
{
    return map_scale;
}
void ViewOne::setMap_scale(double value)
{
    map_scale = value;
    object_scale = std::max(16.0,map_scale);
}
