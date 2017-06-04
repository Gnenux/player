//
// Created by gnenux on 17-3-29.
//

#ifndef PLAYER_VOLUMEBUTTON_H
#define PLAYER_VOLUMEBUTTON_H

#include <QToolButton>

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QLabel)
class VolumeButton : public QToolButton
{
Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    VolumeButton(QWidget *parent = 0);

    int volume() const;

public slots:
    void increaseVolume();
    void descreaseVolume();
    void setVolume(int volume);
    void stylize();

signals:
    void volumeChanged(int volume);

private:
    QMenu *menu;
    QSlider *slider;
    QLabel *label;
};


#endif //PLAYER_VOLUMEBUTTON_H
