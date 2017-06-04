
#include "about.h"  
#include <QLabel>  
#include <QGridLayout>  
  
about::about(QWidget *parent) : QDialog(parent)  
{  
    QLabel *aboutLabel=new QLabel;  
    aboutLabel->setText("简单QT音乐播放器");
    QHBoxLayout *mainLayout=new QHBoxLayout(this);  
    mainLayout->addWidget(aboutLabel,Qt::AlignCenter);  
  
  
}  
