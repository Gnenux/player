//
// Created by gnenux on 17-3-11.
//
#include <QGridLayout>
#include <QStyle>
#include <QObject>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QAction>
#include "Ui.h"
#include <QHeaderView>
#include <QFile>

void Ui::setupUi(QWidget *parent) {
    QHBoxLayout *topLayout = new QHBoxLayout();
    QGridLayout *centerLayout = new QGridLayout();
    leftLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout(parent);
    QHBoxLayout *sliderLayout = new QHBoxLayout();



    closeBtn = new QToolButton(parent);
    //closeBtn->setText(QString("X"));
    closeBtn->resize(closeBtn->size().width(),closeBtn->size().width());
    closeBtn->setIcon(QIcon(""));
    topLayout->addSpacing(420);
    topLayout->addWidget(closeBtn);


    volum = new QSlider(Qt::Vertical);
    volum->setRange(0,100);



    songList = new QTableView;
    songList->setStyleSheet("background-color: rgba(232, 255, 213, 5);\n"
                                    "border:hidden;\n"
                                    "QListView::item{text-align:center;}"
                                    "horizontalHeader\n"
                                    "{\n"
                                    "background-color: rgba(232, 255, 213, 5)\n"
                                    "}");

    songList->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    songList->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    songList->setShowGrid(false);


    ListViewItemDelegate *songListDelegate =new ListViewItemDelegate;
    songList->setItemDelegate(songListDelegate);

    nameLabel = new QLabel;

    songImg = new QLabel;
    songImg->setScaledContents(true);
    //songImg->setStyle()
    positionLabel = new QLabel(QObject::tr("00:00"));
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());
    horizontalSlider = new PositionSlider(Qt::Horizontal);
    //horizontalSlider->setPageStep(1);
    QFile file("horizontalSlider.css");
    file.open(QIODevice::ReadOnly);
    horizontalSlider->setStyleSheet(file.readAll().toStdString().c_str());

    volBtn = new VolumeButton(parent);

    sliderLayout->addWidget(horizontalSlider);
    sliderLayout->addWidget(positionLabel);
    sliderLayout->addWidget(volBtn);


    preToolbtn = new QToolButton;
    preToolbtn->setIcon(preToolbtn->style()->standardIcon(QStyle::SP_MediaSeekBackward));
    nextToolbtn = new QToolButton;
    nextToolbtn->setIcon(nextToolbtn->style()->standardIcon(QStyle::SP_MediaSeekForward));
    playToolBtn = new QToolButton;
    playToolBtn->setIcon(playToolBtn->style()->standardIcon(QStyle::SP_MediaPlay));

    QToolBar *toolBar = new QToolBar;

    toolBar->addWidget(preToolbtn);
    toolBar->addWidget(playToolBtn);
    toolBar->addWidget(nextToolbtn);



   importBtn = new QPushButton(QObject::tr("导入"));
    QFile importBtnQss("importBtn.Qss");
    importBtnQss.open(QIODevice::ReadOnly);
   importBtn->setStyleSheet(importBtnQss.readAll().toStdString().c_str());
    modeBtn = new QPushButton(QObject::tr(""));
    modeBtn->setIcon(QIcon(QPixmap("")));//mode image

    centerLayout->addWidget(songImg,0,0);
    centerLayout->addWidget(nameLabel,0,1);
    centerLayout->addWidget(toolBar,0,2);

    centerLayout->addLayout(sliderLayout,1,0,1,3);
    //centerLayout->addWidget(toolBar,1,1);
//    centerLayout->addWidget(horizontalSlider,1,0);
//    centerLayout->addWidget(positionLabel,1,1);
//    centerLayout->addWidget(volBtn,1,2);
    centerLayout->addWidget(songList,2,0,1,3);
    //centerLayout->addWidget(importBtn,3,0);
    //centerLayout->addWidget(modeBtn,3,1);

    trayIcon=new QSystemTrayIcon(parent);
    //trayIcon->setIcon(QIcon("saber.jpg"));


    QMenu *trayMenu=new QMenu();
    backAction = new QAction(parent);
    backAction->setText(QObject::tr("上一首"));
    pauseAction = new QAction(parent);
    pauseAction->setText(QObject::tr("播放/暂停"));
    nextAction = new QAction(parent);
    nextAction->setText(QObject::tr("下一首"));

    showAction = new QAction(QObject::tr("显示主面板"),parent);
    importAction = new QAction(QObject::tr("导入歌曲"),parent);
    aboutAction=new QAction(QObject::tr("关于"),parent);
    quitAction=new QAction(QObject::tr("退出"),parent);


    trayMenu->addAction(backAction);
    trayMenu->addAction(pauseAction);
    trayMenu->addAction(nextAction);
    trayMenu->addSeparator();
    trayMenu->addAction(showAction);
    trayMenu->addAction(importAction);
    trayMenu->addAction(aboutAction);
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    trayIcon->setToolTip("Player");
    //trayIcon->showMessage("I'm a MusicPlayer!",QSystemTrayIcon::Information,5000);

    leftLayout->addLayout(topLayout);
    leftLayout->addLayout(centerLayout);


}
