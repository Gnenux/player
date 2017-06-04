//
// Created by gnenux on 17-5-16.
//

#include "LyricViewItemDelegate.h"
#include <QPainter>

LyricViewItemDelegate::LyricViewItemDelegate(LyricView *lv) :QItemDelegate(0){
    lyricView = lv;
}

void LyricViewItemDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect,
                                        const QString &text) const
{
    painter->setPen(Qt::black);


    for(int i =0;i<lyricView->lyricInfo->song_lines->size();i++){
        LineInfo lineInfo = lyricView->lyricInfo->song_lines->at(i);
        if(lineInfo.content.size()!=0&&lineInfo.start>lyricView->mPlayer->position()){
            lyricView->mCurrentPlayLine = i;
            break;
        }
        if(i==lyricView->lyricInfo->song_lines->size()-1){
            lyricView->mCurrentPlayLine = lyricView->lyricInfo->song_lines->size();
        }
    }

    for(int i=0,mLineCount = lyricView->lyricInfo->song_lines->size();i<mLineCount;++i){
        float x = lyricView->size().width()*0.5f;
        float y = lyricView->size().height()*0.5f+(i+0.5f)*lyricView->mLineHeight-6-lyricView->mLineSpace*0.5f-lyricView->mScrollY;

        if(y+lyricView->mLineHeight*0.5f<0){
            continue;
        }
        else if(y-lyricView->mLineHeight*0.5f>lyricView->size().height()){
            break;
        }

        if(i==lyricView->mCurrentPlayLine-1){
            painter->setPen(lyricView->mHighLightColor);
        }
        else{
            if(i==lyricView->mCurrentPlayLine-1){
                painter->setPen(lyricView->mCurrentShowColor);
            }
            else{
                painter->setPen(lyricView->mDefaultColor);
            }
        }

        if(y>lyricView->size().height()-lyricView->mShaderWidth||y<lyricView->mShaderWidth){
            if(y<lyricView->mShaderWidth){
                painter->setOpacity((26+(int)(23000.0f*y/lyricView->mShaderWidth*0.01f))/255.0);
            }
            else{
                painter->setOpacity((26+(int)(23000.0f*(lyricView->size().height()-y)/lyricView->mShaderWidth*0.01f))/255.0);
            }
        }
        else{
            painter->setOpacity(1.0);
        }
        QFont font(painter->font());
        font.setPointSize(14);
        font.setWeight(14);
        painter->setFont(font);
        painter->drawText(0.0f,y,rect.width(),rect.height(),Qt::AlignCenter,text);
    }

}

