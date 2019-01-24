#ifndef SNIFFER_SETTINGS_FORM_H
#define SNIFFER_SETTINGS_FORM_H

#include <QWidget>
#include <QPlainTextEdit>
#include "MODEM/modemclass.h"
#include "myformabstractclass.h"
#include "ui_sniffer_settings_form.h"
#include "RESIZE_CALCULATING/resizecalculating.h"

//namespace Ui {
//class Sniffer_Settings_Form;
//}

class Sniffer_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Sniffer_Settings_Form(QWidget *parent = 0);
    ~Sniffer_Settings_Form();

    void resizeEvent(QResizeEvent *event);

signals:
    void Send_Sniffer_Mode(void);
    void Send_UpLink_Mode(void);
    void Send_CRC_Disable_Mode(void);
    void Send_Broadcasting_Mode(void);
    void Send_Mask_Destination(void);
    void Set_Switch_Prop(void);
    void Send_Switch_Prop(void);
    void Clear_Switch_Table(void);
    void Send_Clear_Switch_Table(void);
    void Send_Write_Switch_Table(void);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);
    void isStopped(void);
    void isRF_Reset(void);

    void Set_In_Sniffer_Properties (SnifferPropertiesClass*);
    void Set_Out_Sniffer_Properties (SnifferPropertiesClass*);
    void Set_In_Retranslator_Properties (RetranslatorPropertiesClass*);
    void Set_Out_Retranslator_Properties (RetranslatorPropertiesClass*);

    void isSnifferMode(void);
    void isUpLink_Mode(void);
    void isCRC_Disable_Mode(void);
    void isBroadcasting_Mode(void);
    void isMask_Destination(void);
    void isSwitch_Prop(void);
    void isSwitch_Table(void);
    void isSwitch_Table_Delete(void);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void on_Up_Link_stateChanged(int arg1);
    void on_Sniffer_Mode_currentIndexChanged(int index);
    void on_Disable_CRC_stateChanged(int arg1);
    void on_Broadcasting_stateChanged(int arg1);
    void on_Reset_clicked();
    void on_SetDestinationMASK_clicked();
    void on_SetNetLevel_clicked();
    void on_SetDeviceMonitorSN_clicked();
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
    void on_Stop_clicked();
    void on_btnSettings_clicked();

    void Set_SnifferMode(uchar);
    uchar Get_SnifferMode(void);
    void Set_UpLink(uchar);
    uchar Get_UpLink(void);
    void Set_CRCDisable(uchar);
    uchar Get_CRCDisable(void);
    void Set_Broadcasting(uchar);
    uchar Get_Broadcasting(void);
    void Set_Mask_Destination(uint);
    uint Get_Mask_Destination(void);

    void SetMaskDestinationToUI(uint);
    void SetTableItemToUI(QString);

    void SetSnifferModeToUI(uchar);
    void SetUpLink_ModeToUI(uchar);
    void SetCRC_Disable_ModeToUI(uchar);
    void SetBroadcasting_ModeToUI(uchar);

    //void Write_Item_To_Switch_Table(QString);

private:
    Ui::Sniffer_Settings_Form    *ui;

    SnifferPropertiesClass       *In_Sniffer_Properties;
    SnifferPropertiesClass       *Out_Sniffer_Properties;

    RetranslatorPropertiesClass  *In_Retranslator_Properties;
    RetranslatorPropertiesClass  *Out_Retranslator_Properties;

    ResizeCalculating             resize_calculating;
};

#endif // SNIFFER_SETTINGS_FORM_H
