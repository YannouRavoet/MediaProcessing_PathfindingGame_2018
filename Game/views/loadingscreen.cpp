#include "loadingscreen.h"

LoadingScreen::LoadingScreen()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setPixmap(QPixmap(imgFile));
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);
    show();
    ensureFirstPaint();
}
