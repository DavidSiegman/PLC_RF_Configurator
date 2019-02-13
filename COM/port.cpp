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

    connect(this->thisPort, SIGNAL(error(QSerialPort::SerialPortError)),         this, SLOT(COM_ErrorHandler(QSerialPort::SerialPortError)));
    connect(this->thisPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(COM_ErrorHandler(QSerialPort::SerialPortError)));
    connect(this->thisPort, SIGNAL(readyRead()),                                 this, SLOT(COM_ReadDATA()));
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

void Port :: COM_Open(void){
    this->thisPort->setPortName(this->SettingsPort.name);
    QString s = "Connect Port: "; s += this->SettingsPort.name;
    qDebug() << s;
    if (this->thisPort->open(QIODevice::ReadWrite)){
        if (this->thisPort->setBaudRate(this->SettingsPort.baudRate)
         && this->thisPort->setDataBits(this->SettingsPort.dataBits)//DataBits
         && this->thisPort->setParity(this->SettingsPort.parity)
         && this->thisPort->setStopBits(this->SettingsPort.stopBits)
         && this->thisPort->setFlowControl(this->SettingsPort.flowControl)){
            if (this->thisPort->isOpen())
            {
                emit COM_Log(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Открыт!\r",COM_OPEN);
                emit COM_Opend();
            }
        }
        else{
            this->thisPort->close();
            emit COM_Log(this->thisPort->errorString().toLocal8Bit() + "\r",NONE);
        }
    }
    else{
        this->thisPort->close();
        emit COM_Log(this->thisPort->errorString().toLocal8Bit() + "\r",NONE);
    }
}

void Port::COM_ErrorHandler(QSerialPort::SerialPortError error){ //

    QString s = "Error: "; s += error;
    emit COM_Error();
    switch (error){
        // ошибка при попытке открыть несуществующее устройство.
    case QSerialPort::DeviceNotFoundError:{
        s += " - DeviceNotFoundError";
        emit COM_Log("QSerialPort::DeviceNotFoundError\r",NONE);
        break;
    }
        // ошибка при попытке открыть уже открытое устройство другим процессом
    case QSerialPort::PermissionError:{
        s += " - PermissionError";
        emit COM_Log("QSerialPort::PermissionError\r",NONE);
        break;
    }
        // ошибка при попытке открыть уже открытое устройство в этом объекте
    case QSerialPort::OpenError:{
        s += " - OpenError";
        emit COM_Log("QSerialPort::OpenError\r",NONE);
        break;
    }
        // ошибка выполнения операции, которая может быть успешно выполнена только при открытом устройстве
    case QSerialPort::NotOpenError:{
        s += " - NotOpenError";
        emit COM_Log("QSerialPort::NotOpenError\r",NONE);
        break;
    }
        // ошибка записи данных
    case QSerialPort::WriteError:{
        s += " - WriteError";
        emit COM_Log("QSerialPort::WriteError\r",NONE);
        break;
    }
        // ошибка чтения данных
    case QSerialPort::ReadError:{
        s += " - ReadError";
        emit COM_Log("QSerialPort::ReadError\r",NONE);
        break;
    }
        // ошибка ресурс стал недоступен
    case QSerialPort::ResourceError:{
        s += " - ResourceError";
        emit COM_Log("QSerialPort::ResourceError\r",NONE);
        break;
    }
        // операция устройства не поддерживается или запрещена
    case QSerialPort::UnsupportedOperationError:{
        s += " - UnsupportedOperationError";
        emit COM_Log("QSerialPort::UnsupportedOperationError\r",NONE);
        break;
    }
        // ошибка тайм-аута
    case QSerialPort::TimeoutError:{
        s += " - TimeoutError";
        emit COM_Log("QSerialPort::TimeoutError\r",NONE);
        break;
    }
        // неопознанная ошибка
    case QSerialPort::UnknownError:{
        s += " - UnknownError";
        emit COM_Log("QSerialPort::UnknownError\r",NONE);
        break;
    }
    }
    COM_Close();
    qDebug() << s;
}//

void  Port::COM_Close(){
    if(this->thisPort->isOpen()){
        this->thisPort->close();
        emit COM_Log(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Закрыт!\r",COM_CLOSE);
        emit COM_Closed();
    }
}

void Port :: COM_WriteDATA(QByteArray data){
    if(this->thisPort->isOpen())
    {
        this->thisPort->write(data);
    }
}

void Port :: COM_ReadDATA(){
    QByteArray  in_data;
    in_data.append(this->thisPort->readAll());
    emit COM_OutDATA(in_data);
}

