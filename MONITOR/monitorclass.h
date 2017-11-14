#ifndef MONITORCLASS_H
#define MONITORCLASS_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <mess_enum.h>

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


signals:
    void SendComand(uint n,uint m);
public slots:
    void handlingMonitor();
    void startMonitor();
    void stopMonitor();
};

#endif // MONITORCLASS_H
