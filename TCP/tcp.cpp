#include "TCP/tcp.h"

TCP::TCP(QObject *parent)
{
    this->setParent(parent);
    TCPSocket = new QTcpSocket(this);

    SettingsTCP.IP   = "95.79.111.134";
    SettingsTCP.PORT = 1131;
}


 TCP::~TCP()
{
    qDebug("By in TCP Thread!");
    emit TCP_Finished();
}

void TCP::run(){
    qDebug("Hello World in TCP Thread!");
    connect(this->TCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(TCP_ErrorHandler(QAbstractSocket::SocketError)));
    connect(this->TCPSocket, SIGNAL(readyRead()),this,SLOT(TCP_ReadDATA()));
    emit TCP_Started();
}

void  TCP::TCP_Disconnect()
{
    if(this->TCPSocket->isOpen()){
        this->TCPSocket->close();
        emit TCP_Log(">> ======= Соединение с: " + this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT)+ " разорвано!\r",TCP_CLOSE);
    }
}
void  TCP::TCP_Connect()
{
    this->TCPSocket->connectToHost(this->SettingsTCP.IP, this->SettingsTCP.PORT);
    QString s = "Connect: "; s += this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT) ;
    qDebug() << s;

    if (this->TCPSocket->isOpen())
    {
        emit TCP_Log(">> ======= Соединение с: " + this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT)  + " установлено\r",TCP_OPEN);
        emit TCP_Connected();
    }
    else
    {
        this->TCPSocket->close();
        emit TCP_Log(this->TCPSocket->errorString().toLocal8Bit() + "\r",NONE);
    }
}
void  TCP::TCP_SetIP(QString IP)
{
    this->SettingsTCP.IP = IP;
}
void  TCP::TCP_SetPORT(uint PORT)
{
    this->SettingsTCP.PORT = PORT;
}
void  TCP::TCP_WriteDATA(QByteArray data)
{
    if(this->TCPSocket->isOpen())
    {
        this->TCPSocket->write(data);
    }
}
void  TCP::TCP_ReadDATA()
{
    QByteArray  in_data;
    in_data.append(this->TCPSocket->readAll());
    emit TCP_OutDATA(in_data);
}
void TCP::TCP_ErrorHandler(QAbstractSocket::SocketError error)//
{
    if ((this->TCPSocket->isOpen())) {
        QString strError =
                "Error: " + (error == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             error == QAbstractSocket::RemoteHostClosedError ?
                             "The remote host is closed." :
                             error == QAbstractSocket::ConnectionRefusedError ?
                             "The connection was refused." :
                             QString(this->TCPSocket->errorString())
                            );
        QString s = "Error: "; s += strError;
        qDebug() << s;
        emit TCP_Log(this->TCPSocket->errorString().toLocal8Bit() + "\r",NONE);
    }
}
