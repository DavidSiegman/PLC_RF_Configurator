#ifndef CONNECTHANDLERCLASS_H
#define CONNECTHANDLERCLASS_H

#include <QObject>
#include "DATALOGIC/datalogic_class.h"
#include "MODEM/modemclass.h"
#include "MONITOR/monitorclass.h"
#include "ui_mainwindow.h"
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "UPDATE/update.h"

class ConnectHandlerClass : public QObject
{
    Q_OBJECT
public:
    explicit ConnectHandlerClass(DataLogic_Class *DataLogic,MODEMClass *MODEM,UPDATE *nUPDATE,QObject *parent = 0);
private:
    DataLogic_Class *DataLogic;
    MODEMClass      *MODEM;
    MonitorClass    *Monitor;
    UPDATE          *nUPDATE;

    uint ReadDataProgress;

signals:
    void SendComand(uint n, uint m);
    void SendLog(QString data, uint n);
    void MonitorStart();
    void MonitorStop();

    void Progress(uint progress);

    void isAOPEN();
    void isSWITCH_MODE();
    void isSWITCH_PROP();
    void isCURRENT_RSSI();
    void isLRSSI_AFC();
    void isRF_PARAMS();
    void isRF_RESET();
    void isRFSI4432_PARAMS();
    void isSNIFER_MODE();
    void isUPLINC_MODE();
    void isCRC_DISABLE_MODE();
    void isBROADCAST_MODE();
    void isSWITCH_TABLE();
    void isSWITCH_TABLE_DELETE();
    void isMASK_DESTINATION();
    void isUPDATED();
    void isDELETED();

public slots:
    void STOP();
    void aOPEN();
    void SetSWITCH_MODE();
    void SetSWITCH_PROP();
    void StartMonitor();
    void StopMonitor();
    void ReadCURRENT_RSSI();
    void ReadLRSSI_AFC();
    void WriteRF_PARAMS();
    void WriteRFSI4432_PARAMS();
    void SendRF_RESET();
    void SendSNIFER_MODE();
    void SendUPLINC_MODE();
    void SendCRC_DISABLE_MODE();
    void SendBROADCAST_MODE();
    void WriteSWITCH_TABLE();
    void ReadSWITCH_TABLE();
    void SendSWITCH_TABLE_DELETE();
    void WriteMASK_DESTINATION();
    void StartUPDATE();
    void StartDELETE();

    void ConnectHandling(uint n, uint state);
    void MonitorComandCounter(uint n, uint state);
};

#endif // CONNECTHANDLERCLASS_H
