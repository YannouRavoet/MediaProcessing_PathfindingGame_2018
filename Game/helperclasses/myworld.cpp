#include <random>
#include <unistd.h>
#include <algorithm>
#include "xenemy.h"
#include "myworld.h"
#include "pathfinding.h"
#include "controller.h"


MyWorld* MyWorld::instance;
MyWorld::MyWorld()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

MyWorld* MyWorld::getInstance(){
    if(instance==nullptr)
        instance=new MyWorld();
    return instance;
}

MyWorld::~MyWorld()
{
    for(MyTile* tile:map){
        delete tile;
        tile=nullptr;
    }
    map.clear();
}

std::vector<MyTile*> MyWorld::createWorld(QString filename)
{
    map.clear();
    hasGrayValue=false;
    std::vector<std::unique_ptr<Tile>> tiles = World::createWorld(filename);
    for(auto& tile: tiles){
        if(!hasGrayValue and tile->getValue()<1)
            hasGrayValue=true;
        map.push_back(new MyTile(tile.get()));
    }
    stepCost1=250/static_cast<float>(map.size());
    stepCost2=1.414f*stepCost1;
    if(hasGrayValue)
        updateTileNeighbours(); //sets the neighbours for every tile and calculates their cost (--pathfinding)
                                //else JPS initialization is done once the start and dest are known
    return map;
}
std::vector<std::shared_ptr<Enemy> > MyWorld::getEnemies(unsigned int nrOfEnemies)
{
    enemies.clear();
    std::vector<std::unique_ptr<Enemy>> uEnemies = World::getEnemies(nrOfEnemies);
    for(auto& enemy: uEnemies){
        enemies.push_back(move(enemy));
    }
    for(unsigned int i=0;i<(nrOfEnemies%3+1);i++){
        int x = rand()%getCols();
        int y = rand()%getRows();
        MyTile* tile = getMapTile(x,y);
        while(tile==nullptr or tile->isWall() or tileContainsEnemy(tile) or tileContainsHealthpack(tile)){
            x = rand()%getCols();
            y = rand()%getRows();
            tile = this->getMapTile(x,y);
        }
        std::shared_ptr<Enemy> enemy =std::shared_ptr<Enemy>(new XEnemy(x,y,rand()%65,rand()%8+1,rand()%5+1));
        enemies.push_back(move(enemy));
    }
    return enemies;
}
std::vector<std::shared_ptr<MyHealthpack>> MyWorld::getHealthPacks(unsigned int nrOfPacks)
{
    healthpacks.clear();
    int x=0;int y=0;
    MyTile* currentTile = this->getMapTile(x,y);
    for(unsigned int i=0;i<nrOfPacks;i++){
        while( (currentTile->getValue() <= 0) or (tileContainsEnemy(currentTile) or (tileContainsHealthpack(currentTile)))  ){//Spawning on Wall, Enemy or Healthpack
            x = rand()%getCols();
            y = rand()%getRows();
            currentTile = this->getMapTile(x,y);
        }
        //removing /100 for it since this will cause the healthpack to have a value between 0-1 resulting in no health gained
        healthpacks.push_back(std::make_shared<MyHealthpack>(x,y,(rand()%100)));
    }
    return healthpacks;
}
std::shared_ptr<MyProtagonist> MyWorld::getProtagonist()
{
    int x=0; int y=0;
    MyTile* currentTile = getMapTile(x,y);
    while( (currentTile->getValue() <= 0) or (tileContainsEnemy(currentTile) or (tileContainsHealthpack(currentTile)))  ){//Spawning on Wall, Enemy or Healthpack
        x = rand()%getCols();
        y = rand()%getRows();
        currentTile = this->getMapTile(x,y);
    }
    prota =  std::make_shared<MyProtagonist>(x,y);
    return prota;
}

void MyWorld::updateTileNeighbours()
{
    for(MyTile* tile: map){
        if(tile->getValue()<=0)
            continue;
        tile->clearNeighbours();
        int x= tile->getXPos();
        int y= tile->getYPos();
        for(int r=std::max(y-1,0); r<=std::min(y+1,this->getRows()-1); r++){
            for(int c=std::max(x-1,0); c<=std::min(x+1,this->getCols()-1); c++){
                if((r!=y or c!=x) and (map[static_cast<unsigned int>(r*this->getCols()+c)]->getValue()>0)){ //if != tile AND !wall
                    float cost = costBetween(tile,map[static_cast<unsigned int>(r*this->getCols()+c)]);
                    std::pair<MyTile*,float> neighbour(map[static_cast<unsigned int>(r*this->getCols()+c)],cost);
                    tile->addNeighbour(neighbour);
                }
            }
        }
    }
}

/*CONSTRAINTS: never gets a wall AND tile1 != tile2*/
float MyWorld::costBetween(MyTile* tile1, MyTile* tile2)
{
    if (tile2->getXPos()==tile1->getXPos() or tile2->getYPos()==tile1->getYPos())
        return std::abs(tile1->getValue()-tile2->getValue())+stepCost1; //horizontal cost
    return std::abs(tile1->getValue()-tile2->getValue())+stepCost2; //diagonal cost
}


MyTile* MyWorld::getMapTile(int x,int y)
{
    if( x<0 or y<0 or x>=getCols() or y>=getRows() )
        return nullptr;
    return map[getCols()*y+x];
}
MyTile* MyWorld::getMapTile(int index)
{
    if(index<0 or index>=static_cast<int>(map.size()))
        return nullptr;
    return map[static_cast<unsigned long>(index)];
}

MyTile *MyWorld::getMapTileUnchecked(int x, int y)
{
    return map[getCols()*y+x];
}

std::vector<MyTile *> MyWorld::getNeighbours(MyTile *tile)
{
    int x = tile->getXPos();
    int y = tile->getYPos();
    return getNeighbours(x,y);
}

std::vector<MyTile *> MyWorld::getNeighbours(int x, int y)
{
    std::vector<MyTile*> neighbours;
    neighbours.push_back(getMapTile(--x,y));
    neighbours.push_back(getMapTile(x,--y));
    neighbours.push_back(getMapTile(++x,y));
    neighbours.push_back(getMapTile(++x,y));
    neighbours.push_back(getMapTile(x,++y));
    neighbours.push_back(getMapTile(x,++y));
    neighbours.push_back(getMapTile(--x,y));
    neighbours.push_back(getMapTile(--x,y));
    return neighbours;
}
std::shared_ptr<Enemy> MyWorld::tileContainsEnemy(MyTile* tile)
{
    for(std::shared_ptr<Enemy> enemy: enemies){
        if (enemy->getXPos() == tile->getXPos() and enemy->getYPos()==tile->getYPos())
            return enemy;
    }
    return nullptr;
}
std::shared_ptr<Enemy>  MyWorld::tileContainsEnemy(int x, int y)
{
    return tileContainsEnemy(getMapTile(x,y));
}
std::shared_ptr<Enemy>  MyWorld::tileContainsEnemy(int index)
{
    return tileContainsEnemy(getMapTile(index));
}
std::shared_ptr<Enemy>  MyWorld::tileContainsLivingEnemy(MyTile* tile)
{
    for(std::shared_ptr<Enemy> enemy: enemies){
        if (enemy->getXPos() == tile->getXPos() and enemy->getYPos()==tile->getYPos() and enemy->getDefeated()==false)
            return enemy;
    }
    return nullptr;
}
std::shared_ptr<Enemy>  MyWorld::tileContainsLivingEnemy(int x, int y)
{
    return tileContainsLivingEnemy(getMapTile(x,y));
}
std::shared_ptr<Enemy>  MyWorld::tileContainsLivingEnemy(int index)
{
    return tileContainsLivingEnemy(getMapTile(index));
}

std::shared_ptr<MyHealthpack>  MyWorld::tileContainsHealthpack(MyTile* tile)
{
    for(std::shared_ptr<MyHealthpack> healthpack: this->healthpacks){
        if(healthpack->getX()==tile->getXPos() and healthpack->getY()==tile->getYPos())
            return healthpack;
    }
    return nullptr;
}
std::shared_ptr<MyHealthpack> MyWorld::tileContainsHealthpack(int x,int y)
{
    return tileContainsHealthpack(getMapTile(x,y));
}
std::shared_ptr<MyHealthpack> MyWorld::tileContainsHealthpack(int index)
{
    return tileContainsHealthpack(getMapTile(index));
}

void MyWorld::addEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies.push_back(enemy);
}

/*====================    AUTOMATED PLAY    ============================*/

bool MyWorld::allEnemiesDefeated()
{
    for(std::shared_ptr<Enemy> enemy:enemies){
        if(!enemy->getDefeated())
            return false;
    }
    return true;
}
std::vector<std::shared_ptr<Enemy> > MyWorld::getLivingEnemies()
{
    std::vector<std::shared_ptr<Enemy>> livingEnemies;
    for(std::shared_ptr<Enemy> enemy: enemies){
        if(!enemy->getDefeated())
            livingEnemies.push_back(enemy);
    }
    return livingEnemies;
}
std::vector<std::shared_ptr<MyHealthpack> > MyWorld::getUnusedHealthpacks()
{
    std::vector<std::shared_ptr<MyHealthpack>> Unusedhp;
    for(std::shared_ptr<MyHealthpack> hp: healthpacks){
        if(!hp->getUsed())
            Unusedhp.push_back(hp);
    }
    return Unusedhp;
}

/*==================== GETTERS AND SETTERS MyWorld ============================*/

std::vector<MyTile*> MyWorld::getMap() const
{
    return map;
}
void MyWorld::setMap(const std::vector<MyTile*> &value)
{
    map = value;
}
std::vector<std::shared_ptr<Enemy>> MyWorld::getEnemies() const
{
    return enemies;
}
void MyWorld::setEnemies(const std::vector<std::shared_ptr<Enemy> > &value)
{
    enemies = value;
}
std::vector<std::shared_ptr<MyHealthpack>> MyWorld::getHealthpacks() const
{
    return healthpacks;
}
void MyWorld::setHealthpacks(const std::vector<std::shared_ptr<MyHealthpack> > &value)
{
    healthpacks = value;
}
std::shared_ptr<MyProtagonist> MyWorld::getProta() const
{
    return prota;
}
void MyWorld::setProta(const std::shared_ptr<MyProtagonist> &value)
{
    prota = value;
}
bool MyWorld::getHasGrayValue() const
{
    return hasGrayValue;
}
float MyWorld::getStepCost1() const
{
    return stepCost1;
}
void MyWorld::setStepCost1(float value)
{
    stepCost1 = value;
}
float MyWorld::getStepCost2() const
{
    return stepCost2;
}
void MyWorld::setStepCost2(float value)
{
    stepCost2 = value;
}
void MyWorld::setStepCosts(float cost1, float cost2)
{
    stepCost1=cost1;
    stepCost2=cost2;
    if(hasGrayValue)
        updateTileNeighbours();
}



/*============================ SORTERS ===========================================*/
void MyWorld::sortHealthpacks0(){

    std::sort(healthpacks.begin(), healthpacks.end(),
              [](const std::shared_ptr<MyHealthpack> a, const std::shared_ptr<MyHealthpack> b) -> bool
    {
        if(a->getX()==b->getX()){
            return a->getY() <b->getY();
        }
        return a->getX() <b->getX();

    });

}
void MyWorld::sortHealthpacks90()
{
    std::sort(healthpacks.begin(), healthpacks.end(),
              [](const std::shared_ptr<MyHealthpack> a, const std::shared_ptr<MyHealthpack> b) -> bool
    {
        if(a->getX()==b->getX()){
            return a->getY() <b->getY();
        }
        return a->getX() >b->getX();

    });

}
void MyWorld::sortHealthpacks180()
{
    std::sort(healthpacks.begin(), healthpacks.end(),
              [](const std::shared_ptr<MyHealthpack> a, const std::shared_ptr<MyHealthpack> b) -> bool
    {
        if(a->getX()==b->getX()){
            return a->getY() >b->getY();
        }
        return a->getX() >b->getX();

    });

}
void MyWorld::sortHealthpacks270()
{
    std::sort(healthpacks.begin(), healthpacks.end(),
              [](const std::shared_ptr<MyHealthpack> a, const std::shared_ptr<MyHealthpack> b) -> bool
    {
        if(a->getX()==b->getX()){
            return a->getY() >b->getY();
        }
        return a->getX() <b->getX();

    });

}

void MyWorld::sortenemies0()
{

    std::sort(enemies.begin(), enemies.end(),
              [](const std::shared_ptr<Enemy> a, const std::shared_ptr<Enemy> b) -> bool
    {
        if(a->getXPos()==b->getXPos()){
            return a->getYPos() <b->getYPos();
        }
        return a->getXPos() <b->getXPos();

    });

}
void MyWorld::sortenemies90()
{
    std::sort(enemies.begin(), enemies.end(),
              [](const std::shared_ptr<Enemy> a, const std::shared_ptr<Enemy> b) -> bool
    {
        if(a->getYPos()==b->getYPos()){
            return a->getXPos() <b->getXPos();
        }
        return a->getYPos() >b->getYPos();

    });

}
void MyWorld::sortenemies180()
{
    std::sort(enemies.begin(), enemies.end(),
              [](const std::shared_ptr<Enemy> a, const std::shared_ptr<Enemy> b) -> bool
    {
        if(a->getXPos()==b->getXPos()){
            return a->getYPos() >b->getYPos();
        }
        return a->getXPos() >b->getXPos();

    });

}
void MyWorld::sortenemies270()
{
    std::sort(enemies.begin(), enemies.end(),
              [](const std::shared_ptr<Enemy> a, const std::shared_ptr<Enemy> b) -> bool
    {
        if(a->getYPos()==b->getYPos()){
            return a->getXPos() >b->getXPos();
        }
        return a->getYPos() <b->getYPos();

    });

}
/*================================================================================*/
