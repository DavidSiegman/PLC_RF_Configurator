#ifndef DATALOGIC_CLASS_H
#define DATALOGIC_CLASS_H

#include <QObject>
#include <QTimer>
#include <qdebug.h>
#include "COM/port.h"
#include "CRC/crc16_class.h"
#include "SI4463/si4463class.h"
#include "MODEM/modemclass.h"
#include <mess_enum.h>

class DataLogic_Class : public QObject
{
    Q_OBJECT
public:
    explicit DataLogic_Class(CRC16_Class *oCRC16, QTimer *t, SI4463Class *SI4463Conf,MODEMClass *MODEM,Port *nPort,QObject *parent = 0);

    uint         DataLogicMode;
    uint         Repeat_Number;
    uint         Repeat_Counter;
    uint         Delay_Time;

    void setSerialNumberMode(QString S, bool Enable);
private:
    QTimer      *timer, *timerRepeat;
    CRC16_Class *CRC16;
    SI4463Class *SI4463Conf;
    MODEMClass  *MODEM;
    Port        *nPort;

    QByteArray  InDataBuffer;
    QByteArray  OutDataBuffer;
    QByteArray  ParceDataBuffer;
    QByteArray  repeat_data;

    QString     SerialNumber;
    bool        addSerialNumber;


signals:
    void writeDataToCOM(QByteArray data);
    void writeDataToTCP(QByteArray data);
    void DataForPrint(QByteArray data,uint n);
    void outConnect(uint n);
    void outCurrentRSSI(signed short RSSI);
    void outLRSSI_AFC(signed short RSSI, signed int AFC);
    void noANSWER();

public slots:
    void SEND_DATA(QByteArray data, uint n);
    void REPEAT_SEND();
    void In_DataBuffer(QByteArray data);
    void Parce_DataBuffer(QByteArray data, uint n);
    void ParceData(uint n);
    void ClearIn_DataBuffer(void);
    void ClearOut_DataBuffer(void);
    void ComandHandling(uint n, uint m);
};

#endif // DATALOGIC_CLASS_H
