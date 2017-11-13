#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName( "АО ПКК Миландр" );
    QApplication::setOrganizationDomain( "___________" );
    QApplication::setApplicationName( "QModBus" );


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
