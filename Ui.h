//
// Created by gnenux on 17-3-11.
//

#ifndef PLAYER_UI_H
#define PLAYER_UI_H

#include <QSpinBox>
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QSlider>
#include <QToolButton>
#include <QToolBar>
#include <QToolBox>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QImage>
#include <QAction>
#include <QVBoxLayout>
#include "volumebutton.h"
#include "positionSlider.h"
#include "ListViewItemDelegate.h"
#include "LyricView.h"
class Ui {
public:
    void setupUi(QWidget *parent);
public:

    QToolButton *closeBtn;

    QSlider *volum;
    QTableView *songList;
    QLabel *songImg;
    QLabel *nameLabel;
    QLabel *positionLabel;
    PositionSlider *horizontalSlider;

    QToolButton *preToolbtn;
    QToolButton *nextToolbtn;
    QToolButton *playToolBtn;

    QPushButton *importBtn;
    QPushButton *modeBtn;

    VolumeButton *volBtn;


    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *nextAction;
    QAction *pauseAction;
    QAction *backAction;

    QAction *showAction;
    QAction *importAction;
    QAction *aboutAction;
    QAction *quitAction;

    LyricView* lyricView;

    QVBoxLayout *leftLayout;
    QHBoxLayout *mainLayout;
};


#endif //PLAYER_UI_H
