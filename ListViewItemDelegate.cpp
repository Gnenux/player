//
// Created by gnenux on 17-5-9.
//

#include "ListViewItemDelegate.h"
#include <QPainter>


void ListViewItemDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{

    painter->setPen(Qt::black);
    painter->drawText(rect.x(),rect.y(),rect.width(),rect.height(),Qt::AlignCenter,text);
    //QItemDelegate::drawDisplay(painter,option,rect,text);
}
