//
// Created by gnenux on 17-3-29.
//

#include "positionSlider.h"
#include <QPoint>
PositionSlider::PositionSlider(Qt::Orientation orientation,QWidget *parent):
        QSlider(orientation,parent) {

}

void PositionSlider::mousePressEvent(QMouseEvent *ev) {
    QSlider::mousePressEvent(ev);
    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());


}

void PositionSlider::mouseMoveEvent(QMouseEvent *ev) {
    QSlider::mouseMoveEvent(ev);

    double pos = ev->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());

}

