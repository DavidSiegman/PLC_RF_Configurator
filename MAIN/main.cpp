#include "WINDOWS_FORMS/mainwindow.h"
#include "ANDROID_FORMS/connections_form.h"
#include "STYLE/style.h"
#include <QString>

#include <QApplication>
#include <qdebug.h>

//QString BUILDING_VERSION;
//QString BUILDING_CRC;
//QString BUILDING_TIME;

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QApplication a(argc, argv);

    //MainWindow w;
    Connections_Form v;
    //w.setStyleSheet(Style::Widget2_StyleSheet);
    //w.show();
    v.show();
    
    return a.exec();
}
/*
void TextInfoReading(void){

    QFile file(":/StringFileInfo/Info/texts/appinfo.txt");
    QString Text, text_buffer;
    QRegExp temp;

    if(file.exists())
    {
        qDebug() << "File exists";
        if (file.open(QIODevice::ReadOnly)){
            qDebug() << "File is open";
            // считываем информацию по строчно
            while(!file.atEnd()){
               Text.clear();
               Text.append(file.readLine());

               if(Text.contains("BUILDING_VERSION "))
               {
                   Text.replace("BUILDING_VERSION ","");
                   BUILDING_VERSION.clear();
                   BUILDING_VERSION.append(Text);
               }
               else if (Text.contains("BUILDING_CRC ")){
                   Text.replace("BUILDING_CRC ","");
                   BUILDING_CRC.clear();
                   BUILDING_CRC.append(Text);
               }
               else if (Text.contains("BUILDING_TIME ")){
                   Text.replace("BUILDING_TIME ","");
                   BUILDING_TIME.clear();
                   BUILDING_TIME.append(Text);
               }
            }
        }
        else{
            qDebug() << "File open error";
            BUILDING_VERSION.clear();
            BUILDING_VERSION.append("Unknown");
            BUILDING_CRC.clear();
            BUILDING_CRC.append("Unknown");
            BUILDING_TIME.clear();
            BUILDING_TIME.append("Unknown");
        }
    }
}

QString Get_BUILDING_VERSION(void){
    return BUILDING_VERSION;
}
QString Get_BUILDING_CRC(void){
    return BUILDING_CRC;
}
QString Get_BUILDING_TIME(void){
    return BUILDING_TIME;
}
*/
