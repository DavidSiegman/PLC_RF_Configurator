#ifndef PLC_RF_NETSETTINGS_FORM_H
#define PLC_RF_NETSETTINGS_FORM_H

#include "ui_plc_rf_netsettings_form.h"
#include "myformabstractclass.h"
#include "MODEM/modemclass.h"

namespace Ui {
class PLC_RF_NetSettings_Form;
}

class PLC_RF_NetSettings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit PLC_RF_NetSettings_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~PLC_RF_NetSettings_Form();

signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isStopped(void);
    void isRF_Reset(void);
    void isInterfaces_Control(void);
    void isUpLink_Mode(void);
    void isCRC_Disable_Mode(void);
    void isBroadcasting_Mode(void);
    void isMask_Destination(void);
    void isSwitchTimeout(void);
    void isSwitchLevel(void);

    void Set_In_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);
    void Set_Out_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);
    void Set_In_Sniffer_Properties (SnifferPropertiesClass*);
    void Set_Out_Sniffer_Properties (SnifferPropertiesClass*);
    void Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data);
    void Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data);

private slots:
    void on_Reset_clicked();
    void on_Stop_clicked();
    void on_Back_clicked();
    void on_btnSettings_clicked();
    void on_Next_clicked();
    void on_Mode_currentIndexChanged(int);
    void on_btnPLCToPLCRet_released();
    void on_btnPLCToRFRet_released();
    void on_btnRFToPLCRet_released();
    void on_btnRFToRFRet_released();
    void on_Up_Link_stateChanged(int arg1);
    //void on_Sniffer_Mode_currentIndexChanged(int index);
    void on_Disable_CRC_stateChanged(int arg1);
    void on_Broadcasting_stateChanged(int arg1);
    void on_SetDestinationMASK_clicked();
    void on_SetMask_clicked();
    void on_SetTimeout_clicked();
    void on_LVL0_valueChanged(int arg1);
    void on_LVL1_valueChanged(int arg1);
    void on_LVL2_valueChanged(int arg1);
    void on_LVL3_valueChanged(int arg1);
    void on_LVL4_valueChanged(int arg1);
    void on_LVL5_valueChanged(int arg1);
    void on_LVL6_valueChanged(int arg1);
    void on_LVL7_valueChanged(int arg1);
    void on_LVL8_valueChanged(int arg1);
    void on_LVL9_valueChanged(int arg1);
    void on_LVL0_2_valueChanged(int arg1);
    void on_LVL1_2_valueChanged(int arg1);
    void on_LVL2_2_valueChanged(int arg1);
    void on_LVL3_2_valueChanged(int arg1);
    void on_LVL4_2_valueChanged(int arg1);
    void on_LVL5_2_valueChanged(int arg1);
    void on_LVL6_2_valueChanged(int arg1);
    void on_LVL7_2_valueChanged(int arg1);
    void on_LVL8_2_valueChanged(int arg1);
    void on_LVL9_2_valueChanged(int arg1);

    void  Set_UpLink(uchar);
    uchar Get_UpLink(void);
    void  Set_CRCDisable(uchar);
    uchar Get_CRCDisable(void);
    void  Set_Broadcasting(uchar);
    uchar Get_Broadcasting(void);
    void  Set_Mask_Destination(uint);
    uint  Get_Mask_Destination(void);
    void  Set_SwitchTimeout(uint);
    void  Set_SwitchMask(uint);
    uint  Get_SwitchMask(void);

    void SetMaskDestinationToUI(uint);
    //void SetTableItemToUI(QString);

    void SetUpLink_ModeToUI(uchar);
    void SetCRC_Disable_ModeToUI(uchar);
    void SetBroadcasting_ModeToUI(uchar);
    void SetSwitchTimeoutToUI(uint);
    void SetSwitchMaskToUI(uint);
    void setInterfaces_ControlToUI(Interfaces_Control_Type);
    void DeviceVersionHandling(void);

private:
    Ui::PLC_RF_NetSettings_Form *ui;
    QSysInfo                    *SysInfo;
    QRegExp                      RegSystemName;
    ResizeCalculating            resize_calculating;

    PlcRfModemPropertiesClass   *In_PLC_RF433_Modem_Properties;
    PlcRfModemPropertiesClass   *Out_PLC_RF433_Modem_Properties;

    SnifferPropertiesClass      *In_Sniffer_Properties;
    SnifferPropertiesClass      *Out_Sniffer_Properties;

    RetranslatorPropertiesClass *In_Retranslator_Properties;
    RetranslatorPropertiesClass *Out_Retranslator_Properties;
};

#endif // PLC_RF_NETSETTINGS_FORM_H
