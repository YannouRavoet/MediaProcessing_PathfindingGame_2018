#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <memory>
#include <QSound>
#include "views/mysplashscreen.h"
#include "helperclasses/myworld.h"
#include "helperclasses/direction.h"
class VictoryScreen;
class MainWindow;
class Pathfinding;

class Controller: public QObject
{
    Q_OBJECT
public:
    static Controller* getInstance();

    Controller(Controller const&)= delete;
    void operator=(Controller const&)  = delete;
    ~Controller();
    void init(QApplication *app , MySplashScreen *splash );

    void pathfindingShowCase();
    void sortMap();
    /*============== GETTERS AND SETTERS ============*/
    MainWindow *getWindow() const;
    Pathfinding *getPathfinding() const;
    MyWorld* getWorld() const;
    void setWorld(QString filename);
    bool getGameOver() const;
    void setGameOver(bool value);
    float getAutospeed() const;
    void setAutospeed(float value);
    QString getMapfile() const;
    void setMapfile(const QString &value);
    bool getAutoplayOn() const;
    void setAutoplayOn(bool value);
    std::vector<MyTile *> getSorted_map() const;
    void setSorted_map(const std::vector<MyTile *> &value);

    /*============== AUTOMATED PLAY METHODS =========*/
    void autoPlay();
    struct closestEnemy getClosestQuarterEnemy();
    struct closestHealthpack getClosestQuarterHealthpack();
    struct closestEnemy getClosestEnemy();
    struct closestHealthpack getClosestHealthpack();
    void followPath(std::vector<MyTile*> path);
    std::vector<MyTile*> findNonSuicidalPath();
    bool pathWillKillYou(std::vector<MyTile*> path);
    bool takeAWalk();

    /*================ PROTAGONIST MOVEMENT ==============*/
    /*Returns true if the move went through
      Returns false if destination was a wall
      Returns false if player did not have enough energy
      Returns false if dest was outside of map*/
    bool moveProtaDir(direction dir);
    bool moveProta(MyTile* tile);
    bool validDest(MyTile* tile);
    bool changeProtaPosition(MyTile* tile);
    void interactProtaWithTileObject();

    /*Returns true  if the attack went through
      Returns false if the enemy and player are not on the same tile
      Returns false if the enemy was already defeated
      Returns false if the player did not have enough health*/
    bool attackEnemy(std::shared_ptr<Enemy> enemy);

    /*Returns true  if the player has taken the healthpack
      Returns false if the pack and player are not on the same tile
      Returns false if the pack was already used
      Returns false if the player already had 100.0f health*/
    bool takeHealthPack(std::shared_ptr<MyHealthpack> healthpack);
    /*=================SOUND METHODS=======================*/
    bool isSoundDone();
    void playSound(unsigned int index);
    void stopSound();

    bool getTrackprotagonist() const;
    void setTrackprotagonist(bool value);
    void victory();
    void defeat();


public slots:
    void loadedsave();

private:
    Controller();
    static Controller* instance;
    bool trackprotagonist=true;
    bool gameOver=false;
    QString mapfile;
    std::vector<std::shared_ptr<QSound>> sounds;

    MyWorld* world;
    std::vector<MyTile*> sorted_map; //used for isometric rotation
    MainWindow* window;
    Pathfinding* pathfinding;
    bool autoplayOn = false;
    float autospeed=0.5;
    unsigned int walkcounter=0;
    MyTile* lastPos=nullptr;
};

struct closestEnemy{
    std::shared_ptr<Enemy> enemy = nullptr;
    std::vector<MyTile*> path;
    float cost = maxScore;
};

struct closestHealthpack{
    std::shared_ptr<MyHealthpack> healthpack = nullptr;
    std::vector<MyTile*> path;
    float cost = maxScore;
};

#endif // CONTROLLER_H
