#ifndef MYSPLASHSCREEN_H
#define MYSPLASHSCREEN_H
#include <QThread>
#include <QApplication>
#include <QSplashScreen>

class MySplashScreen:public QSplashScreen
{
    void paintEvent(QPaintEvent* e) override;
public:
    MySplashScreen();
    void showMessage(const char* message);
    void ensureFirstPaint() const;

private:
    bool painted=false;
};

#endif // MYSPLASHSCREEN_H
