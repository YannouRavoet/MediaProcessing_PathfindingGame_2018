#ifndef PATHFINDING_H
#define PATHFINDING_H
#include <vector>
#include <queue>
#include "controller.h"
#include "helperclasses/mytile.h"
#include "helperclasses/myworld.h"

class Pathfinding
{
public:
    static Pathfinding* getInstance();
    //first call Pathfinding::initPF()
    std::vector<MyTile*> AStar();
    virtual ~Pathfinding()=default;

    //Called before Pathfinding::AStar(...)
    bool initPF();
    bool updateInit();

    MyTile* getStart() const;
    void setStart(MyTile* value);
    MyTile* getDest() const;
    void setDest(MyTile* value);
    float getHeurWeight() const;
    void setHeurWeight(float value);
    float getStepcost1() const;
    float getStepcost2() const;

private:
    Pathfinding();
    void initTile(MyTile* tile);
    void heuristicEstimate(MyTile* tile);
    /*JPS*/
    void JPSAllDir(MyTile* tile);

    void searchJumpPointUp(MyTile* start);
    void searchJumpPointUpRight(MyTile* start);
    void searchJumpPointRight(MyTile* start);
    void searchJumpPointDownRight(MyTile* start);
    void searchJumpPointDown(MyTile* start);
    void searchJumpPointDownLeft(MyTile* start);
    void searchJumpPointLeft(MyTile* start);
    void searchJumpPointUpLeft(MyTile* start);

    bool scanLeft(MyTile* cur);
    bool scanRight(MyTile* cur);
    bool scanUp(MyTile* cur);
    bool scanDown(MyTile* cur);

    bool forcedNeighbourRight(MyTile* tile);
    bool forcedNeighbourLeft(MyTile* tile);
    bool forcedNeighbourUp(MyTile* tile);
    bool forcedNeighbourDown(MyTile* tile);
    bool forcedNeighbourUpRight(MyTile* tile);
    bool forcedNeighbourDownRight(MyTile* tile);
    bool forcedNeighbourDownLeft(MyTile* tile);
    bool forcedNeighbourUpLeft(MyTile* tile);
    /*USED IF YOU PREPROCESS ALL TILES JUMP POINTS
    std::shared_ptr<MyTile> crossedDestColOrRow(std::shared_ptr<MyTile> cur, std::shared_ptr<MyTile> jumpPoint);
    bool destReachableFromTile(int cX,int cY,int dX,int dY);
    void processNewNode(std::shared_ptr<MyTile> tile,std::shared_ptr<MyTile> parent);*/
    std::vector<MyTile*> reconstructAStarPath(MyTile* current);
    std::vector<MyTile*> reconstructJPSPath(MyTile* current);
    void addIntermediateTiles(MyTile* current,std::vector<MyTile*>* path);

    static Pathfinding* instance;
    MyTile* start=nullptr;
    MyTile* dest=nullptr;
    MyWorld* world = nullptr;
    float stepcost1; float stepcost2; float heurWeight=1.00f;
    std::priority_queue<MyTile*, std::vector<MyTile*>, comp> open;
};

#endif // PATHFINDING_H
