#include "COM/port.h"

Port :: Port(QObject *parent)
{
    this->setParent(parent);
    this->thisPort = new QSerialPort(this);
}

Port :: ~Port()
{
    qDebug("By in COM Thread!");
    emit COM_Finished();
}

void Port :: run(){
    qDebug("Hello World in COM Thread!");
    connect(this->thisPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(COM_ErrorHandler(QSerialPort::SerialPortError)));
    connect(this->thisPort, SIGNAL(readyRead()),this,SLOT(COM_ReadDATA()));
    emit COM_Started();
}

void Port :: COM_SetPortName(QString Name)
{
    SettingsPort.name = Name;
    QString s = "Set Port Name: "; s += Name;
    qDebug() << s;
}

void Port :: COM_SetBaudRate(int BaudRate)
{
    SettingsPort.baudRate = (QSerialPort::BaudRate) BaudRate;
    QString s = "Set BaudRate: "; s += QString("%1").arg(BaudRate);
    qDebug() << s;
}

void Port :: COM_SetDataBits(int DataBits)
{
    SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
    QString s = "Set DataBits: "; s += QString("%1").arg(DataBits);
    qDebug() << s;
}

void Port :: COM_SetParity(int Parity)
{
    SettingsPort.parity = (QSerialPort::Parity) Parity;
    QString s = "Set Parity: "; s += QString("%1").arg(Parity);
    qDebug() << s;
}

void Port :: COM_SetStopBits(int StopBits)
{
    SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
    QString s = "Set StopBits: "; s += QString("%1").arg(StopBits);
    qDebug() << s;
}

void Port :: COM_SetFlowControl(int FlowControl)
{
    this->SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
    QString s = "Set FlowControl: "; s += QString("%1").arg(FlowControl);
    qDebug() << s;
}

void Port :: COM_Connect(void)
{
    this->thisPort->setPortName(this->SettingsPort.name);
    QString s = "Connect Port: "; s += this->SettingsPort.name;
    qDebug() << s;
    if (this->thisPort->open(QIODevice::ReadWrite))
    {
        if (this->thisPort->setBaudRate(this->SettingsPort.baudRate)
         && this->thisPort->setDataBits(this->SettingsPort.dataBits)//DataBits
         && this->thisPort->setParity(this->SettingsPort.parity)
         && this->thisPort->setStopBits(this->SettingsPort.stopBits)
         && this->thisPort->setFlowControl(this->SettingsPort.flowControl))
        {
            if (this->thisPort->isOpen())
            {
                emit COM_Error(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Открыт!\r",COM_OPEN);
            }
        }
        else
        {
            this->thisPort->close();
            emit COM_Error(this->thisPort->errorString().toLocal8Bit() + "\r",NONE);
        }
    }
    else
    {
        this->thisPort->close();
        emit COM_Error(this->thisPort->errorString().toLocal8Bit() + "\r",NONE);
    }
}

void Port::COM_ErrorHandler(QSerialPort::SerialPortError error)//
{
    if ( (this->thisPort->isOpen()) && (error == QSerialPort::ResourceError)) {
        emit COM_Error(this->thisPort->errorString().toLocal8Bit() + "\r",NONE);
        COM_Disconnect();
    }
    QString s = "Error: "; s += error;
    qDebug() << s;
}//

void  Port::COM_Disconnect(){
    if(this->thisPort->isOpen()){
        this->thisPort->close();
        emit COM_Error(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Закрыт!\r",COM_CLOSE);
    }
}

void Port :: COM_WriteDATA(QByteArray data)
{
    if(this->thisPort->isOpen())
    {
        this->thisPort->write(data);
    }
}

void Port :: COM_ReadDATA()
{
    QByteArray  in_data;
    in_data.append(this->thisPort->readAll());
    emit COM_OutDATA(in_data);
}

