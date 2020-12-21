#include "xenemy.h"
#include "babyenemy.h"
#include "controller.h"
#include "mainwindow.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength, unsigned int range,unsigned int children)
    :Enemy (xPosition,yPosition,strength),children(children),spawnRange(range)
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

void XEnemy::setDefeated(bool value)
{

    Enemy::setDefeated(value); //this will emit the dead() signal from the Enemy class;
    if(value){
        Controller* contr = Controller::getInstance();
        MyWorld* world = contr->getWorld();
        unsigned int x = static_cast<unsigned int>(getXPos())+static_cast<unsigned int>(rand())%spawnRange;
        unsigned int y = static_cast<unsigned int>(getYPos())+static_cast<unsigned int>(rand())%spawnRange;
        MyTile* tile = world->getMapTile(static_cast<int>(x),static_cast<int>(y));

        for(unsigned int i=0;i<children;i++){
            int counter =0;
            while((tile==nullptr or tile->isWall() or world->tileContainsEnemy(tile) or world->tileContainsHealthpack(tile)) and counter <=10000){
                x=static_cast<unsigned int>(getXPos())+static_cast<unsigned int>(rand())%spawnRange;
                y=static_cast<unsigned int>(getYPos())+static_cast<unsigned int>(rand())%spawnRange;
                tile = world->getMapTile(static_cast<int>(x),static_cast<int>(y));
                counter ++;
            }
            float strength = this->getValue()/children;
            if(not(tile==nullptr or tile->isWall() or world->tileContainsEnemy(tile) or world->tileContainsHealthpack(tile))){
                std::shared_ptr<BabyEnemy> baby = std::make_shared<BabyEnemy>(x,y,strength);
                world->addEnemy(baby);
            }

        }
        switch (contr->getWindow()->getRotation()) {

            case 1:{
                world->sortenemies90();
            }
            case 2:{
                world->sortenemies180();
            }
            case 3:{
                world->sortenemies270();
            }
            default:{
                world->sortenemies0();
            }
        }
    }
}

void XEnemy::setDefeatedWithNoSpawn(bool value)
{
    Enemy::setDefeated(value);
}

unsigned int XEnemy::getChildren() const
{
    return children;
}

void XEnemy::setChildren(unsigned int value)
{
    children = value;
}

unsigned int XEnemy::getSpawnRange() const
{
    return spawnRange;
}

void XEnemy::setSpawnRange(unsigned int value)
{
    spawnRange = value;
}


