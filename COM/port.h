#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QThread>
#include <qdebug.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <mess_enum.h>

struct Settings {
    QString                  name;
    qint32                   baudRate;
    QSerialPort::DataBits    dataBits;
    QSerialPort::Parity      parity;
    QSerialPort::StopBits    stopBits;
    QSerialPort::FlowControl flowControl;
};

class Port : public QThread
{
    Q_OBJECT

public:

    explicit Port(QObject *parent = 0);

    ~Port();
    QSerialPort thisPort;

private:
    Settings    SettingsPort;

signals:

    void finished_Port(); //

    void error_(QString err, uint n);

    void outPort(QByteArray data);

    void PortStartProcess();

public slots:

    void DisconnectPort();

    void Connect();

    void Set_PortName(QString Name);

    void Set_BaudRate(int baudrate);

    void Set_DataBits(int DataBits);

    void Set_Parity(int Parity);

    void Set_StopBits(int StopBits);

    void Set_FlowControl(int FlowControl);

    //void process_Port();

    void WriteToPort(QByteArray data);

    void ReadInPort();

private slots:

    void handleError(QSerialPort::SerialPortError error);//

public:
    void run();

};

#endif // PORT_H
