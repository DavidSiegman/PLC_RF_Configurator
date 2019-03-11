#ifndef PLC_SETTINGS_FORM_H
#define PLC_SETTINGS_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "PLC/plcclass.h"
#include "myformabstractclass.h"
#include "ui_plc_settings_form.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

//namespace Ui {
//class PLC_Settings_Form;
//}

class PLC_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit PLC_Settings_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~PLC_Settings_Form();

signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);
    void isStopped(void);
    void isRF_Reset(void);

    void isST750_Parameters(void);

    void setIn_ST750_Parameters(ST750ConfigurationClass*);
    void setOut_ST750_Parameters(ST750ConfigurationClass*);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void on_Stop_clicked();
    void on_Reset_clicked();
    void on_btnSettings_clicked();
    void on_Write_clicked();
    void on_PLC_HighF_valueChanged(int arg1);
    void on_PLC_LowF_valueChanged(int arg1);
    void on_PLC_Power_valueChanged(int value);
    void on_PLC_Power_sliderReleased();
    void on_PLCModulation_currentIndexChanged(int index);

    void setLOWFToUI(unsigned int);
    void setHIGHFToUI(unsigned int);
    void setTransmit_ConditionsToUI(TX_Conditions_Type);

    void DeviceVersionHandling(void);

private:
    Ui::PLC_Settings_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
    ResizeCalculating         resize_calculating;

    ST750ConfigurationClass  *In_ST750_Parameters;
    ST750ConfigurationClass  *Out_ST750_Parameters;
};

#endif // PLC_SETTINGS_FORM_H
