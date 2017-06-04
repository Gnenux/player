//
// Created by gnenux on 17-5-15.
//

#ifndef PLAYER_LYRICVIEW_H
#define PLAYER_LYRICVIEW_H

#include <QListView>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QStandardItemModel>

struct LineInfo {
    QString content;//歌词内容
    long start;//开始时间
};

struct LyricInfo {
    QList<LineInfo>* song_lines;
    QString song_artist;//歌手
    QString song_title;//标题
    QString song_album;//专辑
    long song_offset;//偏移量
};


class LyricView :public QListView{
    Q_OBJECT
public:
    explicit LyricView(QMediaPlayer *mediaPlayer= 0,QWidget *parent = 0);

    void setupLyricResource(QString lyricFileName);

    ~LyricView(){delete lyricInfo->song_lines;delete lyricInfo;}
private:
protected:
    virtual void paintEvent(QPaintEvent *e);

public:
    QMediaPlayer *mPlayer;

    LyricInfo *lyricInfo;
    QPainter *painter;
    int mLineHeight;
    int mLineCount;
    int mLineSpace;
    int mCurrentPlayLine;
    float mScrollY;

    QColor mHighLightColor;
    QColor mCurrentShowColor;
    QColor mDefaultColor;

    int mShaderWidth;

    QStandardItemModel *lrcModel;

    void analyzeLyric(QString& line);
    long measureStartTimeMillis(QString time);
    void measureLineHeight();
    float measureCurrentScrollY(int line_num);
};


#endif //PLAYER_LYRICVIEW_H
