#include <QtMath>
#include "isometricview.h"

#include "enemyview.h"
#include "penemyview.h"
#include "xenemyview.h"
#include "regenemyview.h"
#include "babyenemyview.h"
#include "healthpackview.h"
#include "protagonistview.h"
#include "helperclasses/xenemy.h"
#include "helperclasses/myworld.h"
#include "helperclasses/babyenemy.h"

#define PI 3.14159265

isometricView* isometricView::instance;

isometricView::isometricView(MainWindow* window)
{
    scene = new QGraphicsScene();
    window->getUi()->graphview_map2->setScene(scene);
}

isometricView::~isometricView()
{
    delete scene;
}

isometricView *isometricView::getInstance(MainWindow* window)
{
    if (instance==nullptr)
        instance = new isometricView(window);
    return instance;
}

isometricView *isometricView::getInstance()
{
    if (instance==nullptr)
        instance = getInstance(Controller::getInstance()->getWindow());
    return instance;
}

std::vector<MyTile*> isometricView::loadImageMap()
{
    MyWorld* world = Controller::getInstance()->getWorld();
    MainWindow *window = Controller::getInstance()->getWindow();
    Ui::MainWindow * ui=window->getUi();
    ui->graphview_map2->scene()->clear();
    QRectF screen =ui->graphview_map2->mapToScene(ui->graphview_map2->viewport()->geometry()).boundingRect();
    qreal screen_size_x = screen.width();
    qreal screen_size_y = screen.height();
    qreal center_top_x =screen.topLeft().x();
    qreal center_top_y =screen.topLeft().y();

    ui->graphview_map2->resetTransform();
    // cartesian to isometric
    qreal min_x = center_top_x - screen_size_x;
    qreal max_x = center_top_x + 2*screen_size_x;
    qreal min_y = center_top_y/0.86602 - screen_size_y;
    qreal max_y = center_top_y/0.86602 + 2*screen_size_y;
    int nr_of_rows = world->getRows();
    int nr_of_cols = world->getCols();

    //map here
    int min_row = min_y/(50);
    int max_row = max_y/(50);
    int min_col = min_x/(50);
    int max_col = max_x/(50);

    if(min_row <0){
        min_row =0;
    }
    else if (min_row>nr_of_rows) {
        min_row = nr_of_rows-1;
    }

    if(max_row <0){
        max_row =0;
    }
    else if (max_row>nr_of_rows) {
        max_row = nr_of_rows-1;
    }

    if(min_col <0){
        min_col =0;
    }
    else if (min_col>nr_of_cols) {
        min_col = nr_of_cols-1;
    }

    if(max_col <0){
        max_col =0;
    }
    else if (max_col>nr_of_cols) {
        max_col = nr_of_cols-1;
    }

    if(min_row> max_row){
        int temp = max_row;
        max_row = min_row;
        min_row = temp;
    }
    if(min_col>max_col){
        int temp = max_col;
        max_col = min_col;
        min_row = temp;
    }

    std::vector<MyTile*> tilesToDraw;
    std::vector<MyTile*> sorted_map = Controller::getInstance()->getSorted_map();

    /* putting the switch around the for loops will result code duplication yet will result in the switch only being run once instead of a lot of times
        this in term increases efficientie at the cost of code duplication*/
    switch (window->getRotation()) {

    case 1:{
        if(min_col ==0 and max_col == nr_of_cols-1 and min_row ==0 and max_row ==nr_of_rows-1){
            //what lies below doesn't work for when the view is completly visible
            // but since everything is visible we can return the sorted map
            return sorted_map;
        }
        for(int j = min_col;j<=max_col;j++){
            for(int i = min_row;i<=max_row;i++){
                int index =(j-(nr_of_cols-nr_of_rows))*(nr_of_cols) + i;
                    if(!((index)>=nr_of_cols*nr_of_rows) and index >=0){
                        tilesToDraw.push_back(sorted_map[index]);
                    }
            }
        }
        break;
    }
    case 2: {
        for(int j = min_col;j<=max_col;j++){
            for(int i = min_row;i<=max_row;i++){
                int index =j*nr_of_rows+i;
                    if(!((index)>=nr_of_cols*nr_of_rows) and index >=0){
                        tilesToDraw.push_back(sorted_map[j*nr_of_rows+i]);
                    }
            }
        }
        break;
    }
    case 3:{
        if(min_col ==0 and max_col == nr_of_cols-1 and min_row ==0 and max_row ==nr_of_rows-1){
            //what lies below doesn't work for when the view is completly visible
            // but since everything is visible we can return the sorted map
            return sorted_map;
        }
        for(int j = min_col;j<=max_col;j++){
            for(int i = min_row;i<=max_row;i++){
                int index =j*(nr_of_cols) + (nr_of_cols-nr_of_rows) + i;
                    if(!((index)>=nr_of_cols*nr_of_rows) and index >=0){
                        tilesToDraw.push_back(sorted_map[index]);

                    }
            }
        }
        break;
    }
    default: {
        for(int j = min_col;j<=max_col;j++){
            for(int i = min_row;i<=max_row;i++){
                int index =j*nr_of_rows+i;
                    if(!((index)>=nr_of_cols*nr_of_rows) and index >=0){
                        tilesToDraw.push_back(sorted_map[j*nr_of_rows+i]);
                    }
            }
        }
        break;
    }


    }
    return tilesToDraw;

}

void isometricView::draw_wall(double start_x, double start_y, double size,float height,QGraphicsScene* scene,int rotation)
{


    QBrush brush(QColor(106,75,70));
    QPen pen(QColor(112,99,99));
    QBrush brush2(QColor(187,136,127));
    QBrush brush3(QColor(168,97,85));

    double xpos= start_x-cos(45*PI/180)*height;
    double ypos= start_y-cos(45*PI/180)*height*0.86602;
    QPolygonF top;
    top << QPointF(xpos, ypos)<< QPointF(xpos,ypos+size*0.86602)<<QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos);
    QPolygonF poly;
    poly << QPointF(xpos+size, ypos+size*0.86602) << QPointF(xpos+size, ypos) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+cos(45*PI/180)*height*0.86602) << QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);
    QPolygonF front;
    front <<QPointF(xpos,ypos+size*0.86602) << QPointF(xpos+size, ypos+size*0.86602) <<QPointF(xpos+size+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602)<<QPointF(xpos+cos(45*PI/180)*height,ypos+size*0.86602+cos(45*PI/180)*height*0.86602);
    switch (rotation) {
        case 1:{
            scene->addPolygon(poly, pen, brush);
            scene->addPolygon(front, pen, brush);

            break;
        }
        case 2:{
            scene->addPolygon(poly, pen, brush);
            scene->addPolygon(front, pen, brush);

            break;
        }
        case 3:{
            scene->addPolygon(poly, pen, brush3);
            scene->addPolygon(front, pen, brush);

            break;
        }
        default:{
            scene->addPolygon(poly, pen, brush);
            scene->addPolygon(front, pen, brush3);
            break;
        }

    }

    scene->addPolygon(top, pen, brush2);


}

void isometricView::draw_map(QGraphicsScene* scene,std::vector<MyTile*> worldToDraw)
{
    MainWindow *window = Controller::getInstance()->getWindow();
    //QImage myimage = window->getImage().toImage();    // convert your QPixmap to QImage

    Ui::MainWindow * ui=window->getUi();
    // reset the transformations done on the graphicalview
    //ui->graphview_map2->scene()->clear(max_col);
    ui->graphview_map2->resetTransform();
    // following two functions might be added somewhere else just ot make sure they work done here

    //drawing each tile
    for(MyTile* tile : worldToDraw) {
        //drawing each tile
        float tileValue=tile->getValue();
        float height = tileValue*50;
        if(tileValue <=0){
            height =75;
        }
        if(tileValue >=1){
            height =0;
        }
        else{
            isometricView::draw_wall(tile->getXPos()*50-20,(tile->getYPos()*50-20)*0.86602,50,height,scene,window->getRotation());
        }

    }

    ui->graphview_map2->rotate(30);

    ui->graphview_map2->shear(-0.6,0);

}

void isometricView::transform_to_isometric()
{
    MainWindow *window = Controller::getInstance()->getWindow();
    Ui::MainWindow * ui=window->getUi();
    ui->graphview_map2->resetTransform();
    ui->graphview_map2->resetMatrix();
    ui->graphview_map2->rotate(0);

    // create a scene and add it your view
    //QGraphicsScene* scene = new QGraphicsScene;
    //ui->graphview_map2->setScene(scene);


    // call function to draw walls on necessary places


    //isometricView::draw_map(window,scene);


    //ui->graphview_map2->setScene(map_scene);
    ui->graphview_map2->rotate(30);

    ui->graphview_map2->shear(-0.6,0);
}

void isometricView::draw_world()
{


    if(Controller::getInstance()->getTrackprotagonist()){
        FocusOnProtagonist();
    }

    MyWorld* world = Controller::getInstance()->getWorld();
    MainWindow* window = Controller::getInstance()->getWindow();

    //QImage myimage = window->getImage().toImage();    // convert your QPixmap to QImage

    //std::shared_ptr<MyWorld> thingy = std::make_shared<MyWorld>(MyWorld(world));
    //sort here

    std::vector<MyTile*> worldToDraw = loadImageMap();


    std::vector<std::shared_ptr<MyHealthpack>> healthpacks = calculate_visible_healthpacks(worldToDraw,world->getHealthpacks());
    std::vector<std::shared_ptr<Enemy>> enemies = calculate_visible_enemies(worldToDraw,world->getEnemies());



    int index_healthpack =0;
    int healthpack_size=healthpacks.size();
    int index_enemies =0;
    int enemies_size=enemies.size();
    int protagonist_x =world->getProta()->getXPos();
    int protagonist_y =world->getProta()->getYPos();
    // make sure you can scroll to everywhere by setting the sceneRect

    Ui::MainWindow * ui=window->getUi();
    QRectF mapsize(QPointF(0,0),QPointF(world->getCols()*50,world->getRows()*50));

    ui->graphview_map2->setSceneRect(mapsize);

    //drawing each tile
    for(MyTile* tile : worldToDraw) {
        //drawing each tile
        float tileValue=tile->getValue();
        float height = tileValue*50;
        bool draw_healthpack = false;
        bool draw_enemy = false;
        if(tileValue <=0){
            height =75;
        }
        if(tileValue >=1){
            height =0;
        }

        int xpos =tile->getXPos();
        int ypos =tile->getYPos();

        //see if there is no other item that has to be drawn first
        if(index_healthpack<healthpack_size){
            if(xpos== healthpacks[index_healthpack]->getX()){
                //check for y value
                if(ypos== healthpacks[index_healthpack]->getY()){

                    //check if medkit is already taken, if so increase index of healthpack and not draw it
                    if(healthpacks[index_healthpack]->getUsed()){
                        index_healthpack++;
                    }

                    else{
                        draw_healthpack=true;
                    }
                }
            }
        }
        if(index_enemies < enemies_size){
            if(xpos == enemies[index_enemies]->getXPos()){
                //check for y value
                if(ypos== enemies[index_enemies]->getYPos()){
                    draw_enemy=true;
                }
            }
        }

        int X=tile->getXPos();
        int Y=tile->getYPos();

        switch (window->getRotation()) {

            case 1:{

                int new_y=X;
                X=world->getCols() -Y -1;
                Y=new_y;

                break;
            }
            case 2:{
                X=world->getCols() -X-1;
                Y=world->getRows()-Y-1;
                break;
            }
            case 3:{

                int new_x =Y;
                Y=world->getRows()-X-1;
                X=new_x;
                break;
            }
            default:{
                break;
            }

        }

        if(height>0){
            isometricView::draw_wall(X*50-20,(Y*50-20)*0.86602,50,height,scene,window->getRotation());

        }

        if(draw_healthpack){
            int X=healthpacks[index_healthpack]->getX();
            int Y=healthpacks[index_healthpack]->getY();

            switch (window->getRotation()) {

                case 1:{
                    int new_y=X;
                    X=world->getCols() -Y -1;
                    Y=new_y;
                    break;
                }
                case 2:{
                    X=world->getCols() -X-1;
                    Y=world->getRows()-Y-1;
                    break;
                }
                case 3:{
                    int new_x =Y;
                    Y=world->getRows()-X-1;
                    X=new_x;
                    break;
                }
                default:{
                    break;
                }
            }
            HealthpackView::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,30);
            index_healthpack++;
        }
        if(draw_enemy){

            int X=enemies[index_enemies]->getXPos();
            int Y= enemies[index_enemies]->getYPos();
            //check what rotation we are in and adapt X,Y to it
            //determine correct position to draw the enemy at since we know it has to be drawn
            switch (window->getRotation()) {

                case 1:{
                    int new_y=X;
                    X=world->getCols() -Y -1;
                    Y=new_y;
                    break;
                }
                case 2:{
                    X=world->getCols() -X-1;
                    Y=world->getRows()-Y-1;
                    break;
                }
                case 3:{
                    int new_x =Y;
                    Y=world->getRows()-X-1;
                    X=new_x;
                    break;
                }
                default:{
                    break;
                }
            }


            if(dynamic_cast<PEnemy*>(enemies[index_enemies].get())){
                // penemy draw
                if(enemies[index_enemies]->getDefeated()){
                    PEnemyView::drawDeadIsometric(window,X*50-20-height*cos(45*PI/180), (Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602, 50);
                }
                else{
                    PEnemyView::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,50);
                }

            }
            else if(dynamic_cast<XEnemy*>(enemies[index_enemies].get())) {

                if(enemies[index_enemies]->getDefeated()){
                    xenemyview::drawDeadIsometric(window,X*50-20-height*cos(45*PI/180), (Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602, 50);
                }
                else{
                    xenemyview::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,50);
                }

            }
            else if (dynamic_cast<BabyEnemy*>(enemies[index_enemies].get())){
                if(enemies[index_enemies]->getDefeated()){
                    Babyenemyview::drawDeadIsometric(window,X*50-20-height*cos(45*PI/180), (Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602, 50);
                }
                else{
                    Babyenemyview::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,50);
                }
            }
            // cast last to the RegEnemy since this should always succeed
            else if(dynamic_cast<Enemy*>(enemies[index_enemies].get()))
            {
                if(enemies[index_enemies]->getDefeated()){
                    RegEnemyView::drawDeadIsometric(window,X*50-20-height*cos(45*PI/180), (Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602, 50);
                }
                else{
                    RegEnemyView::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,50);
                }
            }
            //need to create class xenemys

            else{
                //shoudn't come here
            }

            index_enemies++;
        }
        if(protagonist_x==tile->getXPos()&&protagonist_y==tile->getYPos()){

            int X=protagonist_x;
            int Y= protagonist_y;
            //check what rotation we are in and adapt X,Y to it
            //determine correct position to draw the enemy at since we know it has to be drawn
            switch (window->getRotation()) {

                case 1:{
                    int new_y=X;
                    X=world->getCols() -Y -1;
                    Y=new_y;
                    break;
                }
                case 2:{
                    X=world->getCols() -X-1;
                    Y=world->getRows()-Y-1;
                    break;
                }
                case 3:{
                    int new_x =Y;
                    Y=world->getRows()-X-1;
                    X=new_x;
                    break;
                }
                default:{
                    break;
                }
            }


            ProtagonistView::drawIsometric(window,X*50-20-height*cos(45*PI/180),(Y*50-20)*0.86602-height*cos(45*PI/180)*0.86602,50,50);
        }

    }
    //transform back into isometric view.

    ui->graphview_map2->rotate(30);
    ui->graphview_map2->shear(-0.6,0);



}

std::vector<std::shared_ptr<Enemy >> isometricView::calculate_visible_enemies(std::vector<MyTile *> map, std::vector<std::shared_ptr<Enemy>> enemies)
{

    std::vector<std::shared_ptr<Enemy>> visibleEnemies;
    //the required list is already sorted:
    MainWindow * window = Controller::getInstance()->getWindow();

    //should be sorted here but not sure
    if(map.size()==0){
        return visibleEnemies;
    }
    int min_x=map[0]->getXPos();
    int max_x=map[0]->getXPos();
    int min_y=map[0]->getYPos();
    int max_y=map[0]->getYPos();
    for(MyTile * tile : map){
        if(tile->getXPos()>max_x){
            max_x = tile->getXPos();
        }
        else if(tile->getXPos()<min_x){
            min_x = tile->getXPos();
        }

        if(tile->getYPos()>max_y){
            max_y = tile->getYPos();
        }
        else if(tile->getYPos()<min_y){
            min_y = tile->getYPos();
        }

    }

    //enemies are sorted here
    for( std::shared_ptr<Enemy> bart : enemies)
    {
        if(bart->getXPos()>=min_x & bart->getXPos()<=max_x){
            if(bart->getYPos()>=min_y & bart->getYPos()<=max_y){
                visibleEnemies.push_back(bart);

            }
        }
    }
    std::sort(visibleEnemies.begin(), visibleEnemies.end(),
              [window](std::shared_ptr<Enemy> a, std::shared_ptr<Enemy> b) -> bool
    {
        switch (window->getRotation()) {

            case 1:{
                if(a->getYPos()==b->getYPos()){
                    return a->getXPos() <b->getXPos();
                }
                return a->getYPos() >b->getYPos();

                break;
            }
            case 2:{

                if(a->getXPos()==b->getXPos()){
                    return a->getYPos() >b->getYPos();
                }
                return a->getXPos() >b->getXPos();

                break;
            }
            case 3:{

                if(a->getYPos()==b->getYPos()){
                    return a->getXPos() >b->getXPos();
                }
                return a->getYPos() <b->getYPos();

                break;
            }
            default:{
                if(a->getXPos()==b->getXPos()){
                    return a->getYPos() <b->getYPos();
                }
                return a->getXPos() <b->getXPos();

                break;
            }

        }


    });
    return visibleEnemies;

}

std::vector<std::shared_ptr<MyHealthpack>> isometricView::calculate_visible_healthpacks(std::vector<MyTile *> map, std::vector<std::shared_ptr<MyHealthpack>> healthpacks)
{

    std::vector<std::shared_ptr<MyHealthpack>> visiblehealthpacks;
    MainWindow * window = Controller::getInstance()->getWindow();
    //the required list is already sorted:
    //should be sorted here but not sure
    if(map.size()==0){
        return visiblehealthpacks;
    }
    int min_x=map[0]->getXPos();
    int max_x=map[0]->getXPos();
    int min_y=map[0]->getYPos();
    int max_y=map[0]->getYPos();
    for(MyTile * tile : map){
        if(tile->getXPos()>max_x){
            max_x = tile->getXPos();
        }
        else if(tile->getXPos()<min_x){
            min_x = tile->getXPos();
        }

        if(tile->getYPos()>max_y){
            max_y = tile->getYPos();
        }
        else if(tile->getYPos()<min_y){
            min_y = tile->getYPos();
        }

    }


    //enemies are sorted here
    for( std::shared_ptr<MyHealthpack> hppack : healthpacks)
    {

        if(hppack->getX()>=min_x & hppack->getX()<=max_x){
            if(hppack->getY()>=min_y & hppack->getY()<=max_y){
                visiblehealthpacks.push_back(hppack);
            }
        }
    }

    std::sort(visiblehealthpacks.begin(), visiblehealthpacks.end(),
              [window](std::shared_ptr<MyHealthpack> a, std::shared_ptr<MyHealthpack> b) -> bool
    {
        switch (window->getRotation()) {

            case 1:{
                if(a->getY()==b->getY()){
                    return a->getX() <b->getX();
                }
                return a->getY() >b->getY();

                break;
            }
            case 2:{

                if(a->getX()==b->getX()){
                    return a->getY() >b->getY();
                }
                return a->getX() >b->getX();

                break;
            }
            case 3:{

                if(a->getY()==b->getY()){
                    return a->getX() >b->getX();
                }
                return a->getY() <b->getY();

                break;
            }
            default:{
                if(a->getX()==b->getX()){
                    return a->getY() <b->getY();
                }
                return a->getX() <b->getX();

                break;
            }

        }


    });
    return visiblehealthpacks;

}


void isometricView::FocusOnProtagonist(){

    MainWindow * window = Controller::getInstance()->getWindow();
    MyWorld * world = Controller::getInstance()->getWorld();

    int X=(Controller::getInstance()->getWorld()->getProta()->getXPos());
    int Y=(Controller::getInstance()->getWorld()->getProta()->getYPos());

    switch (window->getRotation()) {

        case 1:{

            int new_y=X;
            X=world->getCols() -Y -1;
            Y=new_y;

            break;
        }
        case 2:{
            X=world->getCols() -X-1;
            Y=world->getRows()-Y-1;
            break;
        }
        case 3:{

            int new_x =Y;
            Y=world->getRows()-X-1;
            X=new_x;
            break;
        }
        default:{
            break;
        }
    }

    window->getUi()->graphview_map2->centerOn(X*50,Y*50*0.86602);


}
