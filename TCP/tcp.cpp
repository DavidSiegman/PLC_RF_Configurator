#include "TCP/tcp.h"

TCP::TCP(QObject *parent)
{
    this->setParent(parent);
    TCPSocket = new QTcpSocket(this);

    SettingsTCP.IP   = "95.79.111.134";
    SettingsTCP.PORT = 1131;
}
 TCP::~TCP(){
    qDebug("By in TCP Thread!");
    emit TCP_Finished();
}
void TCP::run(){
    qDebug("Hello World in TCP Thread!");
    connect(this->TCPSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(TCP_ErrorHandler(QAbstractSocket::SocketError)));
    connect(this->TCPSocket, SIGNAL(readyRead()),this,SLOT(TCP_ReadDATA()));
    emit TCP_Started();
}
void  TCP::TCP_Connect(){
    this->TCPSocket->connectToHost(this->SettingsTCP.IP, this->SettingsTCP.PORT);
    QString s = "Connect: "; s += this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT) ;
    qDebug() << s;

    if (this->TCPSocket->isOpen()){
        emit TCP_Log(">> ======= Соединение с: " + this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT)  + " установлено\r",TCP_OPEN);
        emit TCP_Connected();
    }
    else{
        this->TCPSocket->close();
        emit TCP_Log(this->TCPSocket->errorString().toLocal8Bit() + "\r",NONE);
    }
}
void  TCP::TCP_SetIP(QString IP){
    this->SettingsTCP.IP = IP;
}
void  TCP::TCP_SetPORT(uint PORT){
    this->SettingsTCP.PORT = PORT;
}
void  TCP::TCP_WriteDATA(QByteArray data){
    if(this->TCPSocket->isOpen()){
        this->TCPSocket->write(data);
    }
}
void  TCP::TCP_ReadDATA(){
    QByteArray  in_data;
    in_data.append(this->TCPSocket->readAll());
    emit TCP_OutDATA(in_data);
}
void  TCP::TCP_Disconnect(){
    if(this->TCPSocket->isOpen()){
        this->TCPSocket->close();
        emit TCP_Log(">> ======= Соединение с: " + this->SettingsTCP.IP.toLocal8Bit() + ":" + QString::number(this->SettingsTCP.PORT)+ " разорвано!\r",TCP_CLOSE);
        emit TCP_Disconnected();
    }
}
void TCP::TCP_ErrorHandler(QAbstractSocket::SocketError error)//
{
    QString s = "Error: "; s += error;
    emit TCP_Error();
    switch (error){
    case QAbstractSocket::ConnectionRefusedError:{
        s += " - ConnectionRefusedError";
        emit TCP_Log("QAbstractSocket::ConnectionRefusedError\r",NONE);
        break;
    }
    case QAbstractSocket::RemoteHostClosedError:{
        s += " - RemoteHostClosedError";
        emit TCP_Log("QAbstractSocket::RemoteHostClosedError\r",NONE);
        break;
    }
    case QAbstractSocket::HostNotFoundError:{
        s += " - HostNotFoundError";
        emit TCP_Log("QAbstractSocket::HostNotFoundError\r",NONE);
        break;
    }
    case QAbstractSocket::SocketAccessError:{
        s += " - SocketAccessError";
        emit TCP_Log("QAbstractSocket::SocketAccessError\r",NONE);
        break;
    }
    case QAbstractSocket::SocketResourceError:{
        s += " - SocketResourceError";
        emit TCP_Log("QAbstractSocket::SocketResourceError\r",NONE);
        break;
    }
    case QAbstractSocket::SocketTimeoutError:{
        s += " - SocketTimeoutError";
        emit TCP_Log("QAbstractSocket::SocketTimeoutError\r",NONE);
        break;
    }
    case QAbstractSocket::DatagramTooLargeError:{
        s += " - DatagramTooLargeError";
        emit TCP_Log("QAbstractSocket::DatagramTooLargeError\r",NONE);
        break;
    }
    case QAbstractSocket::NetworkError:{
        s += " - NetworkError";
        emit TCP_Log("QAbstractSocket::NetworkError\r",NONE);
        break;
    }
    case QAbstractSocket::AddressInUseError:{
        s += " - AddressInUseError";
        emit TCP_Log("QAbstractSocket::AddressInUseError\r",NONE);
        break;
    }
    case QAbstractSocket::SocketAddressNotAvailableError:{
        s += " - SocketAddressNotAvailableError";
        emit TCP_Log("QAbstractSocket::SocketAddressNotAvailableError\r",NONE);
        break;
    }
    case QAbstractSocket::UnsupportedSocketOperationError:{
        s += " - UnsupportedSocketOperationError";
        emit TCP_Log("QAbstractSocket::UnsupportedSocketOperationError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyAuthenticationRequiredError:{
        s += " - ProxyAuthenticationRequiredError";
        emit TCP_Log("QAbstractSocket::ProxyAuthenticationRequiredError\r",NONE);
        break;
    }
    case QAbstractSocket::SslHandshakeFailedError:{
        s += " - SslHandshakeFailedError";
        emit TCP_Log("QAbstractSocket::SslHandshakeFailedError\r",NONE);
        break;
    }
    case QAbstractSocket::UnfinishedSocketOperationError:{
        s += " - UnfinishedSocketOperationError";
        emit TCP_Log("QAbstractSocket::UnfinishedSocketOperationError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyConnectionRefusedError:{
        s += " - ProxyConnectionRefusedError";
        emit TCP_Log("QAbstractSocket::ProxyConnectionRefusedError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyConnectionClosedError:{
        s += " - ProxyConnectionClosedError";
        emit TCP_Log("QAbstractSocket::ProxyConnectionClosedError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyConnectionTimeoutError:{
        s += " - ProxyConnectionTimeoutError";
        emit TCP_Log("QAbstractSocket::ProxyConnectionTimeoutError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyNotFoundError:{
        s += " - ProxyNotFoundError";
        emit TCP_Log("QAbstractSocket::ProxyNotFoundError\r",NONE);
        break;
    }
    case QAbstractSocket::ProxyProtocolError:{
        s += " - ProxyProtocolError";
        emit TCP_Log("QAbstractSocket::ProxyProtocolError\r",NONE);
        break;
    }
    case QAbstractSocket::OperationError:{
        s += " - OperationError";
        emit TCP_Log("QAbstractSocket::OperationError\r",NONE);
        break;
    }
    case QAbstractSocket::SslInternalError:{
        s += " - SslInternalError";
        emit TCP_Log("QAbstractSocket::SslInternalError\r",NONE);
        break;
    }
    case QAbstractSocket::SslInvalidUserDataError:{
        s += " - SslInvalidUserDataError";
        emit TCP_Log("QAbstractSocket::SslInvalidUserDataError\r",NONE);
        break;
    }
    case QAbstractSocket::TemporaryError:{
        s += " - TemporaryError";
        emit TCP_Log("QAbstractSocket::TemporaryError\r",NONE);
        break;
    }
    case QAbstractSocket::UnknownSocketError:{
        s += " - UnknownSocketError";
        emit TCP_Log("QAbstractSocket::UnknownSocketError\r",NONE);
        break;
    }
    }
    TCP_Disconnect();
    qDebug() << s;
}
