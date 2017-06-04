#ifndef PLAYER_H
#define PLAYER_H
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>  
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>  
#include <QSystemTrayIcon>  
#include <QEvent>  
#include <QMenu>  
#include <QAction>  
#include "about.h"
#include <QStandardItemModel>  
#include <QTableView>  
#include <QDirModel>  
#include <QDir>  
#include <QStringListIterator>  
#include <QtMultimedia/QMediaPlaylist>
#include <QTimer>  
#include "Ui.h"

class player : public QWidget  
{  
    Q_OBJECT  
  
public:  
    explicit player(QWidget *parent = 0);  
    ~player();  
    QPoint drag;//定义一个释放点  
    void mousePressEvent(QMouseEvent *);//窗口移动事件  
    void mouseMoveEvent(QMouseEvent *);//窗口移动事件  
    QMediaPlayer *myPlayer;
protected:  
    QAction *quitAction;  
    QAction *aboutAction;  
    QAction *nextAction;  
    QAction *pauseAction;  
    QAction *backAction;
    QStandardItemModel *songListModel;
    QStandardItemModel *LrcModel;
    QStringList path;  
    QMediaPlaylist *playList;  
//    QTimer *timer;
    qint64 pausePosition;  
    int currentIndex;  

  
private slots:  
    void on_closeBtn_clicked();                                 //隐藏主面板
    void on_showAct_triggered();                                //显示主面板
    void on_miniBtn_clicked();                                  //最小化主面板
    void on_pushButton_2_clicked();
    void on_pauseBtn_clicked();                                 //暂停
    void on_volum_valueChanged(int value);                      //调整音量
    void tuopan(QSystemTrayIcon::ActivationReason reason);      //托盘
    void showAbout();                                           //说明
    void myPlayerSlot(QModelIndex index);                       //
    void on_importBtn_clicked();  
    //void setPosition();
    void on_horizontalSlider_valueChanged(int value);           //
    void on_nextBtn_clicked();                                  //下一首
    void on_backBtn_clicked();                                  //上一首

    void change_play_model();                                   //改变播放模式

    void on_quitAct_triggered();                                //退出

    void mediaChange(int);
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
private:
    Ui *ui;
    int play_back_mode;
};  
  
#endif // PLAYER_H  
