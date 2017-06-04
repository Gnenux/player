//
// Created by gnenux on 17-3-29.
//

#ifndef PLAYER_POSITIONSLIDER_H
#define PLAYER_POSITIONSLIDER_H

#include <QWidget>
#include <QSlider>
#include <QMouseEvent>


class PositionSlider : public QSlider
{
Q_OBJECT
public:
    PositionSlider(Qt::Orientation orientation,QWidget* parent = 0);
private:
protected:
    virtual void mousePressEvent(QMouseEvent *ev);

    virtual void mouseMoveEvent(QMouseEvent *ev);

};


#endif //PLAYER_POSITIONSLIDER_H
