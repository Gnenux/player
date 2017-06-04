//
// Created by gnenux on 17-5-15.
//

#include "LyricView.h"
#include "ListViewItemDelegate.h"
#include <QScrollBar>

LyricView::LyricView(QMediaPlayer *mediaPlayer,QWidget *parent) :QListView(parent),mPlayer(mediaPlayer){
   lyricInfo = new LyricInfo;
   lyricInfo->song_lines = new QList<LineInfo>;
    painter = new QPainter(viewport());
    mLineHeight = 14;
    mLineCount = 0;
    mLineSpace=10;
    mHighLightColor = Qt::green;
    mDefaultColor = Qt::lightGray;
    mCurrentShowColor=Qt::yellow;
    mShaderWidth=10;
    lrcModel = new QStandardItemModel;
    ListViewItemDelegate *lrcListDelegate =new ListViewItemDelegate;
    this->setItemDelegate(lrcListDelegate);
    this->setModel(lrcModel);
    this->setStyleSheet("background-color: rgba(232, 255, 213, 5);\n"
                                    "border:hidden;\n"
                                    "QListView::item{text-align:center;}"
                                    "horizontalHeader\n"
                                    "{\n"
                                    "background-color: rgba(232, 255, 213, 5)\n"
                                    "}");
    this->verticalScrollBar()->hide();
    this->setSpacing(10);
}

void LyricView::setupLyricResource(QString lyricFileName) {
    QFile file(lyricFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    if(lyricInfo){
        if(lyricInfo->song_lines)
            delete lyricInfo->song_lines;
        delete lyricInfo;
        lyricInfo->song_lines= Q_NULLPTR;
        lyricInfo= Q_NULLPTR;
    }
    lyricInfo = new LyricInfo;
    lyricInfo->song_lines = new QList<LineInfo>;
    QTextStream in(&file);
    in.setCodec("GB18030");
    while (!in.atEnd()) {
        QString line = in.readLine();
        analyzeLyric(line);
    }

    lrcModel->setHorizontalHeaderItem(0,new QStandardItem(lyricInfo->song_title));
    for(int i=0;i<lyricInfo->song_lines->size();++i) {
        lrcModel->setItem(i, 0, new QStandardItem(lyricInfo->song_lines->at(i).content));
    }
}

void LyricView::analyzeLyric(QString& line) {
    int index = line.lastIndexOf("]");
    if(line.size()!=0&&line.startsWith("[offset:")) {
        QString song_offset = QString(line.toStdString().substr(8, index).c_str());
        lyricInfo->song_offset = song_offset.toLong();
        return;
    }
    else if(line.size()!=0&line.startsWith("[ti:")){
        QString song_title = QString::fromStdString(line.toStdString().substr(4,index));
        lyricInfo->song_title = song_title;
        return;
    }
    else if(line.size()!=0&&line.startsWith("[ar:")){
        QString song_artist = QString::fromStdString(line.toStdString().substr(4,index));
        lyricInfo->song_artist = song_artist;
        return;
    }
    else if(line.size()!=0&&line.startsWith("[al:")){
        QString song_album = QString::fromStdString(line.toStdString().substr(4,index));
        lyricInfo->song_album = song_album;
        return;
    }
    else if(line.size()!=0&&line.startsWith("[by:")){
        return;
    }
    else if(line.size()!=0&&index==9&&line.length()>10){
        LineInfo lineInfo;
        lineInfo.content = QString::fromStdString(line.toStdString().substr(10,line.length()));
        lineInfo.start = measureStartTimeMillis(QString::fromStdString(line.toStdString().substr(0,10)));
        lyricInfo->song_lines->push_back(lineInfo);
    }
}

long LyricView::measureStartTimeMillis(QString time) {
    long  minute = QString::fromStdString(time.toStdString().substr(1,3)).toLong();
    long  second = QString::fromStdString(time.toStdString().substr(4,6)).toLong();
    long  millisecond = QString::fromStdString(time.toStdString().substr(7,9)).toLong();
    return millisecond+second*1000+minute*60*1000;
}

void LyricView::paintEvent(QPaintEvent *e) {
    QListView::paintEvent(e);
//    for(int i =0;i<lyricInfo->song_lines->size();i++){
//        LineInfo lineInfo = lyricInfo->song_lines->at(i);
//        if(lineInfo.content.size()!=0&&lineInfo.start>mPlayer->position()){
//            mCurrentPlayLine = i;
//            break;
//        }
//        if(i==lyricInfo->song_lines->size()-1){
//            mCurrentPlayLine = lyricInfo->song_lines->size();
//        }
//    }
//
//    for(int i=0,mLineCount = lyricInfo->song_lines->size();i<mLineCount;++i){
//        float x = this->size().width()*0.5f;
//        float y = this->size().height()*0.5f+(i+0.5f)*mLineHeight-6-mLineSpace*0.5f-mScrollY;
//
//        if(y+mLineHeight*0.5f<0){
//            continue;
//        }
//        else if(y-mLineHeight*0.5f>size().height()){
//            break;
//        }
//
//        if(i==mCurrentPlayLine-1){
//            painter->setPen(mHighLightColor);
//        }
//        else{
//            if(i==mCurrentPlayLine-1){
//                painter->setPen(mCurrentShowColor);
//            }
//            else{
//                painter->setPen(mDefaultColor);
//            }
//        }
//
//        if(y>size().height()-mShaderWidth||y<mShaderWidth){
//            if(y<mShaderWidth){
//                painter->setOpacity((26+(int)(23000.0f*y/mShaderWidth*0.01f))/255.0);
//            }
//            else{
//                painter->setOpacity((26+(int)(23000.0f*(size().height()-y)/mShaderWidth*0.01f))/255.0);
//            }
//        }
//        else{
//            painter->setOpacity(1.0);
//        }
//        painter->drawText(x,y,lyricInfo->song_lines->at(i).content);
//    }


}


void LyricView::measureLineHeight() {
    mLineHeight = 14;
}

float  LyricView::measureCurrentScrollY(int line_num) {
    return  (line_num-1)*mLineHeight;
}