#include "mainwindow.h"
#include "connections_form.h"
#include "STYLE/style.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName( "АО ПКК Миландр" );
    QApplication::setOrganizationDomain( "___________" );
    QApplication::setApplicationName( "QModBus" );

    QApplication a(argc, argv);
    //MainWindow w;
    Connections_Form v;
    //w.setStyleSheet(Style::Widget2_StyleSheet);
    //w.show();
    v.show();
    
    return a.exec();
}
