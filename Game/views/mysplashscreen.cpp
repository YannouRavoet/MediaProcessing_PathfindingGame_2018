#include "mysplashscreen.h"
void MySplashScreen::paintEvent(QPaintEvent *e)
{
    QSplashScreen::paintEvent(e);
    painted=true;
}

MySplashScreen::MySplashScreen()
{
}

void MySplashScreen::showMessage(const char* message)
{
    QSplashScreen::showMessage(QSplashScreen::tr(message), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
}

void MySplashScreen::ensureFirstPaint() const
{
    while(!painted)
    {
        QThread::usleep(500);
        qApp->processEvents();
    }
}
