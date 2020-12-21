#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <ui_mainwindow.h>

#include "controller.h"
#include "helperclasses/myworld.h"


class isometricView;
class ViewOne;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *getUi() const;
    void addTextToOutput(QString text);

    /*UI INTERACTION*/
    void updateHeurweights(float weight);
    void updateStepCosts(double cost1, double cost2);
    void updateStepCostLabels(double cost1,double cost2);
    void updateEnemyLabels();
    void setImgLabel(QString filename);
    void updateSpeedValue(int value);
    void updateHealthvalue(int value);
    void updateEnergyvalue(int value);
    void updateStartValue(unsigned int x, unsigned int y);
    void updateDestValue(unsigned int x, unsigned int y);
    void updateMaximumXandY(int x, int y);
    void loadNewWorld(QString filename);
    void selectNewMapFile();

    /*EVENTS*/
    void closeEvent(QCloseEvent* event);
    void wheelEvent(QWheelEvent * event );
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent*event);

    /*GETTERS AND SETTERS*/
    isometricView *getIsometricview() const;
    ViewOne *getViewone() const;
    void setViewone(ViewOne *value);
    unsigned int getCurrentTabIndex();
    int getRotation() const;
    void setRotation(int value);

signals:
    void newMapLoaded();

public slots:


private slots:
    void energyChanged(int energy);
    void healthChanged(int health);
    void on_tabWidget_currentChanged(int index);


    //ISOMETRIC VIEW INTERACTION
    void tracking(bool status);
    void on_rotate_button_clicked();
    void onScrollIsometric(int);

    //FILE INTERACTION
    void on_openFile_button_clicked();
    void on_openFile_button2_clicked();
    void on_saveButton_clicked();
    void on_saveButton2_clicked();
    void on_loadButton_clicked();
    void on_loadButton2_clicked();

    //AUTOPLAY INTERACTION
    void on_play_button_released();
    void on_play_button2_released();
    void on_speed_slider_valueChanged(int value);
    void on_speed_slider2_valueChanged(int value);

    //PATHFINDING INTERACTION
    //HEURISTIC WEIGHT
    void on_heurweight_slider_sliderReleased();
    void on_heurweight_slider2_sliderReleased();
    void on_heurweight_slider_valueChanged(int value);
    void on_heurweight_slider2_valueChanged(int value);
    //STEPCOST
    void on_updateStepCost_button_released();
    void on_updateStepCost_button2_released();

    //START EN DEST
    void on_setstart_button2_released();
    void on_setdest_button2_released();
    void on_setstart_button_released();
    void on_setdest_button_released();
    //SEARCH PATH
    void on_start_button_released();
    void on_startbutton_2_released();


private:
    Ui::MainWindow *ui;
    QString* text;
    Controller* contr;
    isometricView* isometricview=nullptr;
    ViewOne* viewone=nullptr;
    int rotation=0;
    bool processingKeyEvent=false;

};

#endif // MAINWINDOW_H

