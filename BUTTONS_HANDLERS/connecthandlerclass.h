#ifndef CONNECTHANDLERCLASS_H
#define CONNECTHANDLERCLASS_H

#include <QObject>
#include "DATALOGIC/datalogic_class.h"
#include "MODEM/modemclass.h"
#include "MONITOR/monitorclass.h"
#include "ui_mainwindow.h"
#include <mess_enum.h>

class ConnectHandlerClass : public QObject
{
    Q_OBJECT
public:
    explicit ConnectHandlerClass(Ui::MainWindow *ui, DataLogic_Class *DataLogic,MODEMClass *MODEM,QObject *parent = 0);
private:
    Ui::MainWindow  *ui;
    DataLogic_Class *DataLogic;
    MODEMClass      *MODEM;
    MonitorClass    *Monitor;

    QWidget *NetTab, *PLCTab, *RFTab, *RFOldTab, *SniferTab, *RFMonitorTab;

    uint ReadDataProgress;

signals:
    void SendComand(uint n, uint m);
    void SendLog(QString data, uint n);
    void MonitorStart();
    void MonitorStop();
public slots:
    void aOPEN();
    void SetSWITCH_MODE();
    void SetSWITCH_PROP();
    void StartMonitor();
    void StopMonitor();
    void ReadCURRENT_RSSI();
    void ReadLRSSI_AFC();
    void WriteRF_PARAMS();
    void SendRF_RESET();
    void SendSNIFER_MODE();
    void SendUPLINC_MODE();
    void SendCRC_DISABLE_MODE();
    void SendBROADCAST_MODE();
    void WriteSWITCH_TABLE();

    void ConnectHandling(uint n, uint state);

    void isAOPEN();
    void isSWITCH_MODE();
    void isSWITCH_PROP();
    void isCURRENT_RSSI();
    void isLRSSI_AFC();
    void isRF_PARAMS();
    void isRF_RESET();
    void isSNIFER_MODE();
    void isUPLINC_MODE();
    void isCRC_DISABLE_MODE();
    void isBROADCAST_MODE();
    void isSWITCH_TABLE();
};

#endif // CONNECTHANDLERCLASS_H
