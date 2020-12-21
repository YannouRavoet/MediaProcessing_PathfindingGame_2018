#include "pathfinding.h"
Pathfinding* Pathfinding::instance = nullptr;

Pathfinding::Pathfinding()
    :start(nullptr),dest(nullptr)
{
    open = std::priority_queue<MyTile*, std::vector<MyTile*>, comp>();
}

Pathfinding *Pathfinding::getInstance()
{
    if(instance==nullptr)
        instance = new Pathfinding();
    return instance;
}

std::vector<MyTile*> Pathfinding::AStar()
{
    MyTile* current;
    while(!open.empty()){
        current=open.top(); //4,2% of time
        /*Destination?*/
        if(current==dest){
            if(!Controller::getInstance()->getWorld()->getHasGrayValue())
                return reconstructJPSPath(current);
            return reconstructAStarPath(current);//0.04% of time
        }
        /*not destination*/
        current->setVisited(true); //2,89% of time
        open.pop(); // 57,2% of time -> much less now that they are raw pointers
        std::vector<std::pair<MyTile*,float>> neighbours = current->getNeighbours(); //22,4% of time
        for(unsigned int i=0; i<neighbours.size(); i++){ //16,2% of time
            if (neighbours[i].first->getVisited())
                continue;
            float temp_gScore=current->getGScore()+neighbours[i].second;
            if(temp_gScore >= neighbours[i].first->getGScore())
                continue;
            /*Best path to this tile so far*/
            neighbours[i].first->setParent(current);
            neighbours[i].first->setGScore(temp_gScore);
            neighbours[i].first->setFScore(temp_gScore + heurWeight*(neighbours[i].first->getHScore()) );
            open.push(neighbours[i].first);
        }
    }
    return {};
}

//To be called before calling Pathfinding::AStar(...)
bool Pathfinding::initPF()
{
    if (start==nullptr)
        return false;
    if (dest==nullptr)
        return false;
    world = Controller::getInstance()->getWorld();
    stepcost1=world->getStepCost1();
    stepcost2=world->getStepCost2();
    /*General init*/
    updateInit();
    /*JPS init*/
    if(!Controller::getInstance()->getWorld()->getHasGrayValue())
        JPSAllDir(start);
    return true;
}

bool Pathfinding::updateInit()
{
    open = std::priority_queue<MyTile*, std::vector<MyTile*>, comp>();
    for(MyTile* tile : world->getMap()){
        if(tile->getValue()>0){
            tile->setVisited(false);
            tile->setParent(nullptr);
            heuristicEstimate(tile);
            tile->setGScore(maxScore);
            tile->setFScore(tile->getGScore()+tile->getHScore());
            tile->setFpsVisitedUp(false);
            tile->setFpsVisitedDown(false);
        }
    }
    start->setFScore(start->getHScore());
    start->setGScore(0.00f);
    open.push(start);
    return true;
}

/*8-direction movement => Chebyshev distance*/
void Pathfinding::heuristicEstimate(MyTile* tile)
{
    int steps = std::max(std::abs(tile->getXPos()-dest->getXPos()),std::abs(tile->getYPos()-dest->getYPos()));
    int diags = std::min(std::abs(tile->getXPos()-dest->getXPos()),std::abs(tile->getYPos()-dest->getYPos()));
    tile->setHScore((steps-diags)*stepcost1 + diags*stepcost2);
}

void Pathfinding::JPSAllDir(MyTile* tile)
{
    searchJumpPointUp(tile);
    searchJumpPointUpRight(tile);
    searchJumpPointRight(tile);
    searchJumpPointDownRight(tile);
    searchJumpPointDown(tile);
    searchJumpPointDownLeft(tile);
    searchJumpPointLeft(tile);
    searchJumpPointUpLeft(tile);
}

void Pathfinding::searchJumpPointUp(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(x,--y);
        if(cur==nullptr or cur->isWall())
            return;
    }while(!forcedNeighbourUp(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(start->getYPos()-y)*stepcost1);
    start->addNeighbour(neighbour);
    //recursive searching
    if(!cur->getFpsVisitedUp()){
        cur->setFpsVisitedUp(true);
        searchJumpPointUp(cur);
        searchJumpPointUpRight(cur);
        searchJumpPointUpLeft(cur);
    }
    return;
}
void Pathfinding::searchJumpPointUpRight(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(++x,--y);
        if(cur==nullptr or cur->isWall())
            return;
        if(scanRight(cur))
            break;
        if(scanUp(cur))
            break;
    }while(!forcedNeighbourUpRight(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(start->getYPos()-y)*stepcost2);
    start->addNeighbour(neighbour);
    if(!cur->getFpsVisitedUp()){
        cur->setFpsVisitedUp(true);
        //recursive searching
        searchJumpPointUp(cur);
        searchJumpPointUpRight(cur);
        searchJumpPointRight(cur);
        if(world->getMapTile(--x,y)->isWall() and !world->getMapTile(x,--y)->isWall())
            searchJumpPointUpLeft(cur); //to turn 1 tile corners
    }
    return;
}
void Pathfinding::searchJumpPointRight(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(++x,y);
        if(cur==nullptr or cur->isWall())
            return;
    }while(!forcedNeighbourRight(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(x-start->getXPos())*stepcost1);
    start->addNeighbour(neighbour);
    //recursive searching
    searchJumpPointUpRight(cur);
    searchJumpPointRight(cur);
    searchJumpPointDownRight(cur);

    return;
}
void Pathfinding::searchJumpPointDownRight(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(++x,++y);
        if(cur==nullptr or cur->isWall())
            return;
        if(scanRight(cur))
            break;
        if(scanDown(cur))
            break;
    }while(!forcedNeighbourDownRight(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(x-start->getXPos())*stepcost2);
    start->addNeighbour(neighbour);
    //recursive searching
    if(!cur->getFpsVisitedDown()){
        cur->setFpsVisitedDown(true);
        searchJumpPointRight(cur);
        searchJumpPointDownRight(cur);
        searchJumpPointDown(cur);
        if(world->getMapTile(--x,y)->isWall() and !world->getMapTile(x,++y)->isWall())
            searchJumpPointDownLeft(cur);
    }
    return;
}
void Pathfinding::searchJumpPointDown(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(x,++y);
        if(cur==nullptr or cur->isWall())
            return;
    }while(!forcedNeighbourDown(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(y-start->getYPos())*stepcost1);
    start->addNeighbour(neighbour);
    if(!cur->getFpsVisitedDown()){
        cur->setFpsVisitedDown(true);
        //recursive searching
        searchJumpPointDownRight(cur);
        searchJumpPointDown(cur);
        searchJumpPointDownLeft(cur);
    }
    return;
}
void Pathfinding::searchJumpPointDownLeft(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(--x,++y);
        if(cur==nullptr or cur->isWall())
            return;
        if(scanLeft(cur))
            break;
        if(scanDown(cur))
            break;
    }while(!forcedNeighbourDownLeft(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(y-start->getYPos())*stepcost2);
    start->addNeighbour(neighbour);
    if(!cur->getFpsVisitedDown()){
        cur->setFpsVisitedDown(true);
        //recursive searching
        searchJumpPointDown(cur);
        searchJumpPointDownLeft(cur);
        searchJumpPointLeft(cur);
        if(world->getMapTile(++x,y)->isWall() and !world->getMapTile(x,++y)->isWall())
            searchJumpPointDownRight(cur);
    }
    return;
}
void Pathfinding::searchJumpPointLeft(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(--x,y);
        if(cur==nullptr or cur->isWall())
            return;
    }while(!forcedNeighbourLeft(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(start->getXPos()-x)*stepcost1);
    start->addNeighbour(neighbour);
    //recursive searching
    searchJumpPointDownLeft(cur);
    searchJumpPointLeft(cur);
    searchJumpPointUpLeft(cur);

    return;
}
void Pathfinding::searchJumpPointUpLeft(MyTile *start)
{
    int x = start->getXPos();
    int y = start->getYPos();
    MyTile* cur;
    do{
        cur = world->getMapTile(--x,--y);
        if(cur==nullptr or cur->isWall())
            return;
        if(scanLeft(cur))
            break;
        if(scanUp(cur))
            break;
    }while(!forcedNeighbourUpLeft(cur));
    std::pair<MyTile*,float>neighbour(cur,static_cast<float>(start->getXPos()-x)*stepcost2);
    start->addNeighbour(neighbour);
    if(!cur->getFpsVisitedUp()){
        cur->setFpsVisitedUp(true);
        //recursive searching
        searchJumpPointUp(cur);
        searchJumpPointLeft(cur);
        searchJumpPointUpLeft(cur);
        if(world->getMapTile(++x,y)->isWall() and !world->getMapTile(x,--y)->isWall())
            searchJumpPointUpRight(cur);
    }
    return;
}

bool Pathfinding::scanLeft(MyTile *cur){
    MyTile* scanTile = cur;
    int x = cur->getXPos();
    int y = cur->getYPos();
    do{
        scanTile = world->getMapTile(--x,y);
        if(scanTile==nullptr or scanTile->isWall())
            return false;
    }while(!forcedNeighbourLeft(scanTile));
    return true;
}
bool Pathfinding::scanRight(MyTile *cur){
    MyTile* scanTile = cur;
    int x = cur->getXPos();
    int y = cur->getYPos();
    do{
        scanTile = world->getMapTile(++x,y);
        if(scanTile==nullptr or scanTile->isWall())
            return false;
    }while(!forcedNeighbourRight(scanTile));
    return true;
}
bool Pathfinding::scanUp(MyTile *cur){
    MyTile* scanTile = cur;
    int x = cur->getXPos();
    int y = cur->getYPos();
    do{
        scanTile = world->getMapTile(x,--y);
        if(scanTile==nullptr or scanTile->isWall())
            return false;
    }while(!forcedNeighbourUp(scanTile));
    return true;
}
bool Pathfinding::scanDown(MyTile *cur){
    MyTile* scanTile = cur;
    int x = cur->getXPos();
    int y = cur->getYPos();
    do{
        scanTile = world->getMapTile(x,++y);
        if(scanTile==nullptr or scanTile->isWall())
            return false;
    }while(!forcedNeighbourDown(scanTile));
    return true;
}

bool Pathfinding::forcedNeighbourRight(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* above       = world->getMapTile(x,y-1);
    if(above!=nullptr and above->isWall()){
        MyTile* abovePlus   = world->getMapTile(x+1,y-1);
        if(abovePlus!= nullptr and !abovePlus->isWall())
            return true;
    }
    MyTile* below       = world->getMapTile(x,y+1);
    if(below!=nullptr and below->isWall()){
        MyTile* belowPlus   = world->getMapTile(x+1,y+1);
        if(belowPlus!=nullptr and !belowPlus->isWall())
            return true;
    }
    return false;

}
bool Pathfinding::forcedNeighbourLeft(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* above       = world->getMapTile(x,y-1);
    if(above!=nullptr and above->isWall()){
        MyTile* abovePlus   = world->getMapTile(x-1,y-1);
        if(abovePlus!= nullptr and !abovePlus->isWall())
            return true;
    }
    MyTile* below       = world->getMapTile(x,y+1);
    if(below!=nullptr and below->isWall()){
        MyTile* belowPlus   = world->getMapTile(x-1,y+1);
        if(belowPlus!=nullptr and !belowPlus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourUp(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* left        = world->getMapTile(x-1,y);
    if(left!=nullptr and left->isWall() ){
        MyTile* leftPlus    = world->getMapTile(x-1,y-1);
        if(leftPlus!=nullptr and !leftPlus->isWall())
            return true;
    }
    MyTile* right       = world->getMapTile(x+1,y);
    if(right!=nullptr and right->isWall()){
        MyTile* rightPlus   = world->getMapTile(x+1,y-1);
        if(rightPlus!=nullptr and !rightPlus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourDown(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* left        = world->getMapTile(x-1,y);
    if(left!=nullptr and left->isWall() ){
        MyTile* leftPlus    = world->getMapTile(x-1,y+1);
        if(leftPlus!=nullptr and !leftPlus->isWall())
            return true;
    }
    MyTile* right       = world->getMapTile(x+1,y);
    if(right!=nullptr and right->isWall()){
        MyTile* rightPlus   = world->getMapTile(x+1,y+1);
        if(rightPlus!=nullptr and !rightPlus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourUpRight(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* check1      = world->getMapTile(x-1,y);
    if(check1!=nullptr and check1->isWall()){
        MyTile* check1Plus  = world->getMapTile(x-1,y-1);
        if(check1Plus!=nullptr and !check1Plus->isWall())
            return true;
    }
    MyTile* check2      = world->getMapTile(x,y+1);
    if(check2!=nullptr and check2->isWall() ){
        MyTile* check2Plus  = world->getMapTile(x+1,y+1);
        if(check2Plus!=nullptr and !check2Plus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourDownRight(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* check1      = world->getMapTile(x-1,y);
    if(check1!=nullptr and check1->isWall()){
        MyTile* check1Plus  = world->getMapTile(x-1,y+1);
        if(check1Plus!=nullptr and !check1Plus->isWall())
            return true;
    }
    MyTile* check2      = world->getMapTile(x,y-1);
    if(check2!=nullptr and check2->isWall() ){
        MyTile* check2Plus  = world->getMapTile(x+1,y-1);
        if(check2Plus!=nullptr and !check2Plus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourUpLeft(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* check1      = world->getMapTile(x+1,y);
    if(check1!=nullptr and check1->isWall()){
        MyTile* check1Plus  = world->getMapTile(x+1,y-1);
        if(check1Plus!=nullptr and !check1Plus->isWall())
            return true;
    }
    MyTile* check2      = world->getMapTile(x,y+1);
    if(check2!=nullptr and check2->isWall() ){
        MyTile* check2Plus  = world->getMapTile(x-1,y+1);
        if(check2Plus!=nullptr and !check2Plus->isWall())
            return true;
    }
    return false;
}
bool Pathfinding::forcedNeighbourDownLeft(MyTile *tile)
{
    if(tile==dest)
        return true;
    int x = tile->getXPos();
    int y = tile->getYPos();
    MyTile* check1      = world->getMapTile(x+1,y);
    if(check1!=nullptr and check1->isWall()){
        MyTile* check1Plus  = world->getMapTile(x+1,y+1);
        if(check1Plus!=nullptr and !check1Plus->isWall())
            return true;
    }
    MyTile* check2      = world->getMapTile(x,y-1);
    if(check2!=nullptr and check2->isWall() ){
        MyTile* check2Plus  = world->getMapTile(x-1,y-1);
        if(check2Plus!=nullptr and !check2Plus->isWall())
            return true;
    }
    return false;
}

std::vector<MyTile*> Pathfinding::reconstructAStarPath(MyTile* current) //-> 0.0017872 seconds => ceiling analysis = not worth improving
{
    std::vector<MyTile*> path;
    path.push_back(current);
    current=current->getParent();
    while(current!=nullptr){//only the startTile has a nullptr parent
        path.push_back(current);
        current=current->getParent();
    }
    std::reverse(path.begin(),path.end());
    return path;
}
std::vector<MyTile*> Pathfinding::reconstructJPSPath(MyTile* current)
{
    std::vector<MyTile*> path;
    do{
        path.push_back(current);
        addIntermediateTiles(current,&path);
        current=current->getParent();
    }while(current!=nullptr);
    std::reverse(path.begin(),path.end());
    return path;
}
void Pathfinding::addIntermediateTiles(MyTile *current,std::vector<MyTile*>* path)
{
    if(current->getParent()==nullptr)
        return;
    int cX = current->getXPos();
    int cY = current->getYPos();
    int pX = current->getParent()->getXPos();
    int pY = current->getParent()->getYPos();
    if(std::max(std::abs(cX-pX),std::abs(cY-pY))==1 )
        return; //points are adjacent
    //HORIZONTAL
    if(cY==pY){
        if(cX<pX){ //going right
            do{
                path->push_back(world->getMapTileUnchecked(++cX,cY));
            }while(cX<pX-1);
            return;
        }
        else{ //going left
            do{
                path->push_back(world->getMapTileUnchecked(--cX,cY));
            }while(cX>pX+1);
            return;
        }
    }
    //VERTICAL
    else if(cX==pX){
        if(cY<pY){ //going down
            do{
                path->push_back(world->getMapTileUnchecked(cX,++cY));
            }while(cY<pY-1);
            return;
        }
        else{ //going up
            do{
                path->push_back(world->getMapTileUnchecked(cX,--cY));
            }while(cY>pY+1);
            return;
        }
    }
    //DIAGONAL
    else{
        if(cX<pX){ //right
            if(cY<pY){ //going downright
                do{
                    path->push_back(world->getMapTileUnchecked(++cX,++cY));
                }while(cX<pX-1);
            }
            else{ //going upright
                do{
                    path->push_back(world->getMapTileUnchecked(++cX,--cY));
                }while(cX<pX-1);
            }
        }
        else{ //left
            if(cY<pY){ //going downleft
                do{
                    path->push_back(world->getMapTileUnchecked(--cX,++cY));
                }while(cX>pX+1);
                return;
            }
            else{ //going upleft
                do{
                    path->push_back(world->getMapTileUnchecked(--cX,--cY));
                }while(cX>pX+1);
                return;
            }
        }
        return;
    }
}

float Pathfinding::getStepcost2() const
{
    return stepcost2;
}
float Pathfinding::getStepcost1() const
{
    return stepcost1;
}
float Pathfinding::getHeurWeight() const
{
    return heurWeight;
}
void Pathfinding::setHeurWeight(float value)
{
    heurWeight = value;
}
MyTile* Pathfinding::getDest() const
{
    return dest;
}
void Pathfinding::setDest(MyTile* value)
{
    dest = value;
}
MyTile* Pathfinding::getStart() const
{
    return start;
}
void Pathfinding::setStart(MyTile* value)
{
    start = value;
}

/*MyTile* Pathfinding::crossedDestColOrRow(MyTile* cur, MyTile* jumpPoint)
{
    if(*jumpPoint==*dest)
        return dest;
    int cX = cur->getXPos();
    int cY = cur->getYPos();
    int jX = jumpPoint->getXPos();
    int jY = jumpPoint->getYPos();
    int dX = dest->getXPos();
    int dY = dest->getYPos();
    //HORIZONTAL
    if(cY==jY){
        if( (dY==cY) and ((cX<dX and dX<jX) or (jX<dX and dX<cX)) )
            return dest;
    }
    //VERTICAL
    else if(cX==jX){
        if( (dX==cX) and ((cY<dY and dY<jY) or (jY<dY and dY<cY)) )
            return dest;
    }
    //DIAGONAL
    else if( (cX<dX and dX<=jX) or (jX<=dX and dX<cX) or (cY<dY and dY<=jY) or (jY<=dY and dY<cY)){
        if(std::abs(dX-cX)==std::abs(dY-cY)) //dest is on diagonal
            return dest;
        else if(std::abs(dY-cY) < std::abs(dX-cX)){ //choose same row
            if(cX<jX){  //right
                if(destReachableFromTile(cX+std::abs(dY-cY),dY,1,0))
                    return world->getMapTile(cX+std::abs(dY-cY),dY);
                return nullptr;
            }
            else{       //left
                if(destReachableFromTile(cX-std::abs(dY-cY),dY,-1,0))
                    return world->getMapTile(cX-std::abs(dY-cY),dY);
                return nullptr;
            }
        }
        else{//choose same column
            if(cY<jY){  //down
                if(destReachableFromTile(dX,cY+std::abs(dX-cX),0,1))
                    return world->getMapTile(dX,cY+std::abs(dX-cX));
                return nullptr;
            }else{      //up
                if(destReachableFromTile(dX,cY-std::abs(dX-cX),0,-1))
                    return world->getMapTile(dX,cY-std::abs(dX-cX));
                return nullptr;
            }
        }
    }
    return nullptr;
}*/
/*bool Pathfinding::destReachableFromTile(int cX, int cY, int dX, int dY)
{
    bool blocked;
    do{
        cX+=dX;
        cY+=dY;
        MyTile* cur = world->getMapTile(cX,cY);
        if(cur==dest)
            return true;
        blocked = cur->isWall();
    }while(!blocked);
    return false;
}*/
/*void Pathfinding::processNewNode(MyTile* tile, MyTile* parent)
{
    int steps = std::max(std::abs(parent->getXPos()-tile->getXPos()),std::abs(parent->getYPos()-tile->getYPos()));
    int diags = std::min(std::abs(parent->getXPos()-tile->getXPos()),std::abs(parent->getYPos()-tile->getYPos()));
    tile->setGScore( parent->getGScore() + ((steps-diags)*stepcost1 + diags*stepcost2) );
    tile->setFScore(tile->getGScore() + heurWeight*(tile->getHScore()));
    tile->setParent(parent);
    std::pair<MyTile*,float> neighbour(dest,tile->getHScore());
    tile->clearNeighbours();
    tile->addNeighbour(neighbour);
}*/
