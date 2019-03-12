#ifndef INTERFACES_CONTROL_FORM_H
#define INTERFACES_CONTROL_FORM_H

#include "ui_interfaces_control_form.h"
#include "myformabstractclass.h"
#include "MODEM/modemclass.h"

//namespace Ui {
//class Interfaces_Control_Form;
//}

#define INIT_OK_STRING  "Активен"
#define ERROR_STRING    "Ошибка"
#define DISABLED_STRING "Выключен"

class Interfaces_Control_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Interfaces_Control_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Interfaces_Control_Form();

signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isStopped(void);
    void isRF_Reset(void);
    void isInterfaces_Control(void);

    void Set_In_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);
    void Set_Out_PLC_RF433_Modem_Properties (PlcRfModemPropertiesClass*);

private slots:
    void on_Reset_clicked();
    void on_Stop_clicked();
    void on_Back_clicked();
    void on_btnSettings_clicked();
    void on_Next_clicked();
    void on_btnPLCEnable_toggled(bool checked);
    void on_btnRFEnable_toggled(bool checked);
    void on_btnRSEnable_toggled(bool checked);
    void on_btnPLCEnable_released();
    void on_btnRFEnable_released();
    void on_btnRSEnable_released();

    void setInterfaces_ControlToUI(Interfaces_Control_Type);
    void setLastAOPENTimeToUI(RealTime time);

private:
    Ui::Interfaces_Control_Form *ui;
    QSysInfo                    *SysInfo;
    QRegExp                      RegSystemName;
    ResizeCalculating            resize_calculating;

    PlcRfModemPropertiesClass   *In_PLC_RF433_Modem_Properties;
    PlcRfModemPropertiesClass   *Out_PLC_RF433_Modem_Properties;
};

#endif // INTERFACES_CONTROL_FORM_H
