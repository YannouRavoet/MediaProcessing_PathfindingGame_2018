#-------------------------------------------------
#
# Project created by QtCreator 2018-10-31T11:42:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        pathfinding.cpp \
    controller.cpp \
    views/enemyview.cpp \
    views/healthpackview.cpp \
    views/penemyview.cpp \
    views/protagonistview.cpp \
    views/regenemyview.cpp \
    views/viewone.cpp \
    helperclasses/myprotagonist.cpp \
    helperclasses/mytile.cpp \
    helperclasses/myworld.cpp \
    helperclasses/myhealthpack.cpp\
    views/isometricview.cpp \
    views/xenemyview.cpp \
    views/babyenemyview.cpp \
    helperclasses/xenemy.cpp \
    helperclasses/babyenemy.cpp \
    views/mysplashscreen.cpp \
    views/loadingscreen.cpp \
    endofgamescreen.cpp \
    victoryscreen.cpp \
    defeatscreen.cpp

HEADERS += \
        mainwindow.h \
    pathfinding.h \
    controller.h \
    views/enemyview.h \
    views/healthpackview.h \
    views/penemyview.h \
    views/protagonistview.h \
    views/regenemyview.h \
    views/viewone.h \
    helperclasses/myprotagonist.h \
    helperclasses/mytile.h \
    helperclasses/myworld.h \
    helperclasses/world.h \
    helperclasses/world_global.h \
    helperclasses/myhealthpack.h\
    views/isometricview.h \
    views/xenemyview.h \
    views/babyenemyview.h \
    helperclasses/xenemy.h \
    helperclasses/babyenemy.h \
    helperclasses/direction.h \
    views/mysplashscreen.h \
    views/loadingscreen.h \
    endofgamescreen.h \
    victoryscreen.h \
    defeatscreen.h


FORMS += \
        mainwindow.ui \
    endofgamescreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



unix:!macx: LIBS += -L$$PWD/lib -lworld

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

DISTFILES += \
    lib/libworld.so \
    lib/libworld.so.1 \
    lib/libworld.so.1.0 \
    lib/libworld.so.1.0.0 \
    img/maze1.png \
    img/maze2.png \
    img/maze3.png \
    img/worldmap4.png \
    img/enemyDead.png \
    img/healthpack.png \
    img/pEnemyAlive.png \
    img/protagonistAlive.png \
    img/protagonistDead.png \
    img/regEnemyAlive.png \
    img/minimaze_20x20.png \
    img/minimaze_10x10.png \
    img/minimaze_100x100.png \
    img/maze_201x201.png \
    img/wall_50x50.png \
    img/pacman_icon.png \
    img/maze_1500x1500BW.png \
    img/minimaze_10x10_BW.png \
    img/minimaze_40x40_BW.png \
    img/deadBlueGhost.png \
    img/deadGreenGhost.png \
    img/deadRedGhost.png \
    UML.png

RESOURCES += \
    resource.qrc
