#include "parceclass.h"
#include <QFile>
#include <QDebug>
#include <QTextEncoder>

ParceClass::ParceClass(QObject *parent) : QThread ()
{
    RegDECDouble      = QRegExp("(-){0,1}\\d+[.,]{0,1}\\d*");
    RegHEX            = QRegExp("([0-9A-Fa-f]){2,2}");
    RegParams         = QRegExp("[A-Za-z]+[.\\sA-Za-z_()=-]+\\s*:{0,1}");
    RegParamsAndValue = QRegExp("[A-Za-z]+[.\\sA-Za-z_()=-]+\\s*:{0,1}\\s*(-){0,1}\\d+[.,]{0,1}\\d*");
    RegSET_PROPERTY   = QRegExp("[A-Z_0-9]+");
}

void ParceClass::run()
{
    QFile file(this->Patch);
    QString Text, text_buffer;
    Params s;
    uint numb_of_lines = 0, calibration_parameters = 1;

    QRegExp temp;
    if(file.exists())
    {
        qDebug() << "File exists";
        if (file.open(QIODevice::ReadOnly))
        {
            qDebug() << "File is open";
            Text.append(file.readLine());

            temp = QRegExp("(#BatchName Si4463){1,1}");
            if (temp.indexIn(Text,0) != -1)
            {
                qDebug() << "Batch-file for Si4463 identifie";
                while(!file.atEnd())
                {
                    emit PARCE_currentLine((int)(numb_of_lines/3));
                    numb_of_lines++;
                    Text.clear();
                    Text.append(file.readLine());
                    int pos = 0, pos_2 = 0;
                    pos = RegSET_PROPERTY.indexIn(Text,pos);
                    if (RegSET_PROPERTY.cap(0).compare("RESET") == 0)
                    {
                        qDebug() << "RESET";
                    }
                    else if (RegSET_PROPERTY.cap(0).compare("POWER_UP") == 0)
                    {

                        qDebug() << "POWER_UP";
                    }
                    else if (RegSET_PROPERTY.cap(0).compare("GPIO_PIN_CFG") == 0)
                    {
                        qDebug() << "GPIO_PIN_CFG";
                    }
                    else if (RegSET_PROPERTY.cap(0).compare("START_RX") == 0)
                    {
                        qDebug() << "START_RX";
                    }
                    else if (RegSET_PROPERTY.cap(0).compare("IRCAL") == 0)
                    {
                        qDebug() << "IRCAL";
                        calibration_parameters = 0;
                    }
                    else if (RegSET_PROPERTY.cap(0).compare("SET_PROPERTY") == 0)
                    {
                        QString PropertyName, PropertyValue;
                        pos+=RegSET_PROPERTY.matchedLength();
                        pos = RegSET_PROPERTY.indexIn(Text,pos);
                        PropertyName = RegSET_PROPERTY.cap(0);
                        pos+=RegSET_PROPERTY.matchedLength();
                        pos = RegSET_PROPERTY.indexIn(Text,pos);
                        PropertyValue = RegSET_PROPERTY.cap(0);

                        qDebug() << (PropertyName + " " + PropertyValue);

                        for(int i = 0; i < SI4463->SI4463_PROPERTYS_NAME.length(); i++)
                        {
                            if(PropertyName.compare(SI4463->SI4463_PROPERTYS_NAME.at(i))==0)
                            {
                                if (calibration_parameters == 1)
                                {
                                    bool b = false;
                                    uint nHex = PropertyValue.toUInt(&b,16);
                                    SI4463->aSI4463_SET_PROPERTYS(0, 0, i, nHex,SI4463->aSI4463_PROPERTYS_CALIB_FROM_FILE());
                                    break;
                                }
                                else if (calibration_parameters == 0)
                                {
                                    bool b = false;
                                    uint nHex = PropertyValue.toUInt(&b,16);
                                    SI4463->aSI4463_SET_PROPERTYS(0, 0, i, nHex,SI4463->aSI4463_PROPERTYS_FROM_FILE());
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {

                        while((pos = RegParamsAndValue.indexIn(Text,pos)) != -1)
                        {
                            text_buffer = RegParamsAndValue.cap(0);

                            qDebug() << text_buffer;

                            pos+=RegParamsAndValue.matchedLength();

                            pos_2 = 0;
                            pos_2 = RegParams.indexIn(text_buffer,pos_2);
                            s.name = RegParams.cap(0);
                            pos_2 = RegDECDouble.indexIn(text_buffer,pos_2);
                            s.value = RegDECDouble.cap(0);
                            SI4463->Parameters.append(s);
                        }
                    }
                }
                emit PARCE_currentLine(100);
            }
            else
            {

            }
        }
        else
        {
            qDebug() << "File open error";
        }
    }
    emit PARCE_End();
}

void ParceClass::PARCE_Start(QString Patch, SI4463Class *SI4463)
{
    this->Patch  = Patch;
    this->SI4463 = SI4463;
    this->start();
}
