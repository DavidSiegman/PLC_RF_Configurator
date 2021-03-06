#ifndef MONITORCLASS_H
#define MONITORCLASS_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <OTHER_FUNCTIONS/mess_enum.h>

class MonitorClass : public QThread
{
    Q_OBJECT
public:
    explicit MonitorClass(uint Timeout, uint Parameter, QObject *parent = 0);
    void run();
    QTimer *timer;
private:
    uint Timeout, Parameter;
    uint ThreadState;
    bool ThreadStarted;
    uint Message;


signals:
    void SendComand(uint SelectComandQueue,uint SendMode);
public slots:
    void handlingMonitor();
    void startMonitor(uint Message);
    void stopMonitor();
};

#endif // MONITORCLASS_H
