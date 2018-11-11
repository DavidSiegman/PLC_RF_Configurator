#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <qdebug.h>
#include <OTHER_FUNCTIONS/mess_enum.h>

struct TCPSettings {
    QString                  IP;
    uint                     PORT;

};

class TCP: public QThread
{
    Q_OBJECT
public:
    explicit TCP(QObject *parent = 0);
    void run();
    ~TCP();

private:
    TCPSettings    SettingsTCP;
    QTcpSocket    *TCPSocket;

signals:
    void TCP_Finished();
    void TCP_Log(QString err, uint n);
    void TCP_OutDATA(QByteArray data);
    void TCP_Started();
    void TCP_Connected();

public slots:
    void TCP_Disconnect();
    void TCP_Connect();
    void TCP_SetIP(QString IP);
    void TCP_SetPORT(uint PORT);
    void TCP_WriteDATA(QByteArray data);
    void TCP_ReadDATA();

private slots:
    void TCP_ErrorHandler(QAbstractSocket::SocketError error);//
};

#endif // TCP_H
