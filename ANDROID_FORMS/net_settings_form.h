#ifndef NET_SETTINGS_FORM_H
#define NET_SETTINGS_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include "myformabstractclass.h"
#include "ui_net_settings_form.h"
#include "CRC/crc16_class.h"
#include "MODEM/modemclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"

//namespace Ui {
//class Net_Settings_Form;
//}

class Net_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Net_Settings_Form(QWidget *parent = 0);
    ~Net_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Retranslation_Table(QWidget*);
    void Stop_Send_Data(void);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isSwitchMode(void);
    void isSwitchLevel(void);
    void isSwitchTimeout(void);
    void isStopped(void);
    void isRF_Reset(void);

    void Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data);
    void Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void on_btnSettings_clicked();
    void on_Switch_stateChanged(int arg1);
    void on_Reset_clicked();
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
    void on_SetMask_clicked();
    void on_SetLevel_clicked();
    void on_SetTimeout_clicked();
    void on_NetTable_clicked();
    void on_ClearConsole_clicked();

    void SetSwitchModeToUI(uchar);
    void SetSwitchLevelToUI(uint);
    void SetSwitchTimeoutToUI(uint);
    void SetSwitchMaskToUI(uint);

    void  Set_SwitchMode(uchar);
    uchar Get_SwitchMode(void);
    void  Set_SwitchLevel(uint);
    void  Set_SwitchTimeout(uint);
    void  Set_SwitchMask(uint);
    uint  Get_SwitchMask(void);

    void DeviceVersionHandling(void);

private:
    Ui::Net_Settings_Form        *ui;

    RetranslatorPropertiesClass*  In_Retranslator_Properties;
    RetranslatorPropertiesClass*  Out_Retranslator_Properties;

    ResizeCalculating             resize_calculating;
};

#endif // NET_SETTINGS_FORM_H
