#ifndef SI4432_SETTINGS_FORM_H
#define SI4432_SETTINGS_FORM_H

#include "ui_si4432_settings_form.h"
#include "myformabstractclass.h"
#include "SI4432/si4432class.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

//namespace Ui {
//class SI4432_Settings_Form;
//}

class SI4432_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit SI4432_Settings_Form(QWidget *parent = 0);
    ~SI4432_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    //void Out_SI4432_Parameters_Changed(SI4432ConfigurationClass*);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);
    void isStopped(void);
    void isRF_Reset(void);

    void isSI4432_Parameters(void);

    void setIn_SI4432_Parameters(SI4432ConfigurationClass*);
    void setOut_SI4432_Parameters(SI4432ConfigurationClass*);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void CalculateDR_BPS(void);
    void CalculateFNOM(unsigned char);
    void CalculateFo(void);
    void CalculateFd(void);
    void on_MT_currentIndexChanged(int index);
    void on_PA_currentIndexChanged(int index);
    void on_DIV_DR_stateChanged(int arg1);
    void on_DR_valueChanged(int arg1);
    void on_FX2_stateChanged(int arg1);
    void on_FCAR_currentIndexChanged(int index);
    void on_FNOM_valueChanged(double arg1);
    void on_FOFF_valueChanged(int arg1);
    void on_DV_valueChanged(int arg1);
    void on_BW_currentIndexChanged(int index);
    void on_CLOAD_textEdited(const QString &arg1);
    void on_SNW_N_currentIndexChanged(int index);
    void on_HEAD_N_currentIndexChanged(int index);
    void on_SNW_textEdited(const QString &arg1);
    void on_HEAD_TX_textEdited(const QString &arg1);
    void on_HEAD_RX_textEdited(const QString &arg1);
    void on_Write_clicked();
    void on_Stop_clicked();
    void on_Reset_clicked();
    void on_btnSettings_clicked();

    void setMTToUI(unsigned char);
    void setPAToUI(unsigned char);
    void setDIV_DRToUI(unsigned char);
    void setDRToUI(unsigned short);
    void setHBToUI(unsigned char);
    void setFCToUI(unsigned char);
    void setFNOMToUI(unsigned int);
    void setFOFFToUI(signed short);
    void setDVToUI(unsigned short);
    void setIFBWToUI(unsigned char);
    void setSNW_NToUI(unsigned char);
    void setHEAD_NToUI(unsigned char);
    void setSNWToUI(unsigned int);
    void setHEAD_TXToUI(unsigned int);
    void setHEAD_RXToUI(unsigned int);
    void setCLOADToUI(unsigned char);
    void setCLOAD_PFToUI(unsigned int);
    void setRXOSRToUI(unsigned int);
    void setNCOFFToUI(unsigned int);
    void setCRGAINToUI(unsigned int);
    void setNdecToUI(unsigned char);
    void setDwn3ToUI(unsigned char);
    void setFilsetToUI(unsigned char);

    void DeviceVersionHandling(void);

private:
    Ui::SI4432_Settings_Form    *ui;
    QSysInfo                    *SysInfo;
    QRegExp                      RegSystemName;
    ResizeCalculating            resize_calculating;

    SI4432ConfigurationClass    *In_SI4432_Parameters;
    SI4432ConfigurationClass    *Out_SI4432_Parameters;

};

#endif // SI4432_SETTINGS_FORM_H
