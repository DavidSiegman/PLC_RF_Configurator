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
        emit SendComand(this->Message,MONITOR_SEND_CONTROL);
    }
    else if (Parameter == 1)
    {
        emit SendComand(this->Message,MONITOR_SEND_CONTROL);
    }
    else
    {

    }

}

void MonitorClass::startMonitor(uint new_Message)
{
    ThreadStarted = true;
    this->Message = new_Message;

    timer->start(Timeout);

    this->start();
}
void MonitorClass::stopMonitor()
{
    ThreadStarted = false;
    this->deleteLater();
}
