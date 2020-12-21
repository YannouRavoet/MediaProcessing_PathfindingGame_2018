#ifndef ENDOFGAMESCREEN_H
#define ENDOFGAMESCREEN_H

#include <QDialog>
#include "controller.h"
#include "mainwindow.h"

namespace Ui {
class EndOfGameScreen;
}

class EndOfGameScreen : public QDialog
{
    Q_OBJECT

public:
    explicit EndOfGameScreen(QWidget *parent = nullptr);
    ~EndOfGameScreen();

    Ui::EndOfGameScreen *getUi() const;

private slots:
    void on_reloadButton_released();

    void on_newmapButton_released();

    void on_exitButton_released();

private:
    Ui::EndOfGameScreen *ui;
};

#endif // ENDOFGAMESCREEN_H
