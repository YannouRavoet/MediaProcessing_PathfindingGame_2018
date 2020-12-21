#include "defeatscreen.h"
#include "ui_endofgamescreen.h"
#include <QtGui>

DefeatScreen::DefeatScreen():EndOfGameScreen ()
{
    setWindowTitle("Try a bit harder, will you?");
    setStyleSheet("background-image: url(:/img/Defeat_Screen.png);");
    getUi()->giflabel->setVisible(false);
}
