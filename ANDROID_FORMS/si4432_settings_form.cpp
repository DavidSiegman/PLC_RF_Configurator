#include "si4432_settings_form.h"
#include "ui_si4432_settings_form.h"

#include "STYLE/style.h"

SI4432_Settings_Form::SI4432_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4432_Settings_Form)
{
    ui->setupUi(this);
}

SI4432_Settings_Form::~SI4432_Settings_Form()
{
    delete ui;
}

void SI4432_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
}

void SI4432_Settings_Form::on_Back_clicked()
{
    emit Cancel();
}

void SI4432_Settings_Form::on_Next_clicked()
{
    emit Next();
}

void SI4432_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void SI4432_Settings_Form::setIN_SI4432_Parameters(RF_Config_struct new_value)
{
    IN_SI4432_Parameters = new_value;

    setMTToUI(getSI4432_MT(&IN_SI4432_Parameters));
    setPAToUI(getSI4432_PA(&IN_SI4432_Parameters));
    setDIV_DRToUI(getSI4432_DivDR(&IN_SI4432_Parameters));
    setDRToUI(getSI4432_TXDR(&IN_SI4432_Parameters));
    setHBToUI(getSI4432_hb(&IN_SI4432_Parameters));
    setFCToUI(getSI4432_FC(&IN_SI4432_Parameters));
    setFNOMToUI(getSI4432_NFREQ(&IN_SI4432_Parameters));
    setFOFFToUI(getSI4432_Fo(&IN_SI4432_Parameters));
    setDVToUI(getSI4432_Fd(&IN_SI4432_Parameters));
    setIFBWToUI(getSI4432_IFBW(&IN_SI4432_Parameters));
    setSNW_NToUI(getSI4432_SWC(&IN_SI4432_Parameters));
    setHEAD_NToUI(getSI4432_HC(&IN_SI4432_Parameters));
    setSNWToUI(IN_SI4432_Parameters.RF_SYNCH_WORD);
    setHEAD_TXToUI(IN_SI4432_Parameters.RF_TX_HAEDER);
    setHEAD_RXToUI(IN_SI4432_Parameters.RF_RX_HAEDER);

    setCLOADToUI(getSI4432_CLOAD(&IN_SI4432_Parameters));
    setCLOAD_PFToUI(IN_SI4432_Parameters.RF_COscill_CLoad);
    setRXOSRToUI(IN_SI4432_Parameters.RXOSR);
    setNCOFFToUI(IN_SI4432_Parameters.NCOFF);
    setCRGAINToUI(IN_SI4432_Parameters.CRGAIN);
    setNdecToUI(IN_SI4432_Parameters.ndec);
    setDwn3ToUI(IN_SI4432_Parameters.dwn3);
    setFilsetToUI(IN_SI4432_Parameters.filset);

    OUT_SI4432_Parameters = IN_SI4432_Parameters;
}

void SI4432_Settings_Form::on_MT_currentIndexChanged(int index)
{
    if (index >= 0)
    {
        setSI4432_MT(&OUT_SI4432_Parameters,index);

        //emit MT_CHANGED((unsigned char)(index),setSI4432_Property_From_Form);
    }
}
void SI4432_Settings_Form::setMTToUI(unsigned char new_value)
{
    ui->MT->setCurrentIndex((int)(new_value));
}

void SI4432_Settings_Form::on_PA_currentIndexChanged(int index)
{
    if (index >= 0)
    {
        setSI4432_PA(&OUT_SI4432_Parameters,index);
        //emit PA_CHANGED((unsigned char)(index),setSI4432_Property_From_Form);
    }
}

void SI4432_Settings_Form::setPAToUI(unsigned char new_value)
{
    ui->PA->setCurrentIndex((int)(new_value));
}

void SI4432_Settings_Form::on_DIV_DR_stateChanged(int arg1)
{
    unsigned char result = 0;
    if (arg1 == 2)
    {
        result = 1;
    }
    setSI4432_DivDR(&OUT_SI4432_Parameters,result);
    CalculateDR_BPS();
    //emit DIV_DR_CHANGED(result,setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setDIV_DRToUI(unsigned char new_value)
{
    if (new_value == 0)
    {
        ui->DIV_DR->setChecked(false);
    }
    else if (new_value == 1)
    {
        ui->DIV_DR->setChecked(true);
    }
    CalculateDR_BPS();
}

void SI4432_Settings_Form::on_DR_valueChanged(int arg1)
{
    setSI4432_TXDR(&OUT_SI4432_Parameters,(unsigned short)(arg1));
    CalculateDR_BPS();
    //emit DR_CHANGED((unsigned short)(arg1),setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setDRToUI(unsigned short new_value)
{
    ui->DR->setValue((int)(new_value));
}

void SI4432_Settings_Form::CalculateDR_BPS(void)
{
    unsigned char  DivDR = 0; if (ui->DIV_DR->isChecked() == true){DivDR = 1;}
    unsigned short DR = (unsigned short)(ui->DR->text().toInt() & 0xFFFF);

    double         DR_BPS = pow(10,6)/pow(2,16+5*DivDR)*(DR);

    ui->DR_BPS->setText(QString::number(DR_BPS));

    calcSI4432_Rb(&OUT_SI4432_Parameters);
    calcSI4432_IFBW(&OUT_SI4432_Parameters);
    calcSI4432_IFBW_bits(&OUT_SI4432_Parameters);
    calcSI4432_RXOSR(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&OUT_SI4432_Parameters); // !!! без манчестерского кода !!!

    setRXOSRToUI(OUT_SI4432_Parameters.RXOSR);
    setIFBWToUI(getSI4432_IFBW(&OUT_SI4432_Parameters));
    setNCOFFToUI(OUT_SI4432_Parameters.NCOFF);
    setCRGAINToUI(OUT_SI4432_Parameters.CRGAIN);
    setNdecToUI(OUT_SI4432_Parameters.ndec);
    setDwn3ToUI(OUT_SI4432_Parameters.dwn3);
    setFilsetToUI(OUT_SI4432_Parameters.filset);
}

void SI4432_Settings_Form::on_FX2_stateChanged(int arg1)
{
    unsigned char result = 0;
    if (arg1 == 2)
    {
        result = 1;
    }

    CalculateFNOM(1);
    CalculateFo();

    setSI4432_hb(&OUT_SI4432_Parameters,result);
    //emit HB_CHANGED(result,setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setHBToUI(unsigned char new_value)
{
    if (new_value == 0)
    {
        ui->FX2->setChecked(false);
    }
    else if (new_value == 1)
    {
        ui->FX2->setChecked(true);
    }

    CalculateFNOM(1);
    CalculateFo();
}

void SI4432_Settings_Form::on_FCAR_currentIndexChanged(int index)
{
    CalculateFNOM(0);
    setSI4432_FC(&OUT_SI4432_Parameters,(unsigned char)(index));
    //emit FC_CHANGED((unsigned char)(index),setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setFCToUI(unsigned char new_value)
{
    ui->FCAR->setCurrentIndex((int)(new_value));
    CalculateFNOM(0);
}

void SI4432_Settings_Form::CalculateFNOM(unsigned char hb_canged_flag)
{
    char hb = 0;

    this->ui->FCAR->setItemText(0,"240-249,99");
    this->ui->FCAR->setItemText(1,"250-259,99");
    this->ui->FCAR->setItemText(2,"260-269,99");
    this->ui->FCAR->setItemText(3,"270-279,99");
    this->ui->FCAR->setItemText(4,"280-289,99");
    this->ui->FCAR->setItemText(5,"290-299,99");
    this->ui->FCAR->setItemText(6,"300-309,99");
    this->ui->FCAR->setItemText(7,"310-319,99");
    this->ui->FCAR->setItemText(8,"320-329,99");
    this->ui->FCAR->setItemText(9,"330-339,99");
    this->ui->FCAR->setItemText(10,"340-349,99");
    this->ui->FCAR->setItemText(11,"350-359,99");
    this->ui->FCAR->setItemText(12,"360-369,99");
    this->ui->FCAR->setItemText(13,"370-379,99");
    this->ui->FCAR->setItemText(14,"380-389,99");
    this->ui->FCAR->setItemText(15,"390-399,99");
    this->ui->FCAR->setItemText(16,"400-409,99");
    this->ui->FCAR->setItemText(17,"410-419,99");
    this->ui->FCAR->setItemText(18,"420-429,99");
    this->ui->FCAR->setItemText(19,"430-439,99");
    this->ui->FCAR->setItemText(20,"440-449,99");
    this->ui->FCAR->setItemText(21,"450-459,99");
    this->ui->FCAR->setItemText(22,"460-469,99");
    this->ui->FCAR->setItemText(23,"470-479,99");

    if (ui->FX2->isChecked() == true)
    {
        hb = 1;

        this->ui->FCAR->setItemText(0,"480-499,99");
        this->ui->FCAR->setItemText(1,"500-519,99");
        this->ui->FCAR->setItemText(2,"520-539,99");
        this->ui->FCAR->setItemText(3,"540-559,99");
        this->ui->FCAR->setItemText(4,"560-579,99");
        this->ui->FCAR->setItemText(5,"580-599,99");
        this->ui->FCAR->setItemText(6,"600-619,99");
        this->ui->FCAR->setItemText(7,"620-639,99");
        this->ui->FCAR->setItemText(8,"640-659,99");
        this->ui->FCAR->setItemText(9,"660-679,99");
        this->ui->FCAR->setItemText(10,"680-699,99");
        this->ui->FCAR->setItemText(11,"700-719,99");
        this->ui->FCAR->setItemText(12,"720-739,99");
        this->ui->FCAR->setItemText(13,"740-759,99");
        this->ui->FCAR->setItemText(14,"760-779,99");
        this->ui->FCAR->setItemText(15,"780-799,99");
        this->ui->FCAR->setItemText(16,"800-819,99");
        this->ui->FCAR->setItemText(17,"820-839,99");
        this->ui->FCAR->setItemText(18,"840-859,99");
        this->ui->FCAR->setItemText(19,"860-879,99");
        this->ui->FCAR->setItemText(20,"880-899,99");
        this->ui->FCAR->setItemText(21,"900-919,99");
        this->ui->FCAR->setItemText(22,"920-939,99");
        this->ui->FCAR->setItemText(23,"940-960,00");
    }

    int  FC = ui->FCAR->currentIndex();

    if (FC >= 0)
    {
        unsigned int min_car = (240000 + FC*10000)*(1 + hb);
        unsigned int max_car = (min_car + 9999*(1+hb) + hb);

        unsigned int fnom    = ui->FNOM->value()*1000;

        unsigned int current_dev = (fnom - ui->FNOM->minimum()*1000);

        this->ui->FNOM->setMinimum(min_car/1000);
        this->ui->FNOM->setMaximum((double)(max_car)/1000);

        if ((fnom >= max_car)||(fnom < min_car))
        {
            if (hb_canged_flag == 0)
            {
                setFNOMToUI(min_car+current_dev);
            }
            else if (hb_canged_flag == 1)
            {
                if (hb == 0)
                {
                    setFNOMToUI(min_car+current_dev/2);
                }
                else if (hb == 1)
                {
                    setFNOMToUI(min_car+current_dev*2);
                }
            }
        }
    }
}

void SI4432_Settings_Form::on_FNOM_valueChanged(double arg1)
{
    int arg = (int)((arg1+0.0005)*1000);
    setSI4432_NFREQ(&OUT_SI4432_Parameters,arg);
    //emit FNOM_CHANGED(arg,setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setFNOMToUI(unsigned int new_value)
{
    ui->FNOM->setValue((double)(new_value)/1000);
}

void SI4432_Settings_Form::on_FOFF_valueChanged(int arg1)
{
    setSI4432_Fo(&OUT_SI4432_Parameters,(signed   short)(arg1));
    CalculateFo();
    //emit FOFF_CHANGED((signed   short)(arg1),setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setFOFFToUI(signed short new_value)
{
    ui->FOFF->setValue(new_value);
    CalculateFo();
}

void SI4432_Settings_Form::CalculateFo(void)
{
    char hb = 0;

    if (ui->FX2->isChecked() == true)
    {
        hb = 1;
    }

    signed  short Fo = ui->FOFF->value();

    double f_ofset = 0.15625*(hb + 1)*Fo;
    this->ui->FOFF_KHZ->setText(QString::number(f_ofset));
}

void SI4432_Settings_Form::on_DV_valueChanged(int arg1)
{

    setSI4432_Fd(&OUT_SI4432_Parameters,(unsigned short)(arg1));
    CalculateFd();

    //emit DV_CHANGED((unsigned short)(arg1),setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setDVToUI(unsigned short new_value)
{
    this->ui->DV->setValue(new_value);
    CalculateFd();
}

void SI4432_Settings_Form::CalculateFd(void)
{
    unsigned short Fd = this->ui->DV->value();
    double dev = Fd*625;

    this->ui->DV_HZ->setText(0xB1 + QString::number(dev));

    calcSI4432_Rb(&OUT_SI4432_Parameters);
    calcSI4432_IFBW(&OUT_SI4432_Parameters);
    calcSI4432_IFBW_bits(&OUT_SI4432_Parameters);
    calcSI4432_RXOSR(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&OUT_SI4432_Parameters); // !!! без манчестерского кода !!!

    setRXOSRToUI(OUT_SI4432_Parameters.RXOSR);
    setIFBWToUI(getSI4432_IFBW(&OUT_SI4432_Parameters));
    setNCOFFToUI(OUT_SI4432_Parameters.NCOFF);
    setCRGAINToUI(OUT_SI4432_Parameters.CRGAIN);
    setNdecToUI(OUT_SI4432_Parameters.ndec);
    setDwn3ToUI(OUT_SI4432_Parameters.dwn3);
    setFilsetToUI(OUT_SI4432_Parameters.filset);
}

void SI4432_Settings_Form::on_BW_currentIndexChanged(int index)
{
    setSI4432_IFBW(&OUT_SI4432_Parameters,(unsigned char)(index));

    calcSI4432_Rb(&OUT_SI4432_Parameters);
    calcSI4432_IFBW_bits(&OUT_SI4432_Parameters);
    calcSI4432_RXOSR(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&OUT_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&OUT_SI4432_Parameters); // !!! без манчестерского кода !!!

    setRXOSRToUI(OUT_SI4432_Parameters.RXOSR);
    setNCOFFToUI(OUT_SI4432_Parameters.NCOFF);
    setCRGAINToUI(OUT_SI4432_Parameters.CRGAIN);
    setNdecToUI(OUT_SI4432_Parameters.ndec);
    setDwn3ToUI(OUT_SI4432_Parameters.dwn3);
    setFilsetToUI(OUT_SI4432_Parameters.filset);

    //IFBW_CHANGED((unsigned char)(index),setSI4432_Property_From_Form);
}

void SI4432_Settings_Form::setIFBWToUI(unsigned char new_value)
{
    this->ui->BW->setCurrentIndex(new_value);
}

void SI4432_Settings_Form::setSNW_NToUI(unsigned char new_value)
{
    this->ui->SNW_N->setCurrentIndex(new_value);
}

void SI4432_Settings_Form::setHEAD_NToUI(unsigned char new_value)
{
    this->ui->HEAD_N->setCurrentIndex(new_value);
}

void SI4432_Settings_Form::setSNWToUI(unsigned int new_value)
{
    QByteArray SNW;

    if(ui->SNW_N->currentIndex() >= 0)
    {
        SNW.append((char)(new_value >> 24));
    }
    if(ui->SNW_N->currentIndex() >= 1)
    {
        SNW.append((char)(new_value >> 16));
    }
    if(ui->SNW_N->currentIndex() >= 2)
    {
        SNW.append((char)(new_value >> 8));
    }
    if(ui->SNW_N->currentIndex() >= 3)
    {
        SNW.append((char)(new_value >> 0));
    }

    ui->SNW->setText(QByteAray_To_QString(SNW).toUpper());
}

void SI4432_Settings_Form::setHEAD_TXToUI(unsigned int new_value)
{
    QByteArray HEAD_TX;

    if(ui->HEAD_N->currentIndex() >= 1)
    {
        HEAD_TX.append((char)(new_value >> 24));
    }
    if(ui->HEAD_N->currentIndex() >= 2)
    {
        HEAD_TX.append((char)(new_value >> 16));
    }
    if(ui->HEAD_N->currentIndex() >= 3)
    {
        HEAD_TX.append((char)(new_value >> 8));
    }
    if(ui->HEAD_N->currentIndex() >= 4)
    {
        HEAD_TX.append((char)(new_value >> 0));
    }

    ui->HEAD_TX->setText(QByteAray_To_QString(HEAD_TX).toUpper());
}

void SI4432_Settings_Form::setHEAD_RXToUI(unsigned int new_value)
{
    QByteArray HEAD_RX;

    if(ui->HEAD_N->currentIndex() >= 1)
    {
        HEAD_RX.append((char)(new_value >> 24));
    }
    if(ui->HEAD_N->currentIndex() >= 2)
    {
        HEAD_RX.append((char)(new_value >> 16));
    }
    if(ui->HEAD_N->currentIndex() >= 3)
    {
        HEAD_RX.append((char)(new_value >> 8));
    }
    if(ui->HEAD_N->currentIndex() >= 4)
    {
        HEAD_RX.append((char)(new_value >> 0));
    }

    ui->HEAD_RX->setText(QByteAray_To_QString(HEAD_RX).toUpper());
}

void SI4432_Settings_Form::on_CLOAD_textEdited(const QString &arg1)
{
    ui->CLOAD->setStyleSheet(Background_Red);

    if (arg1.length() > 2)
    {
        QString arg;
        arg.append(arg1.data(),2);
        ui->CLOAD->setText(arg);
    }
    int pos = 0;
    QRegExp cload_RegExp = QRegExp("([0-9A-Fa-f]){2,2}");

    if (cload_RegExp.indexIn(arg1,pos) != -1)
    {
        ui->CLOAD->setStyleSheet(Background_White);
        QByteArray cload_barr = QString_To_QByteAray(arg1, false, NULL);

        setSI4432_CLOAD(&OUT_SI4432_Parameters,cload_barr.at(0));
        //CLOAD_CHANGED(cload_barr.at(0),setSI4432_Property_From_Form);
    }
}

void SI4432_Settings_Form::setCLOADToUI(unsigned char new_value)
{
    QByteArray cload_barr; cload_barr.append(new_value);

    ui->CLOAD->setText(QByteAray_To_QString(cload_barr).toUpper());
}

void SI4432_Settings_Form::setCLOAD_PFToUI(unsigned int new_value)
{
    ui->CLOAD_PF->setText(QString::number((double)(new_value)/10));
}

void SI4432_Settings_Form::setRXOSRToUI(unsigned int new_value)
{
    ui->RXOSR->setText(QString::number(new_value));
}

void SI4432_Settings_Form::setNCOFFToUI(unsigned int new_value)
{
    ui->NCOFF->setText(QString::number(new_value));
}

void SI4432_Settings_Form::setCRGAINToUI(unsigned int new_value)
{
    ui->CRGAIN->setText(QString::number(new_value));
}

void SI4432_Settings_Form::setNdecToUI(unsigned char new_value)
{
    ui->ndec->setText(QString::number(new_value));
}

void SI4432_Settings_Form::setDwn3ToUI(unsigned char new_value)
{
    ui->dwn3->setText(QString::number(new_value));
}

void SI4432_Settings_Form::setFilsetToUI(unsigned char new_value)
{
    ui->filset->setText(QString::number(new_value));
}
