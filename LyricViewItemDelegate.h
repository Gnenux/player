//
// Created by gnenux on 17-5-16.
//

#ifndef PLAYER_LYRICVIEWITEMDELEGATE_H
#define PLAYER_LYRICVIEWITEMDELEGATE_H

#include <QItemDelegate>
#include "LyricView.h"


class LyricViewItemDelegate: public QItemDelegate {
    Q_OBJECT
public:
    LyricViewItemDelegate(LyricView *lv);
protected:
    virtual void
    drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    LyricView *lyricView;
};


#endif //PLAYER_LYRICVIEWITEMDELEGATE_H
