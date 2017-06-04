#include <QApplication>
#include "player.h"
#include <iostream>
int main(int argc, char *argv[])
{  
    QApplication app(argc, argv);
    app.setOrganizationDomain(QObject::tr("qt-project.org"));
    player w;

    w.show();  
  
    return app.exec();
}  
