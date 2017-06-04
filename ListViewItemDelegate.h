//
// Created by gnenux on 17-5-9.
//

#ifndef PLAYER_LISTVIEWITEMDELEGATE_H
#define PLAYER_LISTVIEWITEMDELEGATE_H

#include <QItemDelegate>

class ListViewItemDelegate :public QItemDelegate{
    Q_OBJECT
public:
    virtual void
    drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

public:
    ListViewItemDelegate(){}

private:
};


#endif //PLAYER_LISTVIEWITEMDELEGATE_H
