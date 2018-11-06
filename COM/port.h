#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QThread>
#include <qdebug.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <OTHER_FUNCTIONS/mess_enum.h>

struct COMSettings {
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
    void run();
    ~Port();

    QSerialPort   *thisPort;

private:
    COMSettings    SettingsPort;

signals:
    void COM_Finished(); //
    void COM_Error(QString err, uint n);
    void COM_OutDATA(QByteArray data);
    void COM_Started();

public slots:
    void COM_Disconnect();
    void COM_Connect();
    void COM_SetPortName(QString Name);
    void COM_SetBaudRate(int baudrate);
    void COM_SetDataBits(int DataBits);
    void COM_SetParity(int Parity);
    void COM_SetStopBits(int StopBits);
    void COM_SetFlowControl(int FlowControl);
    void COM_WriteDATA(QByteArray data);
    void COM_ReadDATA();

private slots:
    void COM_ErrorHandler(QSerialPort::SerialPortError error);//

};

#endif // PORT_H
