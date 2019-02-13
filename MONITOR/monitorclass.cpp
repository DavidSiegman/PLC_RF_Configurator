#include "monitorclass.h"

MonitorClass::MonitorClass(uint Timeout, uint Parameter, QObject *parent)
{
    this->Timeout   = Timeout;
    this->Parameter = Parameter;\
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(handlingMonitor()));
    ThreadState = 0;
}

void MonitorClass::run()
{
    while(ThreadStarted)
    {

    }
}

void MonitorClass::handlingMonitor()
{
    if (Parameter == 0)
    {
        emit SendComand(SEND_READ_LRSSI_AFC_CURRENT,MONITOR_SEND_CONTROL);
    }
    else if (Parameter == 1)
    {
        emit SendComand(SEND_READ_LRSSI_AFC,MONITOR_SEND_CONTROL);
    }
    else
    {

    }

}

void MonitorClass::startMonitor()
{
    ThreadStarted = true;

    timer->start(Timeout);

    this->start();
}
void MonitorClass::stopMonitor()
{
    ThreadStarted = false;
    this->deleteLater();
}
