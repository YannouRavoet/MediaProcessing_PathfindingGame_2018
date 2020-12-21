/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphview_map;
    QVBoxLayout *ver_rightside;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QWidget *ver_overviewWidget;
    QVBoxLayout *ver_overview;
    QHBoxLayout *hor_fileinteraction;
    QPushButton *openFile_button;
    QLabel *img_label;
    QPushButton *rotate_button_disabled;
    QHBoxLayout *hor_time;
    QPushButton *play_button;
    QLabel *speed_label;
    QSlider *speed_slider;
    QLabel *speed_xlabel;
    QLabel *speed_value;
    QHBoxLayout *hor_health;
    QLabel *health_label;
    QProgressBar *healthbar;
    QHBoxLayout *hor_energy;
    QLabel *energy_label;
    QProgressBar *energybar;
    QHBoxLayout *hor_enemies;
    QLabel *enemies_label;
    QLabel *enemies_left;
    QLabel *enemies_slash;
    QLabel *enemies_total;
    QVBoxLayout *ver_pathfinding;
    QHBoxLayout *hor_pathfinding_ui1;
    QSpinBox *setstart_x;
    QSpinBox *setstart_y;
    QPushButton *setstart_button;
    QSpinBox *setdest_x;
    QSpinBox *setdest_y;
    QPushButton *setdest_button;
    QHBoxLayout *hor_pathfinding_ui2;
    QPushButton *start_button;
    QLabel *heurweight_label;
    QSlider *heurweight_slider;
    QLabel *heurweight_value;
    QHBoxLayout *hor_pathfinding_ui3;
    QLabel *stepCost1_label;
    QDoubleSpinBox *stepCost1_value;
    QLabel *stepCost2_label;
    QDoubleSpinBox *stepCost2_value;
    QPushButton *updateStepCost_button;
    QTextBrowser *textoutput;
    QWidget *tab2;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphview_map2;
    QVBoxLayout *vert_rightside2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *saveButton2;
    QPushButton *loadButton2;
    QWidget *ver_overviewWidget2;
    QVBoxLayout *ver_overview2;
    QHBoxLayout *hor_fileinteraction2;
    QPushButton *openFile_button2;
    QLabel *img_label2;
    QPushButton *rotate_button;
    QHBoxLayout *hor_time2;
    QPushButton *play_button2;
    QLabel *speed_label2;
    QSlider *speed_slider2;
    QLabel *speed_xlabel2;
    QLabel *speed_value2;
    QHBoxLayout *hor_health2;
    QLabel *health_label2;
    QProgressBar *healthbar2;
    QHBoxLayout *hor_energy2;
    QLabel *energy_label2;
    QProgressBar *energybar2;
    QHBoxLayout *hor_enemies2;
    QLabel *enemies_label2;
    QLabel *enemies_left2;
    QLabel *enemies_slash2;
    QLabel *enemies_total2;
    QVBoxLayout *ver_pathfinding2;
    QHBoxLayout *hor_pathfinding_ui1_2;
    QSpinBox *setstart_x2;
    QSpinBox *setstart_y2;
    QPushButton *setstart_button2;
    QSpinBox *setdest_x2;
    QSpinBox *setdest_y2;
    QPushButton *setdest_button2;
    QHBoxLayout *hor_pathfinding_ui2_2;
    QPushButton *startbutton_2;
    QLabel *heurweight_label2;
    QSlider *heurweight_slider2;
    QLabel *heurweight_value2;
    QHBoxLayout *hor_pathfinding_ui3_2;
    QLabel *stepCost1_label2;
    QDoubleSpinBox *stepCost1_value2;
    QLabel *stepCost2_label2;
    QDoubleSpinBox *stepCost2_value2;
    QPushButton *updateStepCost_button2;
    QRadioButton *trackProta;
    QTextBrowser *textoutput2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 744);
        MainWindow->setMinimumSize(QSize(1024, 576));
        MainWindow->setMaximumSize(QSize(3840, 2160));
        MainWindow->setStyleSheet(QString::fromUtf8("QToolTip\n"
"{\n"
"     border: 1px solid black;\n"
"     background-color: #ffa02f;\n"
"     padding: 1px;\n"
"     border-radius: 3px;\n"
"     opacity: 100;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"    background: transparent;\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"    background: #444;\n"
"    border: 1px solid #000;\n"
"    background-color: QLinearGradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:1 #212121,\n"
"        stop:0.4 #343434/*,\n"
"        stop:0.2 #3"
                        "43434,\n"
"        stop:0.1 #ffaa00*/\n"
"    );\n"
"    margin-bottom:-1px;\n"
"    padding-bottom:1px;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"    border: 1px solid #000;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"    padding: 2px 20px 2px 20px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QAbstractItemView\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\n"
"}\n"
"\n"
"QWidget:focus\n"
"{\n"
"    /*border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);*/\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b"
                        "1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #ffaa00;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QComboBox:hover,QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0,"
                        " x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"    selection-background-color: #ffaa00;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    border: 2px solid darkgray;\n"
"    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QComboBox::drop-down\n"
"{\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"     border-left-width: 0px;\n"
"     border-left-color: darkgray;\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 3px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 3px;\n"
" }\n"
"\n"
"QComboBox::down-arrow\n"
"{\n"
"     image: url(:/down_arrow.png"
                        ");\n"
"}\n"
"\n"
"QGroupBox:focus\n"
"{\n"
"border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QTextEdit:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"      subcon"
                        "trol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"      background: QLinearGradi"
                        "ent( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-page:vertical,"
                        " QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QPlainTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
"QCheckBox:disabled\n"
"{\n"
"color: #414141;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    text-align: center;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"    text-align: center;\n"
"    spacing: 1px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232"
                        ", stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover\n"
"{\n"
"    background: #242424;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed\n"
"{\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QToolBar::handle\n"
"{\n"
"     spacing: 3px; /* spacing between items in the t"
                        "ool bar */\n"
"     background: url(:/images/handle.png);\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"    height: 2px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
"\n"
"QProgressBar\n"
"{\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #d7801a;\n"
"    width: 2.15px;\n"
"    margin: 0.5px;\n"
"}\n"
"\n"
"QProgressBar#healthbar::chunk\n"
"{\n"
"	background-color:#ce0c0c\n"
"}\n"
"\n"
"QProgressBar#healthbar2::chunk\n"
"{\n"
"	background-color:#ce0c0c\n"
"}\n"
"\n"
"QProgressBar#energybar::chunk\n"
"{\n"
"	background-color:#13b2c4\n"
"}\n"
"\n"
"QProgressBar#energybar2::chunk\n"
"{\n"
"	background-color:#13b2c4\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    bord"
                        "er-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444;\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabBar::tab:last\n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    color: #b1b1b1;\n"
"    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
""
                        "\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked\n"
"{\n"
"    background-color: qradialgradient(\n"
"        cx: 0.5, cy: 0.5,\n"
"        fx: 0.5, fy: 0.5,\n"
"        radius: 1.0,\n"
"        stop: 0.25 #ffaa00,\n"
"        stop: 0.3 #323232\n"
"    );\n"
"}\n"
"\n"
"QCheckBox::indicator{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"QRadioButton::indicator\n"
"{\n"
"    border-radius: 6p"
                        "x;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover, QCheckBox::indicator:hover\n"
"{\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(:/images/checkbox.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:disabled, QRadioButton::indicator:disabled\n"
"{\n"
"    border: 1px solid #444;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        gridLayout_4 = new QGridLayout(tab1);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphview_map = new QGraphicsView(tab1);
        graphview_map->setObjectName(QString::fromUtf8("graphview_map"));
        graphview_map->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphview_map->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        horizontalLayout->addWidget(graphview_map);

        ver_rightside = new QVBoxLayout();
        ver_rightside->setSpacing(6);
        ver_rightside->setObjectName(QString::fromUtf8("ver_rightside"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        saveButton = new QPushButton(tab1);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_6->addWidget(saveButton);

        loadButton = new QPushButton(tab1);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        horizontalLayout_6->addWidget(loadButton);


        ver_rightside->addLayout(horizontalLayout_6);

        ver_overviewWidget = new QWidget(tab1);
        ver_overviewWidget->setObjectName(QString::fromUtf8("ver_overviewWidget"));
        ver_overviewWidget->setMinimumSize(QSize(500, 0));
        ver_overviewWidget->setMaximumSize(QSize(500, 400));
        ver_overview = new QVBoxLayout(ver_overviewWidget);
        ver_overview->setSpacing(6);
        ver_overview->setContentsMargins(11, 11, 11, 11);
        ver_overview->setObjectName(QString::fromUtf8("ver_overview"));
        ver_overview->setContentsMargins(0, 0, 0, 0);
        hor_fileinteraction = new QHBoxLayout();
        hor_fileinteraction->setSpacing(6);
        hor_fileinteraction->setObjectName(QString::fromUtf8("hor_fileinteraction"));
        openFile_button = new QPushButton(ver_overviewWidget);
        openFile_button->setObjectName(QString::fromUtf8("openFile_button"));

        hor_fileinteraction->addWidget(openFile_button);

        img_label = new QLabel(ver_overviewWidget);
        img_label->setObjectName(QString::fromUtf8("img_label"));

        hor_fileinteraction->addWidget(img_label);

        rotate_button_disabled = new QPushButton(ver_overviewWidget);
        rotate_button_disabled->setObjectName(QString::fromUtf8("rotate_button_disabled"));
        rotate_button_disabled->setEnabled(false);

        hor_fileinteraction->addWidget(rotate_button_disabled);


        ver_overview->addLayout(hor_fileinteraction);

        hor_time = new QHBoxLayout();
        hor_time->setSpacing(6);
        hor_time->setObjectName(QString::fromUtf8("hor_time"));
        play_button = new QPushButton(ver_overviewWidget);
        play_button->setObjectName(QString::fromUtf8("play_button"));

        hor_time->addWidget(play_button);

        speed_label = new QLabel(ver_overviewWidget);
        speed_label->setObjectName(QString::fromUtf8("speed_label"));

        hor_time->addWidget(speed_label);

        speed_slider = new QSlider(ver_overviewWidget);
        speed_slider->setObjectName(QString::fromUtf8("speed_slider"));
        speed_slider->setMinimum(1);
        speed_slider->setMaximum(1024);
        speed_slider->setSingleStep(1);
        speed_slider->setValue(1);
        speed_slider->setOrientation(Qt::Horizontal);

        hor_time->addWidget(speed_slider);

        speed_xlabel = new QLabel(ver_overviewWidget);
        speed_xlabel->setObjectName(QString::fromUtf8("speed_xlabel"));

        hor_time->addWidget(speed_xlabel);

        speed_value = new QLabel(ver_overviewWidget);
        speed_value->setObjectName(QString::fromUtf8("speed_value"));

        hor_time->addWidget(speed_value);


        ver_overview->addLayout(hor_time);

        hor_health = new QHBoxLayout();
        hor_health->setSpacing(6);
        hor_health->setObjectName(QString::fromUtf8("hor_health"));
        health_label = new QLabel(ver_overviewWidget);
        health_label->setObjectName(QString::fromUtf8("health_label"));
        health_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hor_health->addWidget(health_label);

        healthbar = new QProgressBar(ver_overviewWidget);
        healthbar->setObjectName(QString::fromUtf8("healthbar"));
        healthbar->setValue(100);
        healthbar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        healthbar->setTextVisible(false);
        healthbar->setOrientation(Qt::Horizontal);
        healthbar->setInvertedAppearance(true);

        hor_health->addWidget(healthbar);


        ver_overview->addLayout(hor_health);

        hor_energy = new QHBoxLayout();
        hor_energy->setSpacing(6);
        hor_energy->setObjectName(QString::fromUtf8("hor_energy"));
        energy_label = new QLabel(ver_overviewWidget);
        energy_label->setObjectName(QString::fromUtf8("energy_label"));
        energy_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hor_energy->addWidget(energy_label);

        energybar = new QProgressBar(ver_overviewWidget);
        energybar->setObjectName(QString::fromUtf8("energybar"));
        energybar->setValue(100);
        energybar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        energybar->setTextVisible(false);
        energybar->setInvertedAppearance(true);

        hor_energy->addWidget(energybar);


        ver_overview->addLayout(hor_energy);

        hor_enemies = new QHBoxLayout();
        hor_enemies->setSpacing(6);
        hor_enemies->setObjectName(QString::fromUtf8("hor_enemies"));
        enemies_label = new QLabel(ver_overviewWidget);
        enemies_label->setObjectName(QString::fromUtf8("enemies_label"));

        hor_enemies->addWidget(enemies_label);

        enemies_left = new QLabel(ver_overviewWidget);
        enemies_left->setObjectName(QString::fromUtf8("enemies_left"));

        hor_enemies->addWidget(enemies_left);

        enemies_slash = new QLabel(ver_overviewWidget);
        enemies_slash->setObjectName(QString::fromUtf8("enemies_slash"));

        hor_enemies->addWidget(enemies_slash);

        enemies_total = new QLabel(ver_overviewWidget);
        enemies_total->setObjectName(QString::fromUtf8("enemies_total"));

        hor_enemies->addWidget(enemies_total);


        ver_overview->addLayout(hor_enemies);

        ver_pathfinding = new QVBoxLayout();
        ver_pathfinding->setSpacing(6);
        ver_pathfinding->setObjectName(QString::fromUtf8("ver_pathfinding"));
        hor_pathfinding_ui1 = new QHBoxLayout();
        hor_pathfinding_ui1->setSpacing(6);
        hor_pathfinding_ui1->setObjectName(QString::fromUtf8("hor_pathfinding_ui1"));
        setstart_x = new QSpinBox(ver_overviewWidget);
        setstart_x->setObjectName(QString::fromUtf8("setstart_x"));

        hor_pathfinding_ui1->addWidget(setstart_x);

        setstart_y = new QSpinBox(ver_overviewWidget);
        setstart_y->setObjectName(QString::fromUtf8("setstart_y"));

        hor_pathfinding_ui1->addWidget(setstart_y);

        setstart_button = new QPushButton(ver_overviewWidget);
        setstart_button->setObjectName(QString::fromUtf8("setstart_button"));

        hor_pathfinding_ui1->addWidget(setstart_button);

        setdest_x = new QSpinBox(ver_overviewWidget);
        setdest_x->setObjectName(QString::fromUtf8("setdest_x"));

        hor_pathfinding_ui1->addWidget(setdest_x);

        setdest_y = new QSpinBox(ver_overviewWidget);
        setdest_y->setObjectName(QString::fromUtf8("setdest_y"));

        hor_pathfinding_ui1->addWidget(setdest_y);

        setdest_button = new QPushButton(ver_overviewWidget);
        setdest_button->setObjectName(QString::fromUtf8("setdest_button"));

        hor_pathfinding_ui1->addWidget(setdest_button);


        ver_pathfinding->addLayout(hor_pathfinding_ui1);

        hor_pathfinding_ui2 = new QHBoxLayout();
        hor_pathfinding_ui2->setSpacing(6);
        hor_pathfinding_ui2->setObjectName(QString::fromUtf8("hor_pathfinding_ui2"));
        start_button = new QPushButton(ver_overviewWidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));

        hor_pathfinding_ui2->addWidget(start_button);

        heurweight_label = new QLabel(ver_overviewWidget);
        heurweight_label->setObjectName(QString::fromUtf8("heurweight_label"));

        hor_pathfinding_ui2->addWidget(heurweight_label);

        heurweight_slider = new QSlider(ver_overviewWidget);
        heurweight_slider->setObjectName(QString::fromUtf8("heurweight_slider"));
        heurweight_slider->setMaximum(200000);
        heurweight_slider->setValue(0);
        heurweight_slider->setOrientation(Qt::Horizontal);
        heurweight_slider->setTickPosition(QSlider::NoTicks);
        heurweight_slider->setTickInterval(0);

        hor_pathfinding_ui2->addWidget(heurweight_slider);

        heurweight_value = new QLabel(ver_overviewWidget);
        heurweight_value->setObjectName(QString::fromUtf8("heurweight_value"));

        hor_pathfinding_ui2->addWidget(heurweight_value);


        ver_pathfinding->addLayout(hor_pathfinding_ui2);

        hor_pathfinding_ui3 = new QHBoxLayout();
        hor_pathfinding_ui3->setSpacing(6);
        hor_pathfinding_ui3->setObjectName(QString::fromUtf8("hor_pathfinding_ui3"));
        stepCost1_label = new QLabel(ver_overviewWidget);
        stepCost1_label->setObjectName(QString::fromUtf8("stepCost1_label"));

        hor_pathfinding_ui3->addWidget(stepCost1_label);

        stepCost1_value = new QDoubleSpinBox(ver_overviewWidget);
        stepCost1_value->setObjectName(QString::fromUtf8("stepCost1_value"));
        stepCost1_value->setDecimals(7);
        stepCost1_value->setMaximum(10.000000000000000);
        stepCost1_value->setSingleStep(0.000100000000000);

        hor_pathfinding_ui3->addWidget(stepCost1_value);

        stepCost2_label = new QLabel(ver_overviewWidget);
        stepCost2_label->setObjectName(QString::fromUtf8("stepCost2_label"));

        hor_pathfinding_ui3->addWidget(stepCost2_label);

        stepCost2_value = new QDoubleSpinBox(ver_overviewWidget);
        stepCost2_value->setObjectName(QString::fromUtf8("stepCost2_value"));
        stepCost2_value->setDecimals(7);
        stepCost2_value->setMaximum(10.000000000000000);
        stepCost2_value->setSingleStep(0.000100000000000);

        hor_pathfinding_ui3->addWidget(stepCost2_value);

        updateStepCost_button = new QPushButton(ver_overviewWidget);
        updateStepCost_button->setObjectName(QString::fromUtf8("updateStepCost_button"));

        hor_pathfinding_ui3->addWidget(updateStepCost_button);


        ver_pathfinding->addLayout(hor_pathfinding_ui3);


        ver_overview->addLayout(ver_pathfinding);


        ver_rightside->addWidget(ver_overviewWidget);

        textoutput = new QTextBrowser(tab1);
        textoutput->setObjectName(QString::fromUtf8("textoutput"));
        textoutput->setMinimumSize(QSize(500, 0));
        textoutput->setMaximumSize(QSize(500, 16777215));
        textoutput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textoutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textoutput->setLineWrapMode(QTextEdit::WidgetWidth);
        textoutput->setReadOnly(true);

        ver_rightside->addWidget(textoutput);


        horizontalLayout->addLayout(ver_rightside);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        gridLayout_6 = new QGridLayout(tab2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphview_map2 = new QGraphicsView(tab2);
        graphview_map2->setObjectName(QString::fromUtf8("graphview_map2"));
        graphview_map2->setResizeAnchor(QGraphicsView::NoAnchor);
        graphview_map2->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

        horizontalLayout_2->addWidget(graphview_map2);

        vert_rightside2 = new QVBoxLayout();
        vert_rightside2->setSpacing(6);
        vert_rightside2->setObjectName(QString::fromUtf8("vert_rightside2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        saveButton2 = new QPushButton(tab2);
        saveButton2->setObjectName(QString::fromUtf8("saveButton2"));

        horizontalLayout_7->addWidget(saveButton2);

        loadButton2 = new QPushButton(tab2);
        loadButton2->setObjectName(QString::fromUtf8("loadButton2"));

        horizontalLayout_7->addWidget(loadButton2);


        vert_rightside2->addLayout(horizontalLayout_7);

        ver_overviewWidget2 = new QWidget(tab2);
        ver_overviewWidget2->setObjectName(QString::fromUtf8("ver_overviewWidget2"));
        sizePolicy.setHeightForWidth(ver_overviewWidget2->sizePolicy().hasHeightForWidth());
        ver_overviewWidget2->setSizePolicy(sizePolicy);
        ver_overviewWidget2->setMinimumSize(QSize(500, 0));
        ver_overviewWidget2->setMaximumSize(QSize(500, 400));
        ver_overview2 = new QVBoxLayout(ver_overviewWidget2);
        ver_overview2->setSpacing(6);
        ver_overview2->setContentsMargins(11, 11, 11, 11);
        ver_overview2->setObjectName(QString::fromUtf8("ver_overview2"));
        ver_overview2->setContentsMargins(0, 0, 0, 0);
        hor_fileinteraction2 = new QHBoxLayout();
        hor_fileinteraction2->setSpacing(6);
        hor_fileinteraction2->setObjectName(QString::fromUtf8("hor_fileinteraction2"));
        openFile_button2 = new QPushButton(ver_overviewWidget2);
        openFile_button2->setObjectName(QString::fromUtf8("openFile_button2"));

        hor_fileinteraction2->addWidget(openFile_button2);

        img_label2 = new QLabel(ver_overviewWidget2);
        img_label2->setObjectName(QString::fromUtf8("img_label2"));

        hor_fileinteraction2->addWidget(img_label2);

        rotate_button = new QPushButton(ver_overviewWidget2);
        rotate_button->setObjectName(QString::fromUtf8("rotate_button"));

        hor_fileinteraction2->addWidget(rotate_button);


        ver_overview2->addLayout(hor_fileinteraction2);

        hor_time2 = new QHBoxLayout();
        hor_time2->setSpacing(6);
        hor_time2->setObjectName(QString::fromUtf8("hor_time2"));
        play_button2 = new QPushButton(ver_overviewWidget2);
        play_button2->setObjectName(QString::fromUtf8("play_button2"));

        hor_time2->addWidget(play_button2);

        speed_label2 = new QLabel(ver_overviewWidget2);
        speed_label2->setObjectName(QString::fromUtf8("speed_label2"));

        hor_time2->addWidget(speed_label2);

        speed_slider2 = new QSlider(ver_overviewWidget2);
        speed_slider2->setObjectName(QString::fromUtf8("speed_slider2"));
        speed_slider2->setMinimum(1);
        speed_slider2->setMaximum(1024);
        speed_slider2->setValue(1);
        speed_slider2->setOrientation(Qt::Horizontal);

        hor_time2->addWidget(speed_slider2);

        speed_xlabel2 = new QLabel(ver_overviewWidget2);
        speed_xlabel2->setObjectName(QString::fromUtf8("speed_xlabel2"));

        hor_time2->addWidget(speed_xlabel2);

        speed_value2 = new QLabel(ver_overviewWidget2);
        speed_value2->setObjectName(QString::fromUtf8("speed_value2"));

        hor_time2->addWidget(speed_value2);


        ver_overview2->addLayout(hor_time2);

        hor_health2 = new QHBoxLayout();
        hor_health2->setSpacing(6);
        hor_health2->setObjectName(QString::fromUtf8("hor_health2"));
        health_label2 = new QLabel(ver_overviewWidget2);
        health_label2->setObjectName(QString::fromUtf8("health_label2"));

        hor_health2->addWidget(health_label2);

        healthbar2 = new QProgressBar(ver_overviewWidget2);
        healthbar2->setObjectName(QString::fromUtf8("healthbar2"));
        healthbar2->setValue(100);
        healthbar2->setTextVisible(false);
        healthbar2->setInvertedAppearance(true);

        hor_health2->addWidget(healthbar2);


        ver_overview2->addLayout(hor_health2);

        hor_energy2 = new QHBoxLayout();
        hor_energy2->setSpacing(6);
        hor_energy2->setObjectName(QString::fromUtf8("hor_energy2"));
        energy_label2 = new QLabel(ver_overviewWidget2);
        energy_label2->setObjectName(QString::fromUtf8("energy_label2"));

        hor_energy2->addWidget(energy_label2);

        energybar2 = new QProgressBar(ver_overviewWidget2);
        energybar2->setObjectName(QString::fromUtf8("energybar2"));
        energybar2->setValue(100);
        energybar2->setTextVisible(false);
        energybar2->setInvertedAppearance(true);

        hor_energy2->addWidget(energybar2);


        ver_overview2->addLayout(hor_energy2);

        hor_enemies2 = new QHBoxLayout();
        hor_enemies2->setSpacing(6);
        hor_enemies2->setObjectName(QString::fromUtf8("hor_enemies2"));
        enemies_label2 = new QLabel(ver_overviewWidget2);
        enemies_label2->setObjectName(QString::fromUtf8("enemies_label2"));

        hor_enemies2->addWidget(enemies_label2);

        enemies_left2 = new QLabel(ver_overviewWidget2);
        enemies_left2->setObjectName(QString::fromUtf8("enemies_left2"));

        hor_enemies2->addWidget(enemies_left2);

        enemies_slash2 = new QLabel(ver_overviewWidget2);
        enemies_slash2->setObjectName(QString::fromUtf8("enemies_slash2"));

        hor_enemies2->addWidget(enemies_slash2);

        enemies_total2 = new QLabel(ver_overviewWidget2);
        enemies_total2->setObjectName(QString::fromUtf8("enemies_total2"));

        hor_enemies2->addWidget(enemies_total2);


        ver_overview2->addLayout(hor_enemies2);

        ver_pathfinding2 = new QVBoxLayout();
        ver_pathfinding2->setSpacing(6);
        ver_pathfinding2->setObjectName(QString::fromUtf8("ver_pathfinding2"));
        hor_pathfinding_ui1_2 = new QHBoxLayout();
        hor_pathfinding_ui1_2->setSpacing(6);
        hor_pathfinding_ui1_2->setObjectName(QString::fromUtf8("hor_pathfinding_ui1_2"));
        setstart_x2 = new QSpinBox(ver_overviewWidget2);
        setstart_x2->setObjectName(QString::fromUtf8("setstart_x2"));

        hor_pathfinding_ui1_2->addWidget(setstart_x2);

        setstart_y2 = new QSpinBox(ver_overviewWidget2);
        setstart_y2->setObjectName(QString::fromUtf8("setstart_y2"));

        hor_pathfinding_ui1_2->addWidget(setstart_y2);

        setstart_button2 = new QPushButton(ver_overviewWidget2);
        setstart_button2->setObjectName(QString::fromUtf8("setstart_button2"));

        hor_pathfinding_ui1_2->addWidget(setstart_button2);

        setdest_x2 = new QSpinBox(ver_overviewWidget2);
        setdest_x2->setObjectName(QString::fromUtf8("setdest_x2"));

        hor_pathfinding_ui1_2->addWidget(setdest_x2);

        setdest_y2 = new QSpinBox(ver_overviewWidget2);
        setdest_y2->setObjectName(QString::fromUtf8("setdest_y2"));

        hor_pathfinding_ui1_2->addWidget(setdest_y2);

        setdest_button2 = new QPushButton(ver_overviewWidget2);
        setdest_button2->setObjectName(QString::fromUtf8("setdest_button2"));

        hor_pathfinding_ui1_2->addWidget(setdest_button2);


        ver_pathfinding2->addLayout(hor_pathfinding_ui1_2);

        hor_pathfinding_ui2_2 = new QHBoxLayout();
        hor_pathfinding_ui2_2->setSpacing(6);
        hor_pathfinding_ui2_2->setObjectName(QString::fromUtf8("hor_pathfinding_ui2_2"));
        startbutton_2 = new QPushButton(ver_overviewWidget2);
        startbutton_2->setObjectName(QString::fromUtf8("startbutton_2"));

        hor_pathfinding_ui2_2->addWidget(startbutton_2);

        heurweight_label2 = new QLabel(ver_overviewWidget2);
        heurweight_label2->setObjectName(QString::fromUtf8("heurweight_label2"));

        hor_pathfinding_ui2_2->addWidget(heurweight_label2);

        heurweight_slider2 = new QSlider(ver_overviewWidget2);
        heurweight_slider2->setObjectName(QString::fromUtf8("heurweight_slider2"));
        heurweight_slider2->setMaximum(200000);
        heurweight_slider2->setOrientation(Qt::Horizontal);

        hor_pathfinding_ui2_2->addWidget(heurweight_slider2);

        heurweight_value2 = new QLabel(ver_overviewWidget2);
        heurweight_value2->setObjectName(QString::fromUtf8("heurweight_value2"));

        hor_pathfinding_ui2_2->addWidget(heurweight_value2);


        ver_pathfinding2->addLayout(hor_pathfinding_ui2_2);

        hor_pathfinding_ui3_2 = new QHBoxLayout();
        hor_pathfinding_ui3_2->setSpacing(6);
        hor_pathfinding_ui3_2->setObjectName(QString::fromUtf8("hor_pathfinding_ui3_2"));
        stepCost1_label2 = new QLabel(ver_overviewWidget2);
        stepCost1_label2->setObjectName(QString::fromUtf8("stepCost1_label2"));

        hor_pathfinding_ui3_2->addWidget(stepCost1_label2);

        stepCost1_value2 = new QDoubleSpinBox(ver_overviewWidget2);
        stepCost1_value2->setObjectName(QString::fromUtf8("stepCost1_value2"));
        stepCost1_value2->setDecimals(7);
        stepCost1_value2->setMaximum(10.000000000000000);
        stepCost1_value2->setSingleStep(0.000100000000000);

        hor_pathfinding_ui3_2->addWidget(stepCost1_value2);

        stepCost2_label2 = new QLabel(ver_overviewWidget2);
        stepCost2_label2->setObjectName(QString::fromUtf8("stepCost2_label2"));

        hor_pathfinding_ui3_2->addWidget(stepCost2_label2);

        stepCost2_value2 = new QDoubleSpinBox(ver_overviewWidget2);
        stepCost2_value2->setObjectName(QString::fromUtf8("stepCost2_value2"));
        stepCost2_value2->setDecimals(7);
        stepCost2_value2->setMaximum(10.000000000000000);
        stepCost2_value2->setSingleStep(0.000100000000000);

        hor_pathfinding_ui3_2->addWidget(stepCost2_value2);

        updateStepCost_button2 = new QPushButton(ver_overviewWidget2);
        updateStepCost_button2->setObjectName(QString::fromUtf8("updateStepCost_button2"));

        hor_pathfinding_ui3_2->addWidget(updateStepCost_button2);


        ver_pathfinding2->addLayout(hor_pathfinding_ui3_2);


        ver_overview2->addLayout(ver_pathfinding2);


        vert_rightside2->addWidget(ver_overviewWidget2);

        trackProta = new QRadioButton(tab2);
        trackProta->setObjectName(QString::fromUtf8("trackProta"));

        vert_rightside2->addWidget(trackProta);

        textoutput2 = new QTextBrowser(tab2);
        textoutput2->setObjectName(QString::fromUtf8("textoutput2"));
        textoutput2->setMinimumSize(QSize(500, 0));
        textoutput2->setMaximumSize(QSize(500, 16777215));

        vert_rightside2->addWidget(textoutput2);


        horizontalLayout_2->addLayout(vert_rightside2);


        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Papedipoepie", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        loadButton->setText(QApplication::translate("MainWindow", "Load", nullptr));
        openFile_button->setText(QApplication::translate("MainWindow", "Map img...", nullptr));
        img_label->setText(QApplication::translate("MainWindow", "maze1.png", nullptr));
        rotate_button_disabled->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
        play_button->setText(QApplication::translate("MainWindow", "AUTOPLAY", nullptr));
        speed_label->setText(QApplication::translate("MainWindow", "speed ", nullptr));
        speed_xlabel->setText(QApplication::translate("MainWindow", "x", nullptr));
        speed_value->setText(QApplication::translate("MainWindow", "0.5", nullptr));
        health_label->setText(QApplication::translate("MainWindow", "health   ", nullptr));
        energy_label->setText(QApplication::translate("MainWindow", "energy  ", nullptr));
        enemies_label->setText(QApplication::translate("MainWindow", "enemies ", nullptr));
        enemies_left->setText(QApplication::translate("MainWindow", "0", nullptr));
        enemies_slash->setText(QApplication::translate("MainWindow", " / ", nullptr));
        enemies_total->setText(QApplication::translate("MainWindow", "30", nullptr));
        setstart_button->setText(QApplication::translate("MainWindow", "SET START", nullptr));
        setdest_button->setText(QApplication::translate("MainWindow", "SET DEST", nullptr));
        start_button->setText(QApplication::translate("MainWindow", "SHOW PATH", nullptr));
        heurweight_label->setText(QApplication::translate("MainWindow", "heuristicweight", nullptr));
        heurweight_value->setText(QApplication::translate("MainWindow", "0", nullptr));
        stepCost1_label->setText(QApplication::translate("MainWindow", "stepcost1", nullptr));
        stepCost2_label->setText(QApplication::translate("MainWindow", "stepcost2", nullptr));
        updateStepCost_button->setText(QApplication::translate("MainWindow", "Update Stepcost", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "VIEW ONE", nullptr));
        saveButton2->setText(QApplication::translate("MainWindow", "Save", nullptr));
        loadButton2->setText(QApplication::translate("MainWindow", "Load", nullptr));
        openFile_button2->setText(QApplication::translate("MainWindow", "Map img...", nullptr));
        img_label2->setText(QApplication::translate("MainWindow", "maze1.png", nullptr));
        rotate_button->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
        play_button2->setText(QApplication::translate("MainWindow", "AUTOPLAY", nullptr));
        speed_label2->setText(QApplication::translate("MainWindow", "speed ", nullptr));
        speed_xlabel2->setText(QApplication::translate("MainWindow", "x", nullptr));
        speed_value2->setText(QApplication::translate("MainWindow", "0.5", nullptr));
        health_label2->setText(QApplication::translate("MainWindow", "health   ", nullptr));
        energy_label2->setText(QApplication::translate("MainWindow", "energy  ", nullptr));
        enemies_label2->setText(QApplication::translate("MainWindow", "enemies  ", nullptr));
        enemies_left2->setText(QApplication::translate("MainWindow", "0", nullptr));
        enemies_slash2->setText(QApplication::translate("MainWindow", " / ", nullptr));
        enemies_total2->setText(QApplication::translate("MainWindow", "30", nullptr));
        setstart_button2->setText(QApplication::translate("MainWindow", "SET START", nullptr));
        setdest_button2->setText(QApplication::translate("MainWindow", "SET DEST", nullptr));
        startbutton_2->setText(QApplication::translate("MainWindow", "SHOW PATH", nullptr));
        heurweight_label2->setText(QApplication::translate("MainWindow", "heuristicweight", nullptr));
        heurweight_value2->setText(QApplication::translate("MainWindow", "0", nullptr));
        stepCost1_label2->setText(QApplication::translate("MainWindow", "stepcost1", nullptr));
        stepCost2_label2->setText(QApplication::translate("MainWindow", "stepcost2", nullptr));
        updateStepCost_button2->setText(QApplication::translate("MainWindow", "Update Stepcost", nullptr));
        trackProta->setText(QApplication::translate("MainWindow", "Track Protagonist", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "ISOMETRIC VIEW", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
