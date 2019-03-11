#ifndef RS_SETTINGS_FORM_H
#define RS_SETTINGS_FORM_H

#include "ui_rs_settings_form.h"
#include "myformabstractclass.h"
#include "MODEM/modemclass.h"

//namespace Ui {
//class RS_Settings_Form;
//}

class RS_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit RS_Settings_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~RS_Settings_Form();
signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isStopped(void);
    void isRF_Reset(void);
    void isInterfaces_Control(void);
    void isDebug_Control(void);

    void Set_In_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);
    void Set_Out_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);

private slots:
    void on_Reset_clicked();
    void on_Stop_clicked();
    void on_Back_clicked();
    void on_btnSettings_clicked();
    void on_Next_clicked();
    void on_RS_Mode_currentIndexChanged(int);
    void on_RS_Speed_currentIndexChanged(int);
    void on_btnRSToPLCRet_released();
    void on_btnPLCToRSRet_released();
    void on_btnRSToRFRet_released();
    void on_btnRFToRSRet_released();
    void on_RSToPLCUp_Link_stateChanged(int);
    void on_RSToRFUp_Link_stateChanged(int);
    void on_DebugGlobalEnable_stateChanged(int);
    void on_DebugInterfaceControl_stateChanged(int);
    void on_DebugRetranslationHandling_stateChanged(int);
    void on_DebugToHostHandling_stateChanged(int);
    void on_DebugFromHostHandling_stateChanged(int);
    void on_DebugPLCInititalisation_stateChanged(int);
    void on_DebugPLCUART_stateChanged(int);
    void on_DebugPLCHandling_stateChanged(int);
    void on_DebugRSEnable_stateChanged(int);
    void on_DebugRFEnable_stateChanged(int);
    void on_DebugSI4463Initialisation_stateChanged(int);
    void on_DebugSPIEnable_stateChanged(int);
    void on_DebugHOSTUART_stateChanged(int);
    void on_DebugFlashEnable_stateChanged(int);
    void on_DebugFlashFull_stateChanged(int);

    void setInterfaces_ControlToUI(Interfaces_Control_Type);
    void setDebug_ControlToUI(Debug_Control_Type);
    void DeviceVersionHandling(void);
private:
    Ui::RS_Settings_Form *ui;
    QSysInfo                    *SysInfo;
    QRegExp                      RegSystemName;
    ResizeCalculating            resize_calculating;

    PlcRfModemPropertiesClass   *In_PLC_RF433_Modem_Properties;
    PlcRfModemPropertiesClass   *Out_PLC_RF433_Modem_Properties;
};

#endif // RS_SETTINGS_FORM_H
