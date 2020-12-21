#include <memory>
#include <QThread>
#include <QApplication>
#include "mainwindow.h"
#include "controller.h"
#include "views/loadingscreen.h"
#include "views/viewone.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingScreen *splash = new LoadingScreen();
    splash->showMessage("Creating a Controller...");
    a.processEvents();
    Controller* contr = Controller::getInstance();
    contr->init(&a,splash);
    splash->finish(contr->getWindow());
    std::shared_ptr<QSound>  welcomesound = std::make_shared<QSound>(":/audio/Welcome.wav");
    welcomesound->play();

    a.exec();
    return 0;
}

