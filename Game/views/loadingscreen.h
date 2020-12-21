#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include "mysplashscreen.h"

class LoadingScreen:public MySplashScreen
{
public:
    LoadingScreen();

private:
    QString imgFile =":/img/Loading_Screen.png";

};
#endif // LOADINGSCREEN_H
