#include "si4432class.h"
#include <math.h>

SI4432Class::SI4432Class(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    //this->ui = ui;

    unsigned char HD[4]    = {'M','D','R','F'};

    SI4432_Parameters = new RF_Config_struct;
    RF_RegRead        = new RF_RegRead_struct;

    RF22_SET_MT(1);
    RF22_SET_PA(7);
    RF22_SET_DivDR(1);
    RF22_SET_TXDR(10066);
    RF22_SET_hb(0);
    RF22_SET_FC(19);
    RF22_SET_NFREQ(433920);
    RF22_SET_Fo(20);
    RF22_SET_Fd(31);
    RF22_SET_IFBW(38);
    RF22_SET_HC(4);
    RF22_SET_SWC(1);

    SI4432_Parameters->RF_SYNCH_WORD                    = 0x2DD40000;

    SI4432_Parameters->RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    SI4432_Parameters->RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    RF22_SET_CLOAD (0xB5);

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}
SI4432Class::SI4432Class(QObject *parent) : QObject(parent)
{
    unsigned char HD[4]    = {'M','D','R','F'};

    SI4432_Parameters = new RF_Config_struct;
    RF_RegRead        = new RF_RegRead_struct;

    RF22_SET_MT(1);
    RF22_SET_PA(7);
    RF22_SET_DivDR(1);
    RF22_SET_TXDR(10066);
    RF22_SET_hb(0);
    RF22_SET_FC(19);
    RF22_SET_NFREQ(433920);
    RF22_SET_Fo(20);
    RF22_SET_Fd(31);
    RF22_SET_IFBW(38);
    RF22_SET_HC(4);
    RF22_SET_SWC(1);

    SI4432_Parameters->RF_SYNCH_WORD                    = 0x2DD40000;

    SI4432_Parameters->RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    SI4432_Parameters->RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    RF22_SET_CLOAD (0xB5);

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}

RF_Config_struct*        SI4432Class::aSI4432_RF_Config_struct(void)
{
    return SI4432_Parameters;
}
RF_RegRead_struct*       SI4432Class::aSI4432_RF_RegRead_struct(void)
{
    return RF_RegRead;
}

void           SI4432Class::REFRASH_UI_DATA(void)
{
    this->RF22_SET_MT(RF22_GET_MT());
    this->RF22_SET_PA(RF22_GET_PA());
    this->RF22_SET_DivDR(RF22_GET_DivDR());
    this->RF22_SET_TXDR(RF22_GET_TXDR());
    this->RF22_SET_NFREQ(SI4432_Parameters->RF_NOM_FREQUENC);
    this->RF22_SET_hb(RF22_GET_hb());
    this->RF22_SET_FC(RF22_GET_FC());
    this->RF22_SET_Fo(RF22_GET_Fo());
    this->RF22_SET_Fd(RF22_GET_Fd());
    this->RF22_SET_IFBW(RF22_GET_IFBW());
    this->RF22_SET_HC(RF22_GET_HC());
    this->RF22_SET_SWC(RF22_GET_SWC());
    //SI4432_Parameters->RF_SYNCH_WORD                    = 0x2DD40000;

    //SI4432_Parameters->RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    //SI4432_Parameters->RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    RF22_SET_CLOAD (RF22_GET_CLOAD());

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}

void           SI4432Class::RF22_SET_TXDR  (unsigned short TXDR)
{
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~0xFFFF;
    this->SI4432_Parameters->RF_CONF_REG_1.reg |= (TXDR & 0xFFFF);
    //this->ui->DR->setValue(RF22_GET_TXDR());
    double n = pow(10,6)/pow(2,16+5*RF22_GET_DivDR())*(TXDR & 0xFFFF);
    //this->ui->DR_BPS->setText(QString::number(n));
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}
unsigned short   SI4432Class::RF22_GET_TXDR  (void)
{
    unsigned short result = SI4432_Parameters->RF_CONF_REG_1.reg & 0xFFFF;
    return result;
}
void           SI4432Class::RF22_SET_FC    (unsigned char FC)
{
    if (FC > 23)
    {
        FC  = 23;
    }
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1F) << 16);
    this->SI4432_Parameters->RF_CONF_REG_1.reg |=  ((unsigned int)(FC & 0x1F) << 16);

    //this->ui->FCAR->setCurrentIndex(RF22_GET_FC());

    unsigned int min_car = (240000 + RF22_GET_FC()*10000)*(1 + RF22_GET_hb());
    unsigned int max_car = min_car + 10000*(1+RF22_GET_hb());
    unsigned int fnom    = this->RF22_GET_NFREQ ();
    //unsigned int current_dev = fnom - ui->FNOM->minimum()*1000;
    //this->ui->FNOM->setMinimum(min_car/1000);
    //this->ui->FNOM->setMaximum((max_car-1)/1000);
    if ((fnom >= max_car)||(fnom < min_car))
    {
    //    this->RF22_SET_NFREQ (min_car+(current_dev*(1 + RF22_GET_hb())));
    }

}
unsigned char  SI4432Class::RF22_GET_FC    (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_1.reg >> 16) & 0x1F;
    return result;
}
void           SI4432Class::RF22_SET_hb    (unsigned char hb)
{
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 21);
    this->SI4432_Parameters->RF_CONF_REG_1.reg |=  ((unsigned int)(hb & 0x1) << 21);
    //int curr_index = ui->FCAR->currentIndex();
    /*
    if (this->RF22_GET_hb() == 0)
    {
        this->ui->FX2->setChecked(false);
        this->ui->FCAR->clear();
        this->ui->FCAR->addItem("240-249,99");
        this->ui->FCAR->addItem("250-259,99");
        this->ui->FCAR->addItem("260-269,99");
        this->ui->FCAR->addItem("270-279,99");
        this->ui->FCAR->addItem("280-289,99");
        this->ui->FCAR->addItem("290-299,99");
        this->ui->FCAR->addItem("300-309,99");
        this->ui->FCAR->addItem("310-319,99");
        this->ui->FCAR->addItem("320-329,99");
        this->ui->FCAR->addItem("330-339,99");
        this->ui->FCAR->addItem("340-349,99");
        this->ui->FCAR->addItem("350-359,99");
        this->ui->FCAR->addItem("360-369,99");
        this->ui->FCAR->addItem("370-379,99");
        this->ui->FCAR->addItem("380-389,99");
        this->ui->FCAR->addItem("390-399,99");
        this->ui->FCAR->addItem("400-409,99");
        this->ui->FCAR->addItem("410-419,99");
        this->ui->FCAR->addItem("420-429,99");
        this->ui->FCAR->addItem("430-439,99");
        this->ui->FCAR->addItem("440-449,99");
        this->ui->FCAR->addItem("450-459,99");
        this->ui->FCAR->addItem("460-469,99");
        this->ui->FCAR->addItem("470-479,99");
    }
    else if (this->RF22_GET_hb() == 1)
    {
        this->ui->FX2->setChecked(true);
        this->ui->FCAR->clear();
        this->ui->FCAR->addItem("480-499,99");
        this->ui->FCAR->addItem("500-519,99");
        this->ui->FCAR->addItem("520-539,99");
        this->ui->FCAR->addItem("540-559,99");
        this->ui->FCAR->addItem("560-579,99");
        this->ui->FCAR->addItem("580-599,99");
        this->ui->FCAR->addItem("600-619,99");
        this->ui->FCAR->addItem("620-639,99");
        this->ui->FCAR->addItem("640-659,99");
        this->ui->FCAR->addItem("660-679,99");
        this->ui->FCAR->addItem("680-699,99");
        this->ui->FCAR->addItem("700-719,99");
        this->ui->FCAR->addItem("720-739,99");
        this->ui->FCAR->addItem("740-759,99");
        this->ui->FCAR->addItem("760-779,99");
        this->ui->FCAR->addItem("780-799,99");
        this->ui->FCAR->addItem("800-819,99");
        this->ui->FCAR->addItem("820-839,99");
        this->ui->FCAR->addItem("840-859,99");
        this->ui->FCAR->addItem("860-879,99");
        this->ui->FCAR->addItem("880-899,99");
        this->ui->FCAR->addItem("900-919,99");
        this->ui->FCAR->addItem("920-939,99");
        this->ui->FCAR->addItem("940-960,00");
    }
    */
    //this->ui->FCAR->setCurrentIndex(curr_index);
    //this->RF22_SET_FC(curr_index);
    double f_ofset = 0.15625*(RF22_GET_hb() + 1)*RF22_GET_Fo();
    //this->ui->FOFF_KHZ->setText(QString::number(f_ofset));
}
unsigned char  SI4432Class::RF22_GET_hb    (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_1.reg >> 21) & 0x1;
    return result;
}
void           SI4432Class::RF22_SET_DivDR (unsigned char DivDR)
{
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 22);
    this->SI4432_Parameters->RF_CONF_REG_1.reg |=  ((unsigned int)(DivDR & 0x1) << 22);
    if (this->RF22_GET_DivDR() == 0)
    {
    //    this->ui->DIV_DR->setChecked(false);
    }
    else if (this->RF22_GET_DivDR() == 1)
    {
    //    this->ui->DIV_DR->setChecked(true);
    }
    this->RF22_SET_TXDR  (this->RF22_GET_TXDR());
}
unsigned char  SI4432Class::RF22_GET_DivDR (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_1.reg >> 22) & 0x1;
    return result;
}
void           SI4432Class::RF22_SET_PA    (unsigned char PA)
{
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~((unsigned int)(0x7) << 23);
    this->SI4432_Parameters->RF_CONF_REG_1.reg |=  ((unsigned int)(PA & 0x7) << 23);
    //this->ui->PA->setCurrentIndex(this->RF22_GET_PA());
}
unsigned char  SI4432Class::RF22_GET_PA    (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_1.reg >> 23) & 0x7;
    return result;
}
void           SI4432Class::RF22_SET_MT    (unsigned char MT)
{
    this->SI4432_Parameters->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 26);
    this->SI4432_Parameters->RF_CONF_REG_1.reg |=  ((unsigned int)(MT & 0x1) << 26);
   // this->ui->MT->setCurrentIndex(this->RF22_GET_MT());
}
unsigned char  SI4432Class::RF22_GET_MT    (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_1.reg >> 26)&0x1;
    return result;
}
void           SI4432Class::RF22_SET_Fo    (signed  short Fo)
{
    this->SI4432_Parameters->RF_CONF_REG_2.reg &= ~(0x3FF);
    this->SI4432_Parameters->RF_CONF_REG_2.reg |=  (unsigned int)(Fo & 0x3FF);
    //this->ui->FOFF->setValue(this->RF22_GET_Fo());
    double f_ofset = 0.15625*(this->RF22_GET_hb() + 1)*this->RF22_GET_Fo();
    //this->ui->FOFF_KHZ->setText(QString::number(f_ofset));
}
signed  short  SI4432Class::RF22_GET_Fo    (void)
{
    signed short result = this->SI4432_Parameters->RF_CONF_REG_2.reg & 0x3FF;
    if (result & (1 << 9))
    {
        result |= 0xFC00;
    }
    return result;
}
void           SI4432Class::RF22_SET_IFBW  (unsigned char IFBW)
{
    this->SI4432_Parameters->RF_CONF_REG_2.reg &= ~((unsigned int)(0x3F) << 10);
    this->SI4432_Parameters->RF_CONF_REG_2.reg |=  ((unsigned int)(IFBW & 0x3F) << 10);
    //this->ui->BW->setCurrentIndex(RF22_GET_IFBW());
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}
unsigned char  SI4432Class::RF22_GET_IFBW  (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_2.reg >> 10) & 0x3F;
    return result;
}
void           SI4432Class::RF22_SET_Fd    (unsigned short Fd)
{
    this->SI4432_Parameters->RF_CONF_REG_2.reg &= ~((unsigned int)(0x1FF) << 16);
    this->SI4432_Parameters->RF_CONF_REG_2.reg |= ((unsigned int)(Fd & 0x1FF) << 16);
    //this->ui->DV->setValue(this->RF22_GET_Fd());
    double dev = this->RF22_GET_Fd()*625;
    //this->ui->DV_HZ->setText(QString::number(dev));
    this->RF22_Rb_calc(SI4432_Parameters);
    this->RF22_IFBW_bits(SI4432_Parameters);
    this->RF22_RXOSR_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_NCOFF_calc(SI4432_Parameters);  // !!! без манчестерского кода !!!
    this->RF22_CRGAIN_calc(SI4432_Parameters); // !!! без манчестерского кода !!!
}
unsigned short SI4432Class::RF22_GET_Fd    (void)
{
    unsigned short result = (SI4432_Parameters->RF_CONF_REG_2.reg >> 16) & 0x1FF;
    return result;
}
void           SI4432Class::RF22_SET_HC    (unsigned char HC)
{
    this->SI4432_Parameters->RF_CONF_REG_2.reg &= ~((unsigned int)(0xF) << 25);
    this->SI4432_Parameters->RF_CONF_REG_2.reg |= ((unsigned int)(HC & 0xF) << 25);
    //this->ui->HEAD_N->setCurrentIndex(this->RF22_GET_HC());
}
unsigned char  SI4432Class::RF22_GET_HC    (void)
{
    unsigned short result = (SI4432_Parameters->RF_CONF_REG_2.reg >> 25) & 0xF;
    return result;
}
void           SI4432Class::RF22_SET_SWC   (unsigned char SWC)
{
    this->SI4432_Parameters->RF_CONF_REG_2.reg &= ~((unsigned int)(0x7) << 29);
    this->SI4432_Parameters->RF_CONF_REG_2.reg |= ((unsigned int)(SWC & 0x7) << 29);
    //this->ui->SNW_N->setCurrentIndex(this->RF22_GET_SWC());
}
unsigned char  SI4432Class::RF22_GET_SWC   (void)
{
    unsigned short result = (SI4432_Parameters->RF_CONF_REG_2.reg >> 29) & 0x7;
    return result;
}
void           SI4432Class::RF22_SET_NFREQ (unsigned int NFREQ)
{
    this->SI4432_Parameters->RF_NOM_FREQUENC = NFREQ;
    unsigned int val = this->SI4432_Parameters->RF_NOM_FREQUENC;
    //this->ui->FNOM->setValue((double)(val)/1000);
}
unsigned int   SI4432Class::RF22_GET_NFREQ (void)
{
    //double val = this->ui->FNOM->value() + 0.0005f;
    //val = val*1000;
    //this->SI4432_Parameters->RF_NOM_FREQUENC = (int)(val);
    return this->SI4432_Parameters->RF_NOM_FREQUENC;
}
void           SI4432Class::RF22_SET_CLOAD (unsigned char CLOAD)
{
    this->SI4432_Parameters->RF_CONF_REG_3.reg &= ~0xFF;
    this->SI4432_Parameters->RF_CONF_REG_3.reg |= CLOAD & 0xFF;
    RF22_CLOAD_calc(SI4432_Parameters);
    //this->ui->CLOAD_PF->setText(QString::number((double)(this->SI4432_Parameters->RF_COscill_CLoad)/10));
}
unsigned char  SI4432Class::RF22_GET_CLOAD (void)
{
    unsigned char result = (SI4432_Parameters->RF_CONF_REG_3.reg) & 0xFF;
    return result;
}

void SI4432Class::RF22_CLOAD_calc(struct RF_Config_struct *config_structur)
{
    unsigned int result = 0;
    result = (unsigned int)(config_structur->RF_CONF_REG_3.Feld.xcl) * 85;
    result = result + (unsigned int)(config_structur->RF_CONF_REG_3.Feld.xtalshift) * 3700;
    result = result + 1800;
    result = result / 100;
    config_structur->RF_COscill_CLoad = result;
}
void SI4432Class::RF22_Rb_calc(struct RF_Config_struct *config_structur)
{
    int result = 0;

    unsigned int pow2 = (unsigned int)(1 << (16+5*this->RF22_GET_DivDR()));
    float TXDR_6 = RF22_GET_TXDR();
    TXDR_6 /= pow2;

    result = (unsigned int)(TXDR_6*1000000);

    config_structur->Rb = result;
}

void SI4432Class::RF22_RXOSR_calc(struct RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = 500*(1+2*config_structur->dwn3);
    res = res/config_structur->Rb;
    res *= 1000;

    if (config_structur->ndec >= 3)
    {
        res /= (unsigned int)(1 << (config_structur->ndec-3));
    }
    else if (config_structur->ndec == 2)
    {
        res /= 0.5f;
    }
    else if (config_structur->ndec == 1)
    {
        res /= 0.25f;
    }
    else if (config_structur->ndec == 0)
    {
        res /= 0.125f;
    }

    result = (unsigned int)(res);

    config_structur->RXOSR = result;
    //this->ui->RXOSR->setText(QString::number(config_structur->RXOSR));
}
void SI4432Class::RF22_NCOFF_calc(struct RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = config_structur->Rb;
    res /= (500*(1+2*config_structur->dwn3));

    res *= (unsigned int)(1 << (config_structur->ndec+20));

    res /= 1000;
    result = (unsigned int)(res);

    config_structur->NCOFF = result;
    //this->ui->NCOFF->setText(QString::number(config_structur->NCOFF));
}
void SI4432Class::RF22_CRGAIN_calc(struct RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = config_structur->Rb;
    res /= config_structur->RXOSR;
    res /= RF22_GET_Fd();
    res *= (unsigned int)(1 << 16);
    res /= 1000;

    result = 2+(unsigned int)(res);

    config_structur->CRGAIN = result;
    //this->ui->CRGAIN->setText(QString::number(config_structur->CRGAIN));
}
void SI4432Class::RF22_IFBW_calc(struct RF_Config_struct *config_structur)
{
    volatile int ModBW = (2*RF22_GET_Fd()*625+config_structur->Rb)*2;

    if      ((ModBW >= 0)    &&(ModBW <= 2600))  {RF22_SET_IFBW(0);}
    else if ((ModBW > 2600)  &&(ModBW <= 2800))  {RF22_SET_IFBW(1);}
    else if ((ModBW > 2800)  &&(ModBW <= 3100))  {RF22_SET_IFBW(2);}
    else if ((ModBW > 3100)  &&(ModBW <= 3200))  {RF22_SET_IFBW(3);}
    else if ((ModBW > 3200)  &&(ModBW <= 3700))  {RF22_SET_IFBW(4);}
    else if ((ModBW > 3700)  &&(ModBW <= 4200))  {RF22_SET_IFBW(5);}
    else if ((ModBW > 3400)  &&(ModBW <= 4500))  {RF22_SET_IFBW(6);}
    else if ((ModBW > 4500)  &&(ModBW <= 4900))  {RF22_SET_IFBW(7);}
    else if ((ModBW > 4900)  &&(ModBW <= 5400))  {RF22_SET_IFBW(8);}
    else if ((ModBW > 5400)  &&(ModBW <= 5900))  {RF22_SET_IFBW(9);}
    else if ((ModBW > 5900)  &&(ModBW <= 6100))  {RF22_SET_IFBW(10);}
    else if ((ModBW > 6100)  &&(ModBW <= 7200))  {RF22_SET_IFBW(11);}
    else if ((ModBW > 7200)  &&(ModBW <= 8200))  {RF22_SET_IFBW(12);}
    else if ((ModBW > 8200)  &&(ModBW <= 8800))  {RF22_SET_IFBW(13);}
    else if ((ModBW > 8800)  &&(ModBW <= 9500))  {RF22_SET_IFBW(14);}
    else if ((ModBW > 9500)  &&(ModBW <= 10600)) {RF22_SET_IFBW(15);}
    else if ((ModBW > 10600) &&(ModBW <= 11500)) {RF22_SET_IFBW(16);}
    else if ((ModBW > 11500) &&(ModBW <= 12100)) {RF22_SET_IFBW(17);}
    else if ((ModBW > 12100) &&(ModBW <= 14200)) {RF22_SET_IFBW(18);}
    else if ((ModBW > 14200) &&(ModBW <= 16200)) {RF22_SET_IFBW(19);}
    else if ((ModBW > 16200) &&(ModBW <= 17500)) {RF22_SET_IFBW(20);}
    else if ((ModBW > 17500) &&(ModBW <= 18900)) {RF22_SET_IFBW(21);}
    else if ((ModBW > 18900) &&(ModBW <= 21000)) {RF22_SET_IFBW(22);}
    else if ((ModBW > 21000) &&(ModBW <= 22700)) {RF22_SET_IFBW(23);}
    else if ((ModBW > 22700) &&(ModBW <= 24000)) {RF22_SET_IFBW(24);}
    else if ((ModBW > 24000) &&(ModBW <= 28200)) {RF22_SET_IFBW(25);}
    else if ((ModBW > 28200) &&(ModBW <= 32200)) {RF22_SET_IFBW(26);}
    else if ((ModBW > 32200) &&(ModBW <= 34700)) {RF22_SET_IFBW(27);}
    else if ((ModBW > 34700) &&(ModBW <= 37700)) {RF22_SET_IFBW(28);}
    else if ((ModBW > 37700) &&(ModBW <= 41700)) {RF22_SET_IFBW(29);}
    else if ((ModBW > 41700) &&(ModBW <= 45200)) {RF22_SET_IFBW(30);}
    else if ((ModBW > 45200) &&(ModBW <= 47900)) {RF22_SET_IFBW(31);}
    else if ((ModBW > 47900) &&(ModBW <= 56200)) {RF22_SET_IFBW(32);}
    else if ((ModBW > 56200) &&(ModBW <= 64100)) {RF22_SET_IFBW(33);}
    else if ((ModBW > 64100) &&(ModBW <= 69200)) {RF22_SET_IFBW(34);}
    else if ((ModBW > 69200) &&(ModBW <= 75200)) {RF22_SET_IFBW(35);}
    else if ((ModBW > 75200) &&(ModBW <= 83200)) {RF22_SET_IFBW(36);}
    else if ((ModBW > 83200) &&(ModBW <= 90000)) {RF22_SET_IFBW(37);}
    else if ((ModBW > 90000) &&(ModBW <= 95300)) {RF22_SET_IFBW(38);}
    else if ((ModBW > 95300) &&(ModBW <= 112100)){RF22_SET_IFBW(39);}
    else if ((ModBW > 112100)&&(ModBW <= 127900)){RF22_SET_IFBW(40);}
    else if ((ModBW > 127900)&&(ModBW <= 137900)){RF22_SET_IFBW(41);}
    else if ((ModBW > 137900)&&(ModBW <= 142800)){RF22_SET_IFBW(42);}
    else if ((ModBW > 142800)&&(ModBW <= 167800)){RF22_SET_IFBW(43);}
    else if ((ModBW > 167800)&&(ModBW <= 181100)){RF22_SET_IFBW(44);}
    else if ((ModBW > 181100)&&(ModBW <= 191500)){RF22_SET_IFBW(45);}
    else if ((ModBW > 191500)&&(ModBW <= 225100)){RF22_SET_IFBW(46);}
    else if ((ModBW > 225100)&&(ModBW <= 248800)){RF22_SET_IFBW(47);}
    else if ((ModBW > 248800)&&(ModBW <= 269300)){RF22_SET_IFBW(48);}
    else if ((ModBW > 269300)&&(ModBW <= 284900)){RF22_SET_IFBW(49);}
    else if ((ModBW > 284900)&&(ModBW <= 335500)){RF22_SET_IFBW(50);}
    else if ((ModBW > 335500)&&(ModBW <= 361800)){RF22_SET_IFBW(51);}
    else if ((ModBW > 361800)&&(ModBW <= 420200)){RF22_SET_IFBW(52);}
    else if ((ModBW > 420200)&&(ModBW <= 468400)){RF22_SET_IFBW(53);}
    else if ((ModBW > 468400)&&(ModBW <= 518800)){RF22_SET_IFBW(54);}
    else if ((ModBW > 518800)&&(ModBW <= 577000)){RF22_SET_IFBW(55);}
    else if (ModBW > 577000)                     {RF22_SET_IFBW(56);}
}
    //config_structur->RF_CONF_REG_2.Feld.IFBW += 1;
void SI4432Class::RF22_IFBW_bits(struct RF_Config_struct *config_structur)
{
    // ПОЛОСОВОЙ ФИЛЬТР ===============================================================
    // ================================================================================
     switch (RF22_GET_IFBW())
     {
         case 0:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 1; break; //2.6
         case 1:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 2; break; //2.8
         case 2:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 3; break; //3.1
         case 3:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 4; break; //3.2
         case 4:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 5; break; //3.7
         case 5:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 6; break; //4.2
         case 6:  config_structur->ndec = 5; config_structur->dwn3 = 0; config_structur->filset = 7; break; //4.5
         case 7:  config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 1; break; //4.9
         case 8:  config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 2; break; //5.4
         case 9:  config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 3; break; //5.9
         case 10: config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 4; break; //6.1
         case 11: config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 5; break; //7.2
         case 12: config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 6; break; //8.2
         case 13: config_structur->ndec = 4; config_structur->dwn3 = 0; config_structur->filset = 7; break; //8.8
         case 14: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 1; break; //9.5
         case 15: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 2; break; //10.6
         case 16: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 3; break; //11.5
         case 17: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 4; break; //12.1
         case 18: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 5; break; //14.2
         case 19: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 6; break; //16.2
         case 20: config_structur->ndec = 3; config_structur->dwn3 = 0; config_structur->filset = 7; break; //17.5
         case 21: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 1; break; //18.9
         case 22: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 2; break; //21.0
         case 23: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 3; break; //22.7
         case 24: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 4; break; //24.0
         case 25: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 5; break; //28.2
         case 26: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 6; break; //32.2
         case 27: config_structur->ndec = 2; config_structur->dwn3 = 0; config_structur->filset = 7; break; //34.7
         case 28: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 1; break; //37.7
         case 29: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 2; break; //41.7
         case 30: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 3; break; //45.2
         case 31: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 4; break; //47.9
         case 32: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 5; break; //56.2
         case 33: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 6; break; //64.1
         case 34: config_structur->ndec = 1; config_structur->dwn3 = 0; config_structur->filset = 7; break; //69.2
         case 35: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 1; break; //75.2
         case 36: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 2; break; //83.2
         case 37: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 3; break; //90.0
         case 38: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 4; break; //95.3
         case 39: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 5; break; //112.1
         case 40: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 6; break; //127.9
         case 41: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 7; break; //137.9
         case 42: config_structur->ndec = 1; config_structur->dwn3 = 1; config_structur->filset = 4; break; //142.8
         case 43: config_structur->ndec = 1; config_structur->dwn3 = 1; config_structur->filset = 5; break; //167.8
         case 44: config_structur->ndec = 1; config_structur->dwn3 = 1; config_structur->filset = 9; break; //181.1
         case 45: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 15; break;//191.5
         case 46: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 1; break; //225.1
         case 47: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 2; break; //248.8
         case 48: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 3; break; //269.3
         case 49: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 4; break; //284.9
         case 50: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 8; break; //335.5
         case 51: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 9; break; //361.8
         case 52: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 10; break;//420.2
         case 53: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 11; break;//468.4
         case 54: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 12; break;//518.8
         case 55: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 13; break;//577.0
         case 56: config_structur->ndec = 0; config_structur->dwn3 = 1; config_structur->filset = 14; break;//620.7
         default: config_structur->ndec = 0; config_structur->dwn3 = 0; config_structur->filset = 4; break; //95.3
     }
     //ui->ndec->setText(QString::number(config_structur->ndec));
     //ui->dwn3->setText(QString::number(config_structur->dwn3));
     //ui->filset->setText(QString::number(config_structur->filset));
}
