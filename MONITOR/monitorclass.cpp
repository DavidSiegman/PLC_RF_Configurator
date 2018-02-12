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
        emit SendComand(SEND_READ_RSSI_CURRENT,CONFIG_SEND_WHITOUT_REPEAT);
    }
    else if (Parameter == 1)
    {
        emit SendComand(SEND_READ_RSSI,CONFIG_SEND_WHITOUT_REPEAT);
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
