#include "COM/port.h"

Port :: Port(QObject *parent)
{
    //oCRC16 = new CRC16_Class();
}

Port :: ~Port()
{
    qDebug("By in Thread!");
    emit finished_Port();
}

void Port :: run(){
    qDebug("Hello World in Thread!");
    connect(&this->thisPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&this->thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
    emit PortStartProcess();
}

void Port :: Set_PortName(QString Name)
{
    SettingsPort.name        = Name;
    QString s = "Set Port Name: "; s += Name;
    qDebug() << s;
}

void Port :: Set_BaudRate(int BaudRate)
{
    SettingsPort.baudRate = (QSerialPort::BaudRate) BaudRate;
    QString s = "Set BaudRate: "; s += QString("%1").arg(BaudRate);
    qDebug() << s;
}

void Port :: Set_DataBits(int DataBits)
{
    SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
    QString s = "Set DataBits: "; s += QString("%1").arg(DataBits);
    qDebug() << s;
}

void Port :: Set_Parity(int Parity)
{
    SettingsPort.parity = (QSerialPort::Parity) Parity;
    QString s = "Set Parity: "; s += QString("%1").arg(Parity);
    qDebug() << s;
}

void Port :: Set_StopBits(int StopBits)
{
    SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
    QString s = "Set StopBits: "; s += QString("%1").arg(StopBits);
    qDebug() << s;
}

void Port :: Set_FlowControl(int FlowControl)
{
    this->SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
    QString s = "Set FlowControl: "; s += QString("%1").arg(FlowControl);
    qDebug() << s;
}

void Port :: Connect(void)
{
    this->thisPort.setPortName(this->SettingsPort.name);
    QString s = "Connect Port: "; s += this->SettingsPort.name;
    qDebug() << s;
    if (this->thisPort.open(QIODevice::ReadWrite))
    {
        if (this->thisPort.setBaudRate(this->SettingsPort.baudRate)
         && this->thisPort.setDataBits(this->SettingsPort.dataBits)//DataBits
         && this->thisPort.setParity(this->SettingsPort.parity)
         && this->thisPort.setStopBits(this->SettingsPort.stopBits)
         && this->thisPort.setFlowControl(this->SettingsPort.flowControl))
        {
            if (this->thisPort.isOpen())
            {
                error_(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Открыт!\r",COM_OPEN);
            }
        }
        else
        {
            this->thisPort.close();
            error_(this->thisPort.errorString().toLocal8Bit() + "\r",NONE);
        }
    }
    else
    {
        this->thisPort.close();
        error_(this->thisPort.errorString().toLocal8Bit() + "\r",NONE);
    }
}

void Port::handleError(QSerialPort::SerialPortError error)//
{
    if ( (this->thisPort.isOpen()) && (error == QSerialPort::ResourceError)) {
        error_(this->thisPort.errorString().toLocal8Bit() + "\r",NONE);
        DisconnectPort();
    }
    QString s = "Error: "; s += error;
    qDebug() << s;
}//


void  Port::DisconnectPort(){
    if(this->thisPort.isOpen()){
        this->thisPort.close();
        error_(">> ======= Порт " + this->SettingsPort.name.toLocal8Bit() + " Закрыт!\r",COM_CLOSE);
    }
}
//ot tuta kovuratji!!!
void Port :: WriteToPort(QByteArray data)
{
    if(this->thisPort.isOpen())
    {
        this->thisPort.write(data);
    }
}
//
void Port :: ReadInPort()
{
    QByteArray  in_data;
    in_data.append(this->thisPort.readAll());
    outPort(in_data);
    //((QString)(adr.toInt())).toLatin1().toHex()
}

