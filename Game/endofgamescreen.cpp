#include "endofgamescreen.h"
#include "ui_endofgamescreen.h"
#include <QThread>
#include "views/viewone.h"
#include "views/isometricview.h"

EndOfGameScreen::EndOfGameScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndOfGameScreen)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    show();
}

EndOfGameScreen::~EndOfGameScreen()
{
    delete ui;
}

void EndOfGameScreen::on_reloadButton_released()
{
    close();
    Controller::getInstance()->getWindow()->loadNewWorld(Controller::getInstance()->getMapfile());
}

void EndOfGameScreen::on_newmapButton_released()
{
    close();
    Controller::getInstance()->getWindow()->selectNewMapFile();

}

void EndOfGameScreen::on_exitButton_released()
{
    Controller::getInstance()->stopSound();
    Controller::getInstance()->playSound(9);
    QThread::sleep(4);
    Controller::getInstance()->getWindow()->closeEvent(nullptr);
}

Ui::EndOfGameScreen *EndOfGameScreen::getUi() const
{
    return ui;
}
