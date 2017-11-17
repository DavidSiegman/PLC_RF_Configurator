#ifndef PARCECLASS_H
#define PARCECLASS_H

#include <QObject>
#include <QThread>
#include "SI4463/si4463class.h"

class ParceClass : public QThread
{
    Q_OBJECT
public:
    explicit ParceClass( QObject *parent = 0);
    void run();
private:
    QString Patch;
    SI4463Class *SI4463;
    QRegExp RegDECDouble, RegHEX, RegParams, RegParamsAndValue,RegSET_PROPERTY;
signals:
    void PARCE_currentLine(int Line);
    void PARCE_End();
public slots:
    void PARCE_Start(QString Patch, SI4463Class *SI4463);
};

#endif // PARCECLASS_H
