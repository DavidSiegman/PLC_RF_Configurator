#ifndef DATALOGIC_CLASS_H
#define DATALOGIC_CLASS_H

#include <QObject>
#include <QTimer>
#include <qdebug.h>
#include "COM/port.h"
#include "TCP/tcp.h"
#include "CRC/crc16_class.h"
#include "SI4463/si4463class.h"
#include "SI4432/si4432class.h"
#include "MODEM/modemclass.h"
#include <mess_enum.h>

typedef union RF_Message_type {
    struct {
        uchar  Msg_Length;                     //1
        uchar  Unused_Char_0;                  //2
        ushort broadcasting;                   //3-4
        ushort Msg_Uniq_Number;                //5-6
        uchar  Retranslator_Level;             //7
        uchar  Finish_Retranslator_Level;      //8
        uint   Last_Retranslator_Net_Address;  //9-10-11-12
        signed short in_RSSI;                      //13-14
        signed short Finish_RSSI;                   //15-16
        uint   Source_Net_Address;             //17-18-19-20
        uint   Destination_Net_Address;        //21-22-23-24
        uchar  RX_Buffer_current_counter;      //25
        uchar  TX_Buffer_counter;              //26
        unsigned char Unused_Field_1: 5;
        unsigned char Unused_Field_2: 3;
        unsigned char Unused_Field_3: 1;
        unsigned char Unused_Field_4: 1;
        unsigned char UP_Link: 1; // 0 - message transferred from BASE NODE to SERVICE NODE, 1 - message transferred from SERVICE NODE to BASE NODE
        unsigned char Unused_Field_5: 1;
        unsigned char Unused_Field_6: 1;
        unsigned char Unused_Field_7: 1;
        unsigned char Unused_Field_8: 1;
        unsigned char Unused_Field_9: 1;
    } Field;
    char Byte_Array[28];
} RF_Preamble_str;

class DataLogic_Class : public QObject
{
    Q_OBJECT
public:
    explicit DataLogic_Class(CRC16_Class *oCRC16,QTimer *t,SI4463Class *SI4463Conf,SI4432Class *SI4432Conf,MODEMClass *MODEM,Port *nPort,TCP *nTCP,QObject *parent = 0);

    uint         DataLogicMode;
    uint         Repeat_Number;
    uint         Repeat_Counter;
    uint         Delay_Time;

    void setSerialNumberMode(QString S, bool Enable);
    void setCurrentSI4463_PROPERTYS_structur(uint select);

private:
    SI4463Class     *SI4463Conf;
    SI4432Class     *SI4432Conf;
    QTimer          *timer, *timerRepeat;
    CRC16_Class     *CRC16;
    MODEMClass      *MODEM;
    Port            *nPort;
    TCP             *nTCP;

    QByteArray      InDataBuffer;
    QByteArray      OutDataBuffer;
    QByteArray      ParceDataBuffer;
    QByteArray      repeat_data;

    QString         SerialNumber;
    RF_Preamble_str RF_Preamble;
    bool            addSerialNumber;

    SI4463_PROPERTYS_structur* CurrentSI4463_PROPERTYS_structur;


signals:
    void OutData(QByteArray data);
    void DataForPrint(QByteArray data,uint n);
    void LogForPrint(QString data,uint n);
    void outConnect(uint n, uint state);
    void outCurrentRSSI(signed short RSSI);
    void outLRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC);
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
