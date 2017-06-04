//
// Created by gnenux on 17-3-29.
//

#include "volumebutton.h"

#include <QtWidgets>

VolumeButton::VolumeButton(QWidget *parent) :
        QToolButton(parent), menu(0), slider(0)
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Vertical, popup);
    slider->setRange(0, 100);
    slider->setValue(50);
    connect(slider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);


    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(50);
    label->setMinimumWidth(label->sizeHint().width());

    typedef void(QLabel::*IntSlot)(int);
    connect(slider, &QAbstractSlider::valueChanged, label, static_cast<IntSlot>(&QLabel::setNum));

    QBoxLayout *popupLayout = new QVBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(label);
    popupLayout->addWidget(slider);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}

void VolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int VolumeButton::volume() const
{
    return slider->value();
}

void VolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

//! [0]
void VolumeButton::stylize()
{

//    QString css("QMenu { border: 1px solid black; border-radius: 2px; background: transparent; }");
//    menu->setStyleSheet(css);

//    if (true) {

//        QString css("QMenu { border: 1px solid black; border-radius: 2px; background: transparent; }");
//        menu->setStyleSheet(css);
//    } else {

//        QString css("QMenu { border: 1px solid red; background: %1; }");
//        menu->setStyleSheet(css);
//   }
}
//! [0]
