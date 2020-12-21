#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QtWidgets>
#include <algorithm>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QWheelEvent>

#include "controller.h"
#include "pathfinding.h"
#include "views/viewone.h"
#include "views/isometricview.h"
#include "views/loadingscreen.h"
#include "helperclasses/xenemy.h"
#include "helperclasses/babyenemy.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_DeleteOnClose);
    contr = Controller::getInstance();
    ui->setupUi(this);
    text = new QString("");
    addTextToOutput("                                            Welcome to our game...\n");
    QPalette healthbar_palette = ui->healthbar->palette();
    healthbar_palette.setColor(QPalette::Highlight,Qt::red);
    ui->healthbar->setPalette(healthbar_palette);
    ui->healthbar2->setPalette(healthbar_palette);
    connect(ui->trackProta, SIGNAL(clicked(bool)), this, SLOT(tracking(bool)));
    isometricview = isometricView::getInstance(this);
    ui->graphview_map->setFocusPolicy( Qt::NoFocus );
    ui->graphview_map2->setFocusPolicy( Qt::NoFocus );
    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    setFocusPolicy( Qt::StrongFocus );
    setFocus( Qt::PopupFocusReason );
    ui->graphview_map2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphview_map2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setEnabled( true );
    processingKeyEvent=false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete text;
    delete isometricview;
    delete viewone;
    delete contr;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}
void MainWindow::addTextToOutput(QString newText)
{
    text->append(newText);
    ui->textoutput->setText(*text);
    ui->textoutput2->setText(*text);
    ui->textoutput->verticalScrollBar()->setValue(ui->textoutput->verticalScrollBar()->maximum());
    ui->textoutput2->verticalScrollBar()->setValue(ui->textoutput2->verticalScrollBar()->maximum());
}

/*UI INTERACTION*/
void MainWindow::updateHeurweights(float weight){
    Pathfinding* pf =Pathfinding::getInstance();
    pf->setHeurWeight(weight);
    ui->heurweight_slider->setValue(static_cast<int>(weight)*100);
    ui->heurweight_slider2->setValue(static_cast<int>(weight)*100);
    pf->updateInit();
    addTextToOutput("Updated heuristic weight to " + QString::number(static_cast<int>(pf->getHeurWeight()))+"\n");
}
void MainWindow::updateStepCosts(double cost1, double cost2){
    updateStepCostLabels(cost1,cost2);
    contr->getWorld()->setStepCosts(static_cast<float>(cost1),static_cast<float>(cost2));
    contr->getPathfinding()->initPF();
    addTextToOutput("Updated stepcost1 to " + QString::number(static_cast<double>(contr->getWorld()->getStepCost1()))+" and stepcost 2 to " + QString::number(static_cast<double>(contr->getWorld()->getStepCost2()))+"\n");
}
void MainWindow::updateStepCostLabels(double cost1, double cost2)
{
    ui->stepCost1_value->setValue(cost1);
    ui->stepCost2_value->setValue(cost2);
    ui->stepCost1_value2->setValue(cost1);
    ui->stepCost2_value2->setValue(cost2);
    ui->stepCost1_value2->setValue(cost1);
    ui->stepCost2_value2->setValue(cost2);
}
void MainWindow::updateEnemyLabels()
{
    ui->enemies_left->setText(QString::number(contr->getWorld()->getLivingEnemies().size()));
    ui->enemies_left2->setText(QString::number(contr->getWorld()->getLivingEnemies().size()));
    ui->enemies_total->setText(QString::number(contr->getWorld()->getEnemies().size()));
    ui->enemies_total->setText(QString::number(contr->getWorld()->getEnemies().size()));
}
void MainWindow::setImgLabel(QString filename){
    int index=filename.lastIndexOf(QChar('/'));
    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    QString img_name=filename.remove(0,index+1);
    ui->img_label->setText(img_name);
    ui->img_label2->setText(img_name);
}
void MainWindow::updateSpeedValue(int value)
{
    ui->speed_value->setText(QString::number(double(value)/2));
    ui->speed_value2->setText(QString::number(double(value)/2));
    contr->setAutospeed(float(value)/2);
}
void MainWindow::updateHealthvalue(int value)
{
    ui->healthbar->setValue(static_cast<int>(value));
    ui->healthbar2->setValue(static_cast<int>(value));
}
void MainWindow::updateEnergyvalue(int value)
{

    ui->energybar->setValue(static_cast<int>(value));
    ui->energybar2->setValue(static_cast<int>(value));
}
void MainWindow::updateStartValue(unsigned int x, unsigned int y)
{
    contr->getWorld()->getProta()->setPos(static_cast<int>(x),static_cast<int>(y));
    MyTile* tile = contr->getWorld()->getMapTile(static_cast<int>(x),static_cast<int>(y));
    contr->getPathfinding()->setStart(tile);
    contr->getPathfinding()->initPF();
    viewone->refreshSceneImage();
    isometricview->draw_world();
    addTextToOutput(QString("Updated start position to (").append(QString::number(x)).append(QString(",")).append(QString::number(y)).append(QString(")\n")));

}
void MainWindow::updateDestValue(unsigned int x, unsigned int y)
{
    MyTile* tile = contr->getWorld()->getMapTile(static_cast<int>(x),static_cast<int>(y));
    contr->getPathfinding()->setDest(tile);
    contr->getPathfinding()->initPF();
    addTextToOutput(QString("Updated dest position to (").append(QString::number(x)).append(QString(",")).append(QString::number(y)).append(QString(")\n")));

}
void MainWindow::updateMaximumXandY(int x, int y)
{
    ui->setstart_x->setMaximum(x);
    ui->setstart_x2->setMaximum(x);
    ui->setstart_y->setMaximum(y);
    ui->setstart_y2->setMaximum(y);
    ui->setdest_x->setMaximum(x);
    ui->setdest_x2->setMaximum(x);
    ui->setdest_y->setMaximum(y);
    ui->setdest_y2->setMaximum(y);
}
void MainWindow::loadNewWorld(QString filename)
{
    LoadingScreen * loadingscreen= new LoadingScreen();
    loadingscreen->showMessage("cleaning up after the apocalypse");
    qApp->processEvents();

    contr->setWorld(filename);
    loadingscreen->showMessage("resetting the world");
    qApp->processEvents();

    contr->setMapfile(filename);
    //load the map in view one
    if(ViewOne::getInstance()->initViewOne(filename))
    {
        energyChanged(100);
        healthChanged(100);
        loadingscreen->showMessage("configuring healhpacks");
        qApp->processEvents();
        contr->getWorld()->sortHealthpacks0();
        loadingscreen->showMessage("forming the blobs");
        qApp->processEvents();
        contr->getWorld()->sortenemies0();
        rotation=0;
        loadingscreen->showMessage("Getting the world ready for your arrival");
        qApp->processEvents();
        contr->sortMap();
        loadingscreen->showMessage("Constructing the world with Lego");
        qApp->processEvents();
        Controller::getInstance()->setTrackprotagonist(false);
        isometricview->draw_world();
        viewone->updateScaleFactor();
        setImgLabel(filename);
        contr->setGameOver(false);
    }
    else
        QMessageBox::information(this, tr("Error"),"failed to load selected image");

    loadingscreen->showMessage("finishing loading");
    qApp->processEvents();
    loadingscreen->close();

    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(contr->getWorld()->getProta().get(), SIGNAL(energyChanged(int)), this, SLOT(energyChanged(int)));
    connect(contr->getWorld()->getProta().get(), SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));
}
void MainWindow::selectNewMapFile()
{
    disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(contr->getWorld()->getProta().get(), SIGNAL(energyChanged(int)), this, SLOT(energyChanged(int)));
    disconnect(contr->getWorld()->getProta().get(), SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Choose maze"),
                "../Game/img", //This line points to the resource folder
                "Image Files (*.jpeg, *.png);; All files (*.*)"
                );
    if(!filename.isEmpty())
        loadNewWorld(filename);
    else
        QMessageBox::information(this, tr("Error"),"failed to load selected image");
}

/*EVENTS*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    QWidgetList widgets =QApplication::topLevelWidgets();
    contr->setAutoplayOn(false);
    for(QWidget* widget: widgets)
        widget->close();
    QApplication::exit();
}
void MainWindow::wheelEvent(QWheelEvent *event)
{
    ui->graphview_map->horizontalScrollBar()->setEnabled(false);
    ui->graphview_map->verticalScrollBar()->setEnabled(false);
    if(processingKeyEvent)
        return;
    processingKeyEvent=true;
    if(contr->getGameOver())
        return;

    viewone->setInteractive(true);
    viewone->setDragMode(QGraphicsView::ScrollHandDrag);
    viewone->setFocusPolicy(Qt::WheelFocus);

    disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));

    if(ui->tabWidget->currentIndex()==0)
    {
        viewone->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor = 0.25;

        // If ctrl pressed, use original functionality with scrollbars
        if (event->modifiers() & Qt::ControlModifier){
            ui->graphview_map->horizontalScrollBar()->setEnabled(true);
            ui->graphview_map->verticalScrollBar()->setEnabled(true);
            processingKeyEvent=false;
            return;
        }

        // Otherwise, do zooming
        else
        {
            if(event->delta() > 0)
            {
                viewone->setMap_scale(std::min(100.0,(viewone->getMap_scale())+scaleFactor));
                viewone->refreshSceneImage();
            }
            else
            {
                viewone->setMap_scale(std::max(0.0,(viewone->getMap_scale())-scaleFactor));
                viewone->refreshSceneImage();
            }
            viewone->refreshSceneImage();
        }
    }
    processingKeyEvent=false;
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(processingKeyEvent)
        return;
    processingKeyEvent=true;

    if(contr->getGameOver())
        return;
    disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));


    if(ui->tabWidget->currentIndex()==0){//Viewone
        switch(event->key()){
            case Qt::Key_Left:
                contr->moveProtaDir(direction::LEFT);
            break;
            case Qt::Key_Right:
                contr->moveProtaDir(direction::RIGHT);
            break;
            case Qt::Key_Up:
                contr->moveProtaDir(direction::UP);
            break;
            case Qt::Key_Down:
                contr->moveProtaDir(direction::DOWN);
            break;
        }
    }
    else{//isometric view
        if(event->key()== Qt::Key_Left)
        {
            switch (rotation) {
                case 1:{
                    contr->moveProtaDir(direction::RIGHT);
                    break;
                }
                case 2:{
                    contr->moveProtaDir(direction::UP);
                    break;
                }
                case 3:{
                    contr->moveProtaDir(direction::LEFT);
                    break;
                }
                default:{
                    contr->moveProtaDir(direction::DOWN);
                    break;
                }
            }
        }
        else if(event->key() == Qt::Key_Right)
        {
            switch (rotation) {
                case 1:{
                    contr->moveProtaDir(direction::LEFT);
                    break;
                }
                case 2:{
                    contr->moveProtaDir(direction::DOWN);
                    break;
                }
                case 3:{
                    contr->moveProtaDir(direction::RIGHT);
                    break;
                }
                default:{
                    contr->moveProtaDir(direction::UP);
                    break;
                }
            }
        }
        else if(event->key() == Qt::Key_Up)
        {
            switch (rotation) {
                case 1:{
                    contr->moveProtaDir(direction::DOWN);
                    break;
                }
                case 2:{
                    contr->moveProtaDir(direction::RIGHT);
                    break;
                }
                case 3:{
                    contr->moveProtaDir(direction::UP);
                    break;
                }
                default:{
                    contr->moveProtaDir(direction::LEFT);
                    break;
                }
            }
        }
        else if(event->key() == Qt::Key_Down)
        {
            switch (rotation) {
                case 1:{
                    contr->moveProtaDir(direction::UP);
                    break;
                }
                case 2:{
                    contr->moveProtaDir(direction::LEFT);
                    break;
                }
                case 3:{
                    contr->moveProtaDir(direction::DOWN);
                    break;
                }
                default:{
                    contr->moveProtaDir(direction::RIGHT);
                    break;
                }
            }
        }
    }

    ui->graphview_map2->scene()->clear();
    ui->graphview_map2->resetTransform();
    isometricview->draw_world();
    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    processingKeyEvent=false;
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(viewone!=nullptr)
        viewone->updateScaleFactor();
    if(isometricview!=nullptr){
        isometricview->draw_world();
    }
}


/*GETTERS AND SETTERS*/
isometricView *MainWindow::getIsometricview() const
{
    return isometricview;
}
ViewOne *MainWindow::getViewone() const
{
    return viewone;
}
void MainWindow::setViewone(ViewOne *value)
{
    viewone = value;
}
unsigned int MainWindow::getCurrentTabIndex()
{
    return static_cast<unsigned int>(ui->tabWidget->currentIndex());
}
int MainWindow::getRotation() const
{
    return rotation;
}
void MainWindow::setRotation(int value)
{
    rotation = value;
}

/*PRIVATE SLOTS*/
void MainWindow::energyChanged(int energy)
{
    this->getUi()->energybar->setValue(energy);
    this->getUi()->energybar2->setValue(energy);
}
void MainWindow::healthChanged(int health)
{
    this->getUi()->healthbar->setValue(health);
    this->getUi()->healthbar2->setValue(health);
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==0)
        viewone->updateScaleFactor();
    else
        isometricview->draw_world();
}

//-> ISOMETRIC VIEW INTERACTION
void MainWindow::tracking(bool status)
{
    contr->setTrackprotagonist(status);
    if(status){
        // if we redraw when status changed to false , the screen goes to a different location somehow this bypasses this problem
        isometricView::getInstance()->draw_world();
    }
}
void MainWindow::on_rotate_button_clicked()
{
    Controller::getInstance()->playSound(6);
    LoadingScreen *loadingscreen = new LoadingScreen;
    loadingscreen->setPixmap(QPixmap(":/img/Loading_Screen.png"));
    loadingscreen->showMessage("doing rotatas");
    qApp->processEvents();
    QString map_file = "../Game/img/minimaze_20x20.png";
    rotation++;
    if(rotation >=4){
        rotation =0;
    }
    MyWorld* world = contr->getWorld();
    disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    switch (rotation) {

        case 1:{
            //world->sortmap90();
            world->sortHealthpacks90();
            world->sortenemies90();
            break;
        }
        case 2:{
            //world->sortmap180();
            world->sortHealthpacks180();
            world->sortenemies180();
            break;
        }
        case 3:{
            //world->sortmap270();
            world->sortHealthpacks270();
            world->sortenemies270();
            break;
        }
        default:{
            //world->sortmap0();
            world->sortHealthpacks0();
            world->sortenemies0();
            break;
        }

    }
    ui->graphview_map2->scene()->clear();
    ui->graphview_map2->resetTransform();
    contr->sortMap();
    isometricview->draw_world();
    loadingscreen->close();
    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
}
void MainWindow::onScrollIsometric(int)
{
    disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    // clear the scene and reset the transformations done on the graphicalview
    ui->graphview_map2->scene()->clear();
    ui->graphview_map2->resetTransform();

    isometricview->draw_world();

    ui->graphview_map2->verticalScrollBar()->setMaximum(50*contr->getWorld()->getCols());
    ui->graphview_map2->horizontalScrollBar()->setMaximum(50*contr->getWorld()->getRows());
    connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
    connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));

}

//-> FILE INTERACTION
void MainWindow::on_openFile_button_clicked()
{
    selectNewMapFile();
}
void MainWindow::on_openFile_button2_clicked()
{
    selectNewMapFile();
}
void MainWindow::on_saveButton_clicked()
{
    //checking if a folder exists and if not makes is
    QDir dir("../Game/Saves");
    if (!dir.exists()){
        dir.mkpath(".");
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Game"), "../Game/Saves",
                                                    tr("Saved Games (*);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream stream( &file );

        stream << contr->getMapfile()<<endl;
        qDebug() << "finished saving map";
        stream << "map_done"<<endl;
        //write protagonist to file
        std::shared_ptr<MyProtagonist> prot = contr->getWorld()->getProta();
        stream << prot->getEnergy()<< endl;
        stream << prot->getHealth()<< endl;
        stream << prot->getValue()<< endl;
        stream << prot->getXPos()<< endl;
        stream << prot->getYPos()<< endl;

        stream << "protagonist_done"<<endl;
        qDebug() << "player finished saving";

        for (std::shared_ptr<Enemy> enemy : contr->getWorld()->getEnemies()){

            stream << enemy->getValue()<< endl;
            stream << enemy->getXPos()<< endl;
            stream << enemy->getYPos()<< endl;
            if(enemy->getDefeated()){
                stream << "true"<< endl;
            }
            else{
                stream << "false"<< endl;
            }

            if(dynamic_cast<PEnemy*>(enemy.get())){
                stream << "PEnemy"<< endl;
            }
            else if(dynamic_cast<XEnemy*>(enemy.get())) {
                stream << "XEnemy"<< endl;
                stream << dynamic_cast<XEnemy*>(enemy.get())->getChildren()<< endl;
                stream << dynamic_cast<XEnemy*>(enemy.get())->getSpawnRange()<< endl;

            }
            else if (dynamic_cast<BabyEnemy*>(enemy.get())){
                stream << "BabyEnemy"<< endl;
            }
            // cast last to the RegEnemy since this should always succeed
            else if(dynamic_cast<Enemy*>(enemy.get()))
            {
                stream << "RegEnemy"<< endl;
            }
            //need to create class xenemys

            else{
                //shoudn't come here
            }
        }
        stream << "enemies_done"<< endl;
        qDebug() << "finished saving enemies";

        for (std::shared_ptr<MyHealthpack> healthpack : contr->getWorld()->getHealthpacks()){
            stream << healthpack->getHealth()<< endl;
            stream << healthpack->getX()<< endl;
            stream << healthpack->getY()<< endl;
            if(healthpack->getUsed()){
                stream <<"true"<< endl;
            }
            else{
                stream <<"false"<< endl;
            }
        }
        stream << "healthpacks_done"<< endl;


    }
}
void MainWindow::on_saveButton2_clicked()
{
    on_saveButton_clicked();

}
void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Save Game"), "../Game/Saves",
                                                    tr("Saved Games (*);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else{
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            std::shared_ptr<MyProtagonist> prota = std::make_shared<MyProtagonist>(0,0);
            std::vector<std::shared_ptr<Enemy>> Enemies;
            std::vector<std::shared_ptr<MyHealthpack>> healthpacks;
            QString filelocation;
            int counter=-1;
            float value=0;
            int xpos=0;
            int ypos=0;
            float energy=0;
            float health=0;
            bool used_defeated =false;
            int children=0;
            int range=0;
            bool map_done =false;
            bool prota_done = false;
            bool enemies_done = false;
            bool healthpacks_done = false;
            while (!in.atEnd())
            {
                QString line = in.readLine();
                counter ++;
                if(line == "map_done")
                    map_done = true;
                else if(line == "protagonist_done")
                    prota_done = true;
                else if (line == "enemies_done")
                    enemies_done = true;
                else if (line == "healthpacks_done")
                    healthpacks_done = true;
                if(not map_done)
                    filelocation = line;
                else if(not prota_done){
                    if(line == "map_done")
                        counter =-1;
                    else{
                        switch (counter) {
                            case 0:
                                energy = line.toFloat();
                            break;
                            case 1:
                                health = line.toFloat();
                            break;
                            case 2:
                                value = line.toFloat();
                            break;
                            case 3:
                                xpos = line.toInt();
                            break;
                            case 4:{
                                ypos = line.toInt();
                                prota->setEnergy(energy);
                                prota->setHealth(health);
                                prota->setValue(value);
                                prota->setPos(xpos,ypos);
                                counter =-1;
                                break;
                            }
                            default:
                            break;
                        }
                    }
                }
                else if(not enemies_done){

                    if(line == "protagonist_done")
                        counter =-1;
                    else{
                        switch (counter) {
                            case 0:
                                value = line.toFloat();
                            break;
                            case 1:
                                xpos = line.toInt();
                            break;
                            case 2:
                                ypos = line.toInt();
                            break;
                            case 3:{
                                if(line =="true")
                                    used_defeated = true;
                                else
                                    used_defeated=false;
                                break;
                            }
                            case 4:{
                                if(line !="XEnemy"){
                                    std::shared_ptr<Enemy> enemy;
                                    if(line == "PEnemy")
                                        enemy =std::make_shared<PEnemy>(xpos,ypos,value);
                                    else if(line =="BabyEnemy")
                                        enemy =std::make_shared<BabyEnemy>(xpos,ypos,value);
                                    else if(line == "RegEnemy")
                                        enemy =std::make_shared<Enemy>(xpos,ypos,value);
                                    if(used_defeated)
                                        enemy->setDefeated(true);
                                    else
                                        enemy->setDefeated(false);
                                    Enemies.push_back(enemy);
                                    counter =-1;
                                }
                                break;
                            }
                            case 5:
                                children = line.toInt();
                            break;
                            case 6:{
                                range = line.toInt();
                                std::shared_ptr<XEnemy> enemy = std::make_shared<XEnemy>(xpos, ypos,value,static_cast<unsigned int>(range),static_cast<unsigned int>(children));

                                if(used_defeated)
                                    enemy->setDefeatedWithNoSpawn(true);
                                else
                                    enemy->setDefeatedWithNoSpawn(false);
                                Enemies.push_back(enemy);
                                counter =-1;
                                break;
                            }
                            default:
                            break;
                        }
                    }
                }
                else if (not healthpacks_done){
                    if(line == "enemies_done")
                        counter =-1;
                    else{
                        switch (counter) {
                            case 0:
                                value = line.toFloat();
                            break;
                            case 1:
                                xpos = line.toInt();
                            break;
                            case 2:
                                ypos = line.toInt();
                            break;
                            case 3:{
                                std::shared_ptr<MyHealthpack> hppack = std::make_shared<MyHealthpack>(xpos,ypos,value);
                                if(line =="true")
                                    hppack->setUsed(true);
                                else
                                    hppack->setUsed(false);
                                healthpacks.push_back(hppack);
                                counter =-1;
                                break;
                            }
                            default:
                            break;
                        }
                    }
                }
            }
            inputFile.close();

            disconnect(contr->getWorld()->getProta().get(), SIGNAL(energyChanged(int)), this, SLOT(energyChanged(int)));
            disconnect(contr->getWorld()->getProta().get(), SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));
            //make the loaded map the real map
            contr->setWorld(filelocation);
            contr->getWorld()->setEnemies(Enemies);
            contr->getWorld()->setHealthpacks(healthpacks);
            contr->getWorld()->setProta(prota);


            /*DEBUG PRINTING*/
            qDebug() << "loading should be done";

            qDebug() <<"PROTAGONIST";
            qDebug() <<"xpos " << prota->getXPos() << "ypos " << prota->getYPos() << "value " << prota->getValue() << "energy "<< prota->getEnergy() << "health " << prota->getHealth();

            qDebug() << "ENEMIES";
            for (std::shared_ptr<Enemy> enemy : contr->getWorld()->getEnemies())
                qDebug() <<"xpos " << enemy->getXPos() << "ypos " << enemy->getYPos() << "value " << enemy->getValue() << "defeated "<< enemy->getDefeated();

            qDebug() << "HEALTHPACKS";
            for (std::shared_ptr<MyHealthpack> healthpack : contr->getWorld()->getHealthpacks())
                qDebug() <<"xpos " << healthpack->getX() << "ypos " <<healthpack->getY() << "value " << healthpack->getHealth() << "used " << healthpack->getUsed();


            disconnect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
            disconnect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
            isometricview->draw_world();
            viewone->initMap(contr->getWorld()->getMap(),contr->getMapfile());
            viewone->updateScaleFactor();
            //reconnect the signals again
            connect(ui->graphview_map2->verticalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
            connect(ui->graphview_map2->horizontalScrollBar(), SIGNAL(valueChanged (int)), this, SLOT(onScrollIsometric(int)));
            connect(contr->getWorld()->getProta().get(), SIGNAL(energyChanged(int)), this, SLOT(energyChanged(int)));
            connect(contr->getWorld()->getProta().get(), SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));
            //emit signal that new map has loaded so that the controller can adapt itself to the new signals
            emit newMapLoaded();
        }
    }
}
void MainWindow::on_loadButton2_clicked()
{
    on_loadButton_clicked();
}

//-> AUTOPLAY INTERACTION
void MainWindow::on_play_button_released()
{

    contr->autoPlay();
}
void MainWindow::on_play_button2_released()
{
    contr->autoPlay();
}
void MainWindow::on_speed_slider_valueChanged(int value)
{
    updateSpeedValue(value);
}
void MainWindow::on_speed_slider2_valueChanged(int value)
{
    updateSpeedValue(value);
}


//PATHFINDING INTERACTION
//HEURISTIC WEIGHT
void MainWindow::on_heurweight_slider_sliderReleased()
{
    float newWeight = float(ui->heurweight_slider->value())/100;
    updateHeurweights(newWeight);
}
void MainWindow::on_heurweight_slider2_sliderReleased()
{
    float newWeight = float(ui->heurweight_slider2->value())/100;
    updateHeurweights(newWeight);
}
void MainWindow::on_heurweight_slider_valueChanged(int value)
{
    ui->heurweight_value->setText(QString::number(double(value)/100));
    ui->heurweight_value2->setText(QString::number(double(value)/100));
}
void MainWindow::on_heurweight_slider2_valueChanged(int value)
{
    on_heurweight_slider_valueChanged(value);
}
//STEPCOST
void MainWindow::on_updateStepCost_button_released()
{

    double stepCost1 = ui->stepCost1_value->value();
    double stepCost2 = ui->stepCost2_value->value();
    updateStepCosts(stepCost1,stepCost2);
}
void MainWindow::on_updateStepCost_button2_released()
{

    double stepCost1 = ui->stepCost1_value2->value();
    double stepCost2 = ui->stepCost2_value2->value();
    updateStepCosts(stepCost1,stepCost2);
}
//START END DEST
void MainWindow::on_setstart_button2_released()
{

    unsigned int x = static_cast<unsigned int>(ui->setstart_x2->value());
    unsigned int y = static_cast<unsigned int>(ui->setstart_y2->value());
    updateStartValue(x,y);
}
void MainWindow::on_setdest_button2_released()
{
    unsigned int x = static_cast<unsigned int>(ui->setdest_x2->value());
    unsigned int y = static_cast<unsigned int>(ui->setdest_y2->value());
    updateDestValue(x,y);
}
void MainWindow::on_setstart_button_released()
{

    unsigned int x = static_cast<unsigned int>(ui->setstart_x->value());
    unsigned int y = static_cast<unsigned int>(ui->setstart_y->value());
    updateStartValue(x,y);
}
void MainWindow::on_setdest_button_released()
{
    unsigned int x = static_cast<unsigned int>(ui->setdest_x->value());
    unsigned int y = static_cast<unsigned int>(ui->setdest_y->value());
    updateDestValue(x,y);
}
//SEARCH PATH
void MainWindow::on_start_button_released()
{

    contr->pathfindingShowCase();
}
void MainWindow::on_startbutton_2_released()
{
    on_start_button_released();
}
