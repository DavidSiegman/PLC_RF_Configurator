#ifndef SI4432_SETTINGS_FORM_H
#define SI4432_SETTINGS_FORM_H

#include <QWidget>
#include <QPlainTextEdit>

#include "SI4432/si4432class.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

namespace Ui {
class SI4432_Settings_Form;
}

class SI4432_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4432_Settings_Form(QWidget *parent = 0);
    ~SI4432_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel(void);
    void Next(void);
    void isCreated(void);
    void Get_Console(QPlainTextEdit* console);

    void OUT_SI4432_Parameters_CHANGED(RF_Config_struct);

public slots:
    void SetProgress(uint progress);

    void setIN_SI4432_Parameters(RF_Config_struct);

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

private:
    Ui::SI4432_Settings_Form *ui;

    RF_Config_struct  IN_SI4432_Parameters;
    RF_Config_struct  OUT_SI4432_Parameters;
};

#endif // SI4432_SETTINGS_FORM_H
