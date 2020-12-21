#include "victoryscreen.h"
#include "ui_endofgamescreen.h"
#include <QtGui>

VictoryScreen::VictoryScreen(): EndOfGameScreen ()
{
    setWindowTitle("Congratulations with your victory!");
    setStyleSheet("background-image: url(:/img/Victory_Screen.png);");
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int random = rand()%6;
    QString gifFile = QString(":/img/robotdance").append(QString::number(random)).append(QString(".gif"));
    movie = new QMovie(gifFile);
    getUi()->giflabel->setMovie(movie);
    movie->start();
}

VictoryScreen::~VictoryScreen()
{
    delete movie;
}
