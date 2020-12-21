#include "mytile.h"


MyTile::MyTile(int col, int row, float value)
    :Tile(col,row,value), fScore(maxScore),gScore(maxScore), hScore(0)
{
}

MyTile::MyTile(Tile* tile):
    Tile(tile->getXPos(),tile->getYPos(),tile->getValue()), fScore(maxScore),gScore(maxScore), hScore(0)
{
    if(tile->getValue()>1)  //their library gives a value of Inf instead of 0
        setValue(0.00f);
}
bool MyTile::isWall()
{
    return getValue()<=0;
}
/*==================== GETTERS AND SETTERS ============================*/
float MyTile::getFScore() const
{
    return fScore;
}
void MyTile::setFScore(float value)
{
    fScore = value;
}
float MyTile::getGScore() const
{
    return gScore;
}
void MyTile::setGScore(float value)
{
    gScore = value;
}
float MyTile::getHScore() const
{
    return hScore;
}
void MyTile::setHScore(float value)
{
    hScore = value;
}
bool MyTile::getVisited() const
{
    return visited;
}
void MyTile::setVisited(bool value)
{
    visited = value;
}
bool MyTile::getFpsVisitedDown() const
{
    return fpsVisitedDown;
}
void MyTile::setFpsVisitedDown(bool value)
{
    fpsVisitedDown = value;
}
bool MyTile::getFpsVisitedUp() const
{
    return fpsVisitedUp;
}
void MyTile::setFpsVisitedUp(bool value)
{
    fpsVisitedUp = value;
}
std::vector<std::pair<MyTile*,float>> MyTile::getNeighbours() const
{
    return neighbours;
}
void MyTile::addNeighbour(std::pair<MyTile*,float> neighbour)
{
    neighbours.push_back(neighbour);
}
void MyTile::clearNeighbours()
{
    neighbours.clear();
}
MyTile* MyTile::getParent() const
{
    return parent;
}
void MyTile::setParent(MyTile* value)
{
    parent = value;
}

/*==================================sorters================================*/

bool sortbyXvalue (const Tile Tile1, const Tile Tile2)
{
    if( Tile1.getXPos()== Tile2.getXPos())
        return Tile1.getXPos() < Tile2.getXPos();
    return Tile1.getXPos() < Tile2.getXPos();

}
/*================================================================================*/
/*================================================================================*/
