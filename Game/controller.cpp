#include "controller.h"


#include <memory>
#include <chrono>
#include <QSound>
#include <unistd.h>
#include "pathfinding.h"
#include "victoryscreen.h"
#include "defeatscreen.h"
#include "views/viewone.h"
#include "views/isometricview.h"
#include "views/mysplashscreen.h"
#include "helperclasses/myworld.h"
#include "helperclasses/myprotagonist.h"
#include "helperclasses/xenemy.h"


Controller* Controller::instance = nullptr;

Controller::Controller(){
}

std::vector<MyTile *> Controller::getSorted_map() const
{
    return sorted_map;
}

void Controller::setSorted_map(const std::vector<MyTile *> &value)
{
    sorted_map = value;
}
Controller* Controller::getInstance()
{
    if(instance == nullptr)
        instance = new Controller();
    return instance;

}

Controller::~Controller()
{
    if(lastPos!=nullptr)
        delete lastPos;
    for(MyTile* tile:sorted_map)
         tile->~MyTile();
    delete pathfinding;
    delete world;
}

void Controller::init(QApplication *app , MySplashScreen *splash )
{
    pathfinding = Pathfinding::getInstance();
    window = new MainWindow();

    splash->showMessage("Finding Lego to construct Maze");
    app->processEvents();
    QString map_file = "../Game/img/minimaze_20x20.png";
    setMapfile(map_file);
    world = MyWorld::getInstance();
    setWorld(map_file);
    connect(window, SIGNAL(newMapLoaded()), this, SLOT(loadedsave()));
    // index 0 = enemy death;
    // index 1 = player death;
    // index 2 = victory;
    // index 3 = autoplay startlocation select;
    // index 4 = low health;
    // index 5 = healthpackpickup;
    // index 6 = rotationsound;
    // index 7 = autoplaystart;
    // index 8 = impossible game sound;
    // index 9 = closing game sound;
    sounds.push_back(std::make_shared<QSound>(":/audio/enemyDeath.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/playerDeath.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/victorySound.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/autoplaystartlocation.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/lowHealthEffect.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/HpPackPickup.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/rotatingSound.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/autoplaystart.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/impossibleFile.wav"));
    sounds.push_back(std::make_shared<QSound>(":/audio/closingsound.wav"));

    gameOver=false;


    /*PATHFINDING INIT*/
    splash->showMessage("inflating the autopilot ");
    app->processEvents();
    window->addTextToOutput("===============  USEFULL START AND DEST  ==================\n");
    window->addTextToOutput("maze1.png: start=(0,492), dest=(494,6)\n");
    window->addTextToOutput("maze2.png: start=(796,242), dest=(441,209)\n");
    window->addTextToOutput("maze3.png: start=(35,34), dest=(1255,1211)\n");
    window->addTextToOutput("worldmap4.png: start=(0,44), dest=(999,937)\n");
    window->addTextToOutput("minimaze_10x10.png: start=(9,0), dest=(2,6)\n");
    window->addTextToOutput("minimaze_20x20.png: start=(0,18), dest=(18,8)\n");
    window->addTextToOutput("minimaze_10x10_BW.png: start=(0,1), dest=(4,4)/dest=(8,8)\n");
    window->addTextToOutput("minimaze_40x40_BW.png: start=(0,1), dest=(34,35)\n");
    window->addTextToOutput("=========================================================\n");
    int b = 360;
    int d = 38;
    pathfinding->setStart(world->getMapTile(b));
    pathfinding->setDest(world->getMapTile(d));
    pathfinding->setHeurWeight(0);
    pathfinding->initPF();
    connect(world->getProta().get(), SIGNAL(energyChanged(int)), window, SLOT(energyChanged(int)));
    connect(world->getProta().get(), SIGNAL(healthChanged(int)), window, SLOT(healthChanged(int)));

    splash->showMessage("Drawing everything ");
    app->processEvents();
    ViewOne::getInstance()->initViewOne(mapfile);
    window->setViewone(ViewOne::getInstance());
    sortMap();
    isometricView::getInstance()->draw_world();
    window->show();
    ViewOne::getInstance()->updateScaleFactor();

    trackprotagonist=false;
}

void Controller::victory()
{
    stopSound();
    window->addTextToOutput("You won...\n");
    gameOver=true;
    playSound(2);
    new VictoryScreen();
}
void Controller::defeat()
{

    stopSound();
    world->getProta()->setHealth(0);
    window->updateHealthvalue(0);
    window->addTextToOutput("You died...\n");
    gameOver=true;
    autoplayOn=false;
    playSound(1);
    new DefeatScreen();

}
void Controller::pathfindingShowCase(){
    playSound(3);
    /*PRINT OUTPUT*/
    window->addTextToOutput("======================  PATHFINDING  ======================\n");
    window->addTextToOutput("start: x(" + QString::number(pathfinding->getStart()->getXPos())+ ")-y(" + QString::number(pathfinding->getStart()->getYPos()) + ")  end: x("+QString::number(pathfinding->getDest()->getXPos())+")-y("+QString::number(pathfinding->getDest()->getYPos())+")\n");
    window->addTextToOutput("Stepcost1: " + QString::number(static_cast<double>(world->getStepCost1()))+"   ");
    window->addTextToOutput("Stepcost2: " + QString::number(static_cast<double>(world->getStepCost2()))+"   ");
    window->addTextToOutput("Heuristic Weight: " + QString::number(static_cast<double>(pathfinding->getHeurWeight()))+"\n");
    auto s=std::chrono::high_resolution_clock::now();
    std::vector<MyTile *> path = pathfinding->AStar();
    auto e=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = e-s;
    window->addTextToOutput("Pathfinding took: " + QString::number(elapsed.count(),'f',3)+" seconds   -   ");
    if(path.size()==0){
        window->addTextToOutput("No path was found.\n");
    }
    else
        window->addTextToOutput("Path cost: " + QString::number(static_cast<double>(pathfinding->getDest()->getGScore()),'f',3)+".\n");
    window->addTextToOutput("=========================================================\n");
    /*VISUALIZATION*/
    ViewOne::getInstance()->showPath(path);
}

void Controller::sortMap()
{
    //fix this for rotation so no sorting is necessary here.
    sorted_map.clear();
    for(auto& tile: world->getMap())
        sorted_map.push_back(tile);
    MainWindow* window = getWindow();
    std::sort(sorted_map.begin(), sorted_map.end(),
              [window](const MyTile* a, const MyTile* b) -> bool
    {
        switch (window->getRotation()) {

            case 1:{
                if(a->getYPos()==b->getYPos())
                    return a->getXPos() <b->getXPos();
                return a->getYPos() >b->getYPos();
            }
            case 2:{

                if(a->getXPos()==b->getXPos())
                    return a->getYPos() >b->getYPos();
                return a->getXPos() >b->getXPos();
            }
            case 3:{

                if(a->getYPos()==b->getYPos())
                    return a->getXPos() >b->getXPos();
                return a->getYPos() <b->getYPos();
            }
            default:{
                if(a->getXPos()==b->getXPos())
                    return a->getYPos() <b->getYPos();
                return a->getXPos() <b->getXPos();

            }
        }
    });
}

/*======================================= GETTERS AND SETTERS ============================================*/
Pathfinding *Controller::getPathfinding() const
{
    return pathfinding;
}
MainWindow *Controller::getWindow() const
{
    return window;
}
void Controller::setWorld(QString filename)
{
    autoplayOn=false;
    mapfile = filename;
    world->createWorld(filename);
    unsigned int nrOfEnemies=(static_cast<unsigned int>(world->getRows())/5);
    if(nrOfEnemies<=1){
        nrOfEnemies=2;
    }
    if(nrOfEnemies>25){
        nrOfEnemies=25;
    }
    //two times more healthpacks then enemies
    unsigned int nrOfHealhpacks = nrOfEnemies*2;
    world->getEnemies(nrOfEnemies);
    world->getHealthPacks(nrOfHealhpacks);
    world->getProtagonist();
    world->sortHealthpacks0();
    world->sortenemies0();

    /*UPDATE UI*/
    window->updateEnemyLabels();
    window->updateStepCostLabels(static_cast<double>(world->getStepCost1()),static_cast<double>(world->getStepCost2()));
    window->updateMaximumXandY(world->getCols()-1,world->getRows()-1);
    window->setImgLabel(mapfile);
}
MyWorld* Controller::getWorld() const
{
    return world;
}
bool Controller::getGameOver() const
{
    return gameOver;
}
void Controller::setGameOver(bool value)
{
    gameOver = value;
}
bool Controller::getAutoplayOn() const
{
    return autoplayOn;
}
void Controller::setAutoplayOn(bool value)
{
    autoplayOn = value;
}
float Controller::getAutospeed() const
{
    return autospeed;
}
void Controller::setAutospeed(float value)
{
    autospeed = value;
}
QString Controller::getMapfile() const
{
    return mapfile;
}
void Controller::setMapfile(const QString &value)
{
    mapfile = value;
}
bool Controller::getTrackprotagonist() const
{
    return trackprotagonist;
}
void Controller::setTrackprotagonist(bool value)
{
    trackprotagonist = value;
}


/*======================================= AUTOMATED PLAY METHODS =========================================*/

void Controller::autoPlay()
{
    autoplayOn=!autoplayOn;
    if(!autoplayOn)
        return;
    playSound(7);
    std::shared_ptr<MyProtagonist> prota = world->getProta();
    while(!world->allEnemiesDefeated() and autoplayOn){
        /*== Get closest enemy ==*/
        int x = prota->getXPos();
        int y = prota->getYPos();
        pathfinding->setStart(world->getMapTile(x,y));
        window->addTextToOutput("Scanning targets...\n");
        QCoreApplication::processEvents();
        struct closestEnemy closeBoy = getClosestQuarterEnemy();

        /*== See if enemy is reachable ==*/
        if(closeBoy.cost>prota->getEnergy()){
            window->getViewone()->showPath(closeBoy.path);
            window->addTextToOutput(QString("Cannot reach closest enemy (cost: ").append(QString::number(static_cast<double>(closeBoy.cost))).append(QString(")... autoplay cannot finish the game.\n")));
            playSound(8);
            autoplayOn=false;
            return;
        }
        /*== See if enemy is too strong ==*/
        if(prota->getHealth()<=closeBoy.enemy->getValue()){
            window->addTextToOutput("Closest enemy is too strong...\n->Redirecting to closest healthpack.\n");
            QCoreApplication::processEvents();
            struct closestHealthpack closeHP = getClosestQuarterHealthpack();
            if(closeHP.healthpack==nullptr){
                playSound(8);
                if(walkcounter>=20) //random walk didn't work
                    window->addTextToOutput("Machines are unable to calculate this madness... This requires biological intelligence.\n ");
                else
                    window->addTextToOutput("NO MORE HEALTHPACKS!!! Lordy, lordy... we are doomed.\n ");
                autoplayOn=false;
                return;
            }
            window->getViewone()->showPath(closeHP.path);
            if(closeHP.cost>prota->getEnergy()){
                playSound(8);
                window->addTextToOutput(QString("Cannot reach closest healthpack (cost: ").append(QString::number(static_cast<double>(closeHP.cost))).append(QString("... I'm very sorry, but you are done.\n")));
                autoplayOn=false;
                return;
            }
            window->addTextToOutput("Nom nom nom, juicy healthpack.\n");
            followPath(closeHP.path);
        }
        else{
            window->getViewone()->showPath(closeBoy.path);
            window->addTextToOutput("Target acquired...\n");
            followPath(closeBoy.path);
        }
    }
    if(autoplayOn)
        window->addTextToOutput("=>Congratulations, you have won!\n");
    else
        window->addTextToOutput("Machines are put in rest mode!\n");
    autoplayOn=false;
    return;
}
struct closestEnemy Controller::getClosestQuarterEnemy()
{
    struct closestEnemy min;
    std::vector<std::shared_ptr<Enemy>> enemies = world->getLivingEnemies();
    unsigned int count = 0;
    for(std::shared_ptr<Enemy> enemy: enemies){
        int ex = enemy->getXPos();
        int ey = enemy->getYPos();
        int px = world->getProta()->getXPos();
        int py = world->getProta()->getYPos();
        int cols = world->getCols();
        int rows = world->getRows();
        if(ex>px+cols/4 or ex < px-cols/4 or ey>py+rows/4 or ey<py-rows/4)
            continue;
        count++;
        MyTile* eTile = world->getMapTile(ex,ey);
        pathfinding->setDest(eTile);
        pathfinding->initPF();
        std::vector<MyTile*> path = pathfinding->AStar();
        float cost = eTile->getGScore();
        if(cost<min.cost){
            min.enemy = enemy;
            min.path = path;
            min.cost = cost;
        }
    }
    if(count==0)
        return getClosestEnemy();
    return min;
}
struct closestHealthpack Controller::getClosestQuarterHealthpack()
{
    struct closestHealthpack min;
    std::vector<std::shared_ptr<MyHealthpack>> healthpacks = world->getUnusedHealthpacks();
    for(std::shared_ptr<MyHealthpack> hp: healthpacks){
        int hx = hp->getX();
        int hy = hp->getY();
        int px = world->getProta()->getXPos();
        int py = world->getProta()->getYPos();
        int cols = world->getCols();
        int rows = world->getRows();
        if(hx>px+cols/4 or hx < px-cols/4 or hy>py+rows/4 or hy<py-rows/4)
            continue;
        MyTile* hTile = world->getMapTile(hx,hy);
        pathfinding->setDest(hTile);
        pathfinding->initPF();
        std::vector<MyTile*> path = pathfinding->AStar();
        if(pathWillKillYou(path))
            continue;
        float cost = hTile->getGScore();
        if(cost<min.cost){
            min.healthpack = hp;
            min.path = path;
            min.cost = cost;
        }
    }
    if(min.healthpack==nullptr)
        return getClosestHealthpack();
    return min;
}
struct closestEnemy Controller::getClosestEnemy()
{
    struct closestEnemy min;
    std::vector<std::shared_ptr<Enemy>> enemies = world->getLivingEnemies();
    for(std::shared_ptr<Enemy> enemy: enemies){
        int ex = enemy->getXPos();
        int ey = enemy->getYPos();
        MyTile* eTile = world->getMapTile(ex,ey);
        pathfinding->setDest(eTile);
        pathfinding->initPF();
        std::vector<MyTile*> path = pathfinding->AStar();
        float cost = eTile->getGScore();
        if(cost<min.cost){
            min.enemy = enemy;
            min.path = path;
            min.cost = cost;
        }
    }
    return min;
}
struct closestHealthpack Controller::getClosestHealthpack(){
    struct closestHealthpack min;
    std::vector<std::shared_ptr<MyHealthpack>> healthpacks = world->getUnusedHealthpacks();
    for(std::shared_ptr<MyHealthpack> hp: healthpacks){
        int hx = hp->getX();
        int hy = hp->getY();
        MyTile* hTile = world->getMapTile(hx,hy);
        pathfinding->setDest(hTile);
        pathfinding->initPF();
        std::vector<MyTile*> path = pathfinding->AStar();
        if(pathWillKillYou(path))
            continue;
        float cost = hTile->getGScore();
        if(cost<min.cost){
            min.healthpack = hp;
            min.path = path;
            min.cost = cost;
        }
    }
    if(min.healthpack==nullptr and healthpacks.size()!=0){
        walkcounter=0;
        std::vector<MyTile*>path=findNonSuicidalPath();
        if(path.size()>0){
            min.healthpack=world->tileContainsHealthpack(pathfinding->getDest());
            min.cost = pathfinding->getDest()->getGScore();
            min.path = path;
        }
    }
    return min;
}
void Controller::followPath(std::vector<MyTile*> path)
{
    for(MyTile* tile: path){
        moveProta(tile);//only comes here if path is valid -> so no need to check energy
        usleep(static_cast<__useconds_t>(500000/autospeed));
    }
}
std::vector<MyTile*> Controller::findNonSuicidalPath()
{
    pathfinding->initPF();
    std::vector<MyTile*> path = pathfinding->AStar();
    window->getViewone()->showPath(path);
    QApplication::processEvents();
    if(!pathWillKillYou(path))
        return path;
    if(takeAWalk() and ++walkcounter<20) //will try to move the protagonist away
        return findNonSuicidalPath();
    return {};

}
bool Controller::pathWillKillYou(std::vector<MyTile *> path)
{
    float health = world->getProta()->getHealth();
    for(MyTile* tile:path){
        std::shared_ptr<Enemy> enemy = world->tileContainsLivingEnemy(tile);
        if(enemy!=nullptr){
            health-=enemy->getValue();
            if(health<=0)
                return true;
        }
    }
    return false;
}
bool Controller::takeAWalk(){
    int pX = world->getProta()->getXPos();
    int pY = world->getProta()->getYPos();
    std::vector<MyTile*> neighbours = world->getNeighbours(pX,pY);
    for(unsigned int i=0;i<neighbours.size();i++){
        if(validDest(neighbours[i]) and !world->tileContainsLivingEnemy(neighbours[i]) and neighbours[i]!=lastPos){
            lastPos=world->getMapTile(pX,pY);
            moveProta(neighbours[i]);
            pathfinding->setStart(neighbours[i]);
            return true;
        }
    }
    return false;

}

/*================ PROTAGONIST MOVEMENT ==============*/
bool Controller::moveProtaDir(direction dir)
{
    int x = world->getProta()->getXPos();
    int y = world->getProta()->getYPos();
    MyTile* dest;
    switch (dir) {
        case UP:
            dest = world->getMapTile(x,y-1);
        break;
        case DOWN:
            dest = world->getMapTile(x,y+1);
        break;
        case RIGHT:
            dest = world->getMapTile(x+1,y);
        break;
        case LEFT:
            dest = world->getMapTile(x-1,y);
        break;
    }
    return moveProta(dest);
}
bool Controller::moveProta(MyTile* tile){
    if(!validDest(tile))
        return false;
    /*Valid action*/
    if(!changeProtaPosition(tile)){ //prota died because he did not have enough energy
        defeat();
        return true;
    }
    interactProtaWithTileObject(); //if tile contains enemy or healthpack
    if(window->getCurrentTabIndex()==0)
        window->getViewone()->refreshSceneImage();
    else
        window->getIsometricview()->draw_world();
    QCoreApplication::processEvents();
    return true;
}
bool Controller::validDest(MyTile *tile)
{
    if(tile==nullptr) //out of bounds
        return false;
    if(tile->isWall())//wall
        return false;
    return true;
}
bool Controller::changeProtaPosition(MyTile *tile)
{
    std::shared_ptr<MyProtagonist> prota = world->getProta();
    float cost = world->costBetween(world->getMapTile(prota->getXPos(),prota->getYPos()),tile);
    prota->setPos(tile->getXPos(),tile->getYPos()); //these methods already emit the signal
    prota->setEnergy(prota->getEnergy()-cost);
    if(prota->getEnergy()<0)
        return false;
    if(prota->getHealth() <=25)
        playSound(4);
    return true;
}
void Controller::interactProtaWithTileObject()
{
    std::shared_ptr<MyProtagonist> prota = world->getProta();
    std::shared_ptr<Enemy> tileEnemy = world->tileContainsLivingEnemy(prota->getXPos(),prota->getYPos());
    if(tileEnemy != nullptr)
        attackEnemy(tileEnemy); //checks if victory is achieved
    std::shared_ptr<MyHealthpack> tileHealthpack = world->tileContainsHealthpack(prota->getXPos(),prota->getYPos());
    if(tileHealthpack!=nullptr){
        takeHealthPack(tileHealthpack);
    }
}
bool Controller::attackEnemy(std::shared_ptr<Enemy> enemy)
{
    std::shared_ptr<MyProtagonist> prota = world->getProta();
    /*Invalid action*/
    if( (enemy->getXPos() != prota->getXPos()) or (enemy->getYPos() != prota->getYPos()) )
        return false;
    if(enemy->getDefeated())
        return false;
    /*Valid action*/
    if(enemy->getValue()>=prota->getHealth()){
        defeat();
        return false;
    }
    playSound(0);
    window->updateEnemyLabels();
    prota->setHealth(prota->getHealth()-enemy->getValue());
    prota->setEnergy(100.0f); //killing an enemy restores energy
    if(dynamic_cast<XEnemy*>(enemy.get()))
        dynamic_cast<XEnemy*>(enemy.get())->setDefeated(true);
    else
        enemy->setDefeated(true);
    if(world->allEnemiesDefeated())
        victory();
    return true;
}
bool Controller::takeHealthPack(std::shared_ptr<MyHealthpack> healthpack)
{   std::shared_ptr<MyProtagonist> prota = world->getProta();
    /*Invalid action*/
    if( (healthpack->getX() != prota->getXPos()) or (healthpack->getY() != prota->getYPos()))
        return false;
    if(healthpack->getUsed())
        return false;
    if(prota->getHealth() == 100.0f)
        return false;

    /*Valid action*/
    float newHealth = std::min(100.0f,prota->getHealth()+healthpack->getHealth());
    prota->setHealth(newHealth);
    healthpack->setUsed(true);
    playSound(5);
    return true;
}

/*=================SOUND METHODS=======================*/
bool Controller::isSoundDone()
{
    for (std::shared_ptr<QSound> sound : sounds){
        if(!sound->isFinished()){
            return false;
        }
    }
    return true;
}
void Controller::playSound(unsigned int index)
{
    if(index < sounds.size() and isSoundDone()){
        sounds[index]->play();
    }
}
void Controller::stopSound()
{
    for (std::shared_ptr<QSound> sound : sounds){
        sound->stop();
    }

}


/*=========================================== player inputs ===============================================*/
void Controller::loadedsave()
{
    window->updateEnergyvalue(static_cast<int>(world->getProta()->getEnergy()));
    window->updateHealthvalue(static_cast<int>(world->getProta()->getHealth()));
}



