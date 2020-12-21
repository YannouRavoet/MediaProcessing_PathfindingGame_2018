#ifndef MYTILE_H
#define MYTILE_H

#include "world.h"

static const float maxScore=10000;
class MyTile: public Tile
{
public:
    MyTile(int col, int row, float value); //xPos = col, yPos = row, value should be between 0 and 1
    MyTile(Tile* tile);
    virtual ~MyTile()=default;
    bool isWall();
    bool operator==(const MyTile& other) const{
        return other.getXPos()==getXPos() and other.getYPos()==getYPos();
    }
    bool operator!=(const MyTile& other) const{
        return other.getXPos()!=getXPos() or other.getYPos()!=getYPos();
    }
   /*==================== GETTERS AND SETTERS ============================*/
    float getFScore() const;
    void setFScore(float value);
    float getGScore() const;
    void setGScore(float value);
    float getHScore() const;
    void setHScore(float value);
    bool getVisited() const;
    void setVisited(bool value);
    bool getFpsVisitedUp() const;
    void setFpsVisitedUp(bool value);
    bool getFpsVisitedDown() const;
    void setFpsVisitedDown(bool value);
    std::vector<std::pair<MyTile*,float>> getNeighbours() const;
    void addNeighbour(std::pair<MyTile*,float> neighbour);

    void clearNeighbours();
    MyTile* getParent() const;
    void setParent(MyTile* value);





private:
    float fScore, gScore, hScore;
    bool visited = false;
    bool fpsVisitedUp = false;
    bool fpsVisitedDown = false;
    MyTile* parent = nullptr;
    std::vector<std::pair<MyTile*,float>> neighbours; //Used for pathfinding - does not contain any walls!
};

struct comp
{
public:
    bool operator()(const MyTile* l, const MyTile* r){ //used in pathfinding priority queue
        return l->getFScore()>r->getFScore();
    }
};

#endif // MYTILE_H
