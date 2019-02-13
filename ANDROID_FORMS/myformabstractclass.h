#ifndef MYFORMABSTRACTCLASS_H
#define MYFORMABSTRACTCLASS_H

#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QPlainTextEdit>
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "MODEM/firmwareinformationclass.h"

class myFormAbstractClass : public QWidget
{
    Q_OBJECT
public:
    explicit myFormAbstractClass(QWidget *parent = 0);

signals:
    void isCreated(void);
    void Cancel(QRect);
    void Next(QRect);
    void Settings(QWidget*);
    void ForcedClosed(void);
    void Get_Geometry(QRect);
    void Stop_Send_Data(void);
    void Get_Console(QPlainTextEdit* console);
    void StartSendingProcess(uint SelectComandQueue, uint SendMode);

public slots:
    void SetProgress(uint progress);
    void Set_Geometry(QRect);

    void isStopped(void);
    void isRF_Reset(void);

    void Reset_ClickHandler(void);
    void Back_ClickHandler(void);
    void Next_ClickHandler(void);
    void Setting_ClickHandler(void);
    void ForceCloseHandler(void);
    void Stop_ClickHandler(void);

    uchar Get_resizing_going(void);
    void  Set_resizing_going(uchar);

    void Set_In_Firmware_Information(FirmwareInformationClass*);
    FirmwareInformationClass* Get_In_Firmware_Information(void);
    void Set_ConnectionType(uchar);
    uchar Get_ConnectionType(void);

private:
    FirmwareInformationClass *In_Firmware_Information;
    uchar                     ConnectionType;
    uchar                     resizing_going;
};

#endif // MYFORMABSTRACTCLASS_H
