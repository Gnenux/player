#include "player.h"
#include <QDebug>
#include <QList>  
#include <QHeaderView>
#include <QTime>
#include <QToolButton>
#include <iostream>
#include "LyricViewItemDelegate.h"
player::player(QWidget *parent) :  
    QWidget(parent),  
    ui(new Ui),
    play_back_mode(0)
{  
    ui->setupUi(this);
    myPlayer=new QMediaPlayer(this);
    ui->lyricView = new LyricView(myPlayer);

    LyricViewItemDelegate *lyricViewItemDelegate = new LyricViewItemDelegate(ui->lyricView);
    ui->lyricView->setItemDelegate(lyricViewItemDelegate);
    //connect(myPlayer,SIGNAL(positionChanged()),ui->lyricView,SLOT(update()));
    ui->mainLayout->addWidget(ui->lyricView);
    ui->mainLayout->addLayout(ui->leftLayout);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|Qt::Window);//隐藏标题栏
    this->setFixedSize(840,640);
    this->setWindowIcon(QIcon(":/new/prefix1/image/tray.jpg"));

    connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));



    ui->volum->setValue(50);
    myPlayer->setVolume(ui->volum->value());

    playList=new QMediaPlaylist;
    connect(ui->trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
            SLOT(tuopan(QSystemTrayIcon::ActivationReason)));//将托盘图标和双击事件关联  

    QPalette palette = this->palette();  
    palette.setBrush(backgroundRole(), QBrush(QPixmap("./saber.jpg")));
    //setPalette(palette);


    connect(playList,SIGNAL(currentIndexChanged(int)),this,SLOT(mediaChange(int)));  


    //歌曲列表  
    songListModel=new QStandardItemModel;  
    songListModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("歌曲列表")));     
    ui->songList->setModel(songListModel);  
    ui->songList->setColumnWidth(0,390);      
    ui->songList->verticalHeader()->hide();
    ui->songList->setEditTriggers(QAbstractItemView::NoEditTriggers);  
    ui->songList->setSelectionBehavior(QAbstractItemView::SelectRows);  
    connect(ui->songList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(myPlayerSlot(QModelIndex)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setPosition(int)));
//    connect(ui->horizontalSlider,SIGNAL(actionTriggered(int)),this,SLOT(setPosition(int)));

    LrcModel = new QStandardItemModel;


    connect(ui->preToolbtn,SIGNAL(clicked()),this,SLOT(on_backBtn_clicked()));
    connect(ui->backAction,SIGNAL(triggered()),this,SLOT(on_backBtn_clicked()));
    connect(ui->nextToolbtn,SIGNAL(clicked()),this,SLOT(on_nextBtn_clicked()));
    connect(ui->nextAction,SIGNAL(triggered()),this,SLOT(on_nextBtn_clicked()));
    connect(ui->playToolBtn,SIGNAL(clicked()),this,SLOT(on_pauseBtn_clicked()));
    connect(ui->pauseAction,SIGNAL(triggered()),this,SLOT(on_pauseBtn_clicked()));

    connect(ui->showAction,SIGNAL(triggered()),this,SLOT(show()));
    connect(ui->importAction,SIGNAL(triggered()),this,SLOT(on_importBtn_clicked()));
    connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->quitAction,SIGNAL(triggered()),this,SLOT(on_quitAct_triggered()));
    connect(ui->importBtn,SIGNAL(clicked()),this,SLOT(on_importBtn_clicked()));


    connect(myPlayer, &QMediaPlayer::positionChanged, this, &player::updatePosition);
    connect(myPlayer, &QMediaPlayer::durationChanged, this, &player::updateDuration);
    connect(myPlayer, &QMediaObject::metaDataAvailableChanged, this, &player::updateInfo);

    myPlayer->setMedia(QUrl::fromLocalFile(tr("/home/gnenux/音乐/CloudMusic/兔裹煎蛋卷 - 的.mp3")));
    ui->lyricView->setupLyricResource("huanghun.lrc");
    std::cout<<ui->lyricView->lyricInfo->song_lines->size()<<std::endl;
    for(int i=0;i<ui->lyricView->lyricInfo->song_lines->size();++i){
        std::cout<<ui->lyricView->lyricInfo->song_lines->at(i).content.toStdString()<<std::endl;
    }
    myPlayer->play();
}  
  
player::~player()  
{  
    delete ui;  
}  
  
void player::on_closeBtn_clicked()//单击关闭按钮，产生托盘和托盘菜单
{
    this->hide();
}

void player::on_showAct_triggered() {
    this->showNormal();
}

void player::on_miniBtn_clicked()  
{  
    this->showMinimized();  
}  
void player::mousePressEvent(QMouseEvent *e)  
{  
    if(e->button()==Qt::LeftButton)//button()是按钮  
    {  
        drag=e->globalPos()-this->geometry().topLeft();//鼠标位置减去左上角的左边  
        e->accept();  
    }  
}  
void player::mouseMoveEvent(QMouseEvent *e)  
{  
    if(e->buttons()&Qt::LeftButton)//buttons()返回的是按钮状态  
    {  
        move(e->globalPos()-drag);  
        e->accept();  
    }  
}  
//选择歌曲  
void player::on_pushButton_2_clicked()  
{  
    QString path=QFileDialog::getOpenFileName(this,tr("选择一首歌曲"),"/","*.mp3");  
    QFileInfo fileInfo;  
    fileInfo=QFileInfo(path);  
    QString fileName=fileInfo.baseName();  
    ui->nameLabel->setText(fileName);  
    myPlayer->setMedia(QUrl::fromLocalFile(path));  
    myPlayer->play();  
  
}  
  
//暂停按钮  
void player::on_pauseBtn_clicked()  
{  
    switch (myPlayer->state()) {  
    case QMediaPlayer::PlayingState:  

        currentIndex=playList->currentIndex();  
        pausePosition=myPlayer->position();  
        myPlayer->pause();  
        break;  
    case QMediaPlayer::PausedState:  
        myPlayer->setMedia(playList->media(currentIndex));  
        myPlayer->setPosition(pausePosition);  
        //timer->start(1000);
        myPlayer->play();  
        break;  
    default:  
        break;  
    }  
  
}  
//音量调节  
void player::on_volum_valueChanged(int value)  
{  
    myPlayer->setVolume(value);  
}  
void player::tuopan(QSystemTrayIcon::ActivationReason reason)//双击托盘图标，恢复程序正常界面  
{  
    switch (reason)  
    {  
    case QSystemTrayIcon::DoubleClick:  
        this->showNormal();  
        break;  
    default:  
        break;  
    }  
}  
//显示关于本程序对话框  
void player::showAbout()  
{  
    about showabout;  
    showabout.setModal(false);  
    showabout.setWindowTitle("关于本程序");  
    showabout.exec();  
}  
  
//导入多首歌曲  
void player::on_importBtn_clicked()  
{  
    path=QFileDialog::getOpenFileNames(this,"选择歌曲","/","(*.mp3)");  
    int i=0;  
    QString addSongs;  
    QListIterator<QString> mylist(path);  
    while(mylist.hasNext())  
    {  
        addSongs=mylist.next();  
        QFileInfo fileInfo;  
        fileInfo=QFileInfo(addSongs);  
        QString fileName=fileInfo.fileName();  
        songListModel->setItem(i,0,new QStandardItem(fileName));  
        playList->addMedia(QUrl::fromLocalFile(addSongs));  
        i++;  
    }  
  
    playList->setPlaybackMode(QMediaPlaylist::Loop);  
    myPlayer->setPlaylist(playList);  
  
}  
//双击播放  
void player::myPlayerSlot(QModelIndex index)  
{  

    int n=index.row();  
    playList->setCurrentIndex(n);
    myPlayer->play();  
}
void player::on_horizontalSlider_valueChanged(int value)//快进和快退功能  
{  
    qint64 currentPosition=myPlayer->position();  
    if(qAbs(value-currentPosition)>2000&&(ui->horizontalSlider->value()!=0))  
    {  
        myPlayer->stop();
        myPlayer->setPosition(value);
        myPlayer->play();  
    }  
}  
  
void player::on_nextBtn_clicked()//播放下一首  
{  
    if(playList->mediaCount()-playList->currentIndex()!=1)//这里注意的是，和我们正常数数一样，mediaCount是从1开始计数的  
    {
        playList->setCurrentIndex(playList->nextIndex());  
        myPlayer->play();  
    }  
    else  
    {  
        playList->setCurrentIndex(0);
        myPlayer->play();  
    }  
}  
  
void player::on_backBtn_clicked()//播放上一首  
{  
    if(playList->currentIndex()!=0)//这里注意的是，和我们正常数数一样，mediaCount是从1开始计数的  
    {
        playList->setCurrentIndex(playList->previousIndex());  
        myPlayer->play();  
    }  
    else  
    {  
        playList->setCurrentIndex(playList->mediaCount()-1);
        myPlayer->play();  
    }  
  
}


void player::change_play_model() {
    if(play_back_mode==3){
        play_back_mode = -1;
    }
    play_back_mode++;
    switch(play_back_mode){
        case 0:
            playList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            //ui
            break;
        case 1:
            playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            //ui
            break;
        case 2:
            playList->setPlaybackMode(QMediaPlaylist::Loop);
            //ui
            break;
        case 3:
            playList->setPlaybackMode(QMediaPlaylist::Random);
            //ui
            break;
        default:
            playList->setPlaybackMode(QMediaPlaylist::Loop);
            play_back_mode =2;
            //ui
            break;
    }


}

void player::on_quitAct_triggered() {
    this->close();
}

void player::mediaChange(int i)  
{  
    ui->nameLabel->setText(path.at(i));  
}



void player::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        ui->playToolBtn->setToolTip(tr("Pause"));
        ui->playToolBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        ui->playToolBtn->setToolTip(tr("Play"));
        ui->playToolBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void player::updatePosition(qint64 position)
{
    ui->horizontalSlider->setValue(position);


    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    ui->positionLabel->setText(duration.toString(tr("mm:ss")));
}

void player::updateDuration(qint64 duration)
{
    ui->horizontalSlider->setRange(0, duration);
    ui->horizontalSlider->setEnabled(duration > 0);
    ui->horizontalSlider->setPageStep(duration / 10);
}

void player::setPosition(int position)
{
    
   if (qAbs(myPlayer->position() - position) > 99)
        myPlayer->setPosition(position);
}

void player::updateInfo()
{
    QStringList info;
    QStringList AvailableMetaData = myPlayer->availableMetaData();
    std::cout<<AvailableMetaData.join("::").toStdString()<<std::endl;
    QImage img = myPlayer->metaData("AttachedPicture").value<QImage>();
    //QImage img("./saber.jpg");
    QPixmap pixmap = QPixmap::fromImage(img);

    ui->songImg->setPixmap(QPixmap::fromImage(img));
    ui->songImg->setFixedSize(60,60);
    QString author = myPlayer->metaData("ContributingArtist").toString();
    if (!author.isEmpty())
        info += author;
    QString title = myPlayer->metaData("Title").toString();
    if (!title.isEmpty())
        info += title;
    if (!info.isEmpty())
        ui->nameLabel->setText(info.join(tr(" - ")));
}
