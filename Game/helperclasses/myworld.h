#ifndef MYWORLD_H
#define MYWORLD_H

#include "world.h"
#include "mytile.h"
#include "direction.h"
#include "myprotagonist.h"
#include "myhealthpack.h"


class MyWorld: public World
{
public:
    static MyWorld* getInstance();
    virtual ~MyWorld();

    std::vector<MyTile*> createWorld(QString filename);
    std::vector<std::shared_ptr<Enemy>> getEnemies(unsigned int nrOfEnemies);
    std::vector<std::shared_ptr<MyHealthpack>> getHealthPacks(unsigned int nrOfPacks);
    std::shared_ptr<MyProtagonist> getProtagonist();

    /*Returns nullptr if tile would be out of bounds*/
    MyTile* getMapTile(int x, int y);
    MyTile* getMapTile(int index);
    MyTile* getMapTileUnchecked(int x,int y);
    std::vector<MyTile*> getNeighbours(MyTile* tile);
    std::vector<MyTile*> getNeighbours(int x,int y);
    float costBetween(MyTile* tile1, MyTile* tile2);

    std::shared_ptr<Enemy>  tileContainsEnemy(MyTile* tile);
    std::shared_ptr<Enemy>  tileContainsEnemy(int x,int y);
    std::shared_ptr<Enemy>  tileContainsEnemy(int index);
    std::shared_ptr<Enemy>  tileContainsLivingEnemy(MyTile* tile);
    std::shared_ptr<Enemy>  tileContainsLivingEnemy(int x,int y);
    std::shared_ptr<Enemy>  tileContainsLivingEnemy(int index);
    std::shared_ptr<MyHealthpack> tileContainsHealthpack(MyTile* tile);
    std::shared_ptr<MyHealthpack> tileContainsHealthpack(int x,int y);
    std::shared_ptr<MyHealthpack> tileContainsHealthpack(int index);

    void addEnemy(std::shared_ptr<Enemy> enemy);

    /*====================    AUTOMATED PLAY    ============================*/
    bool allEnemiesDefeated();
    std::vector<std::shared_ptr<Enemy>> getLivingEnemies();
    std::vector<std::shared_ptr<MyHealthpack>> getUnusedHealthpacks();

    /*==================== GETTERS AND SETTERS ============================*/
    std::vector<MyTile*> getMap() const;
    void setMap(const std::vector<MyTile*> &value);
    std::vector<std::shared_ptr<Enemy> > getEnemies() const;
    void setEnemies(const std::vector<std::shared_ptr<Enemy> > &value);
    std::vector<std::shared_ptr<MyHealthpack> > getHealthpacks() const;
    void setHealthpacks(const std::vector<std::shared_ptr<MyHealthpack> > &value);
    std::shared_ptr<MyProtagonist> getProta() const;
    void setProta(const std::shared_ptr<MyProtagonist> &value);

    void setRows(int rows);
    void setCols(int rows);

    bool getHasGrayValue() const;
    float getStepCost1() const;
    void setStepCost1(float value);
    float getStepCost2() const;
    void setStepCost2(float value);
    void setStepCosts(float cost1,float cost2);
    /*=====================================================================*/


    /*======================SORTERS========================================*/
    void sortHealthpacks0();
    void sortHealthpacks90();
    void sortHealthpacks180();
    void sortHealthpacks270();
    void sortenemies0();
    void sortenemies90();
    void sortenemies180();
    void sortenemies270();
    /*=====================================================================*/



private:
    MyWorld();
    void updateTileNeighbours();
    float stepCost1; float stepCost2;
    bool hasGrayValue = false; //is set to true in createWorld if the world contains grayValues
    /*USEFUL FOR EVERYONE*/
    std::vector<MyTile*> map;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<MyHealthpack>> healthpacks;
    std::shared_ptr<MyProtagonist> prota;
    static MyWorld* instance;


};

#endif // MYWORLD_H
