#ifndef CONNECTHANDLERCLASS_H
#define CONNECTHANDLERCLASS_H

#include <QObject>
#include "DATALOGIC/datalogic_class.h"
#include "MODEM/modemclass.h"
#include "MODEM/FirmwareInformationClass.h"
#include "MONITOR/monitorclass.h"
#include "ui_mainwindow.h"
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "UPDATE/update.h"

#define CommandsQueueLength 20

typedef struct ConnectHandler_Type {
    uint  CommandsQueue[CommandsQueueLength];
    uchar CommandsNumber;
    uchar ModuleChoiceEnable;
    uchar ModuleTypeIndex;
    uint  CommandsQueuePreIndex;
    uint  CommandsQueueCurrentIndex;
}ConnectHandlerStruct;

class ConnectHandlerClass : public QObject
{
    Q_OBJECT
public:
    explicit ConnectHandlerClass(DataLogic_Class *DataLogic,MODEMClass *MODEM,UPDATE *nUPDATE,QObject *parent = 0);
private:
    DataLogic_Class     *DataLogic;
    MODEMClass          *MODEM;
    MonitorClass        *Monitor;
    UPDATE              *nUPDATE;

    uchar                ModuleType;
    uchar                Interface;

    ConnectHandlerStruct ConnectHandler;

    uint EnableModuleChoiceMode(FirmwareInformationClass* device);
    void EmitCurrentSignal(uint SelectComandQueue,uint SendMode);

signals:
    void SendComand(uint n, uint m);
    void SendLog(QString data, uint n);
    void MonitorStart();
    void MonitorStop();

    void Progress(uint progress);

    void isAOPEN();
    void isSWITCH_MODE();
    void isSWITCH_PROP();
    void isSWITCH_LEVEL();
    void isSWITCH_TIMEOUT();
    void isCURRENT_RSSI();
    void isLRSSI_AFC();
    void isRFSI4463_PARAMETERS();
    void isRF_RESET();
    void isRFSI4432_PARAMETERS();
    void isPLCST750_PARAMETERS();
    void isSNIFER_MODE();
    void isUPLINK_MODE();
    void isCRC_CHECK_MODE();
    void isBROADCASTING_MODE();
    void isSWITCH_TABLE();
    void isDELET_SWITCH_TABLE();
    void isMASK_DESTINATION();
    void isUPDATED();
    void isDELETED();

public slots:
    void STOP();
    void StartSendingProcess(uint SelectComandQueue, uint SendMode);

    void StartMonitor();
    void StopMonitor();

    void SetModuleType(uchar);
    void SetInterface(uchar);

    void ConnectHandling(uint n, uint state, uint repeate);
};

#endif // CONNECTHANDLERCLASS_H
