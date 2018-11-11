#include "si4432class.h"
#include <math.h>

SI4432Class::SI4432Class(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    //this->ui = ui;

    unsigned char HD[4]    = {0,0,0,0};

    setSI4432_MT(&IN_SI4432_Parameters,   0);
    setSI4432_PA(&IN_SI4432_Parameters,   0);
    setSI4432_DivDR(&IN_SI4432_Parameters,0);
    setSI4432_TXDR(&IN_SI4432_Parameters, 0);
    setSI4432_hb(&IN_SI4432_Parameters,   0);
    setSI4432_FC(&IN_SI4432_Parameters,   0);
    setSI4432_NFREQ(&IN_SI4432_Parameters,0);
    setSI4432_Fo(&IN_SI4432_Parameters,   0);
    setSI4432_Fd(&IN_SI4432_Parameters,   0);
    setSI4432_IFBW(&IN_SI4432_Parameters, 0);
    setSI4432_HC(&IN_SI4432_Parameters,   0);
    setSI4432_SWC(&IN_SI4432_Parameters,  0);

    IN_SI4432_Parameters.RF_SYNCH_WORD                    = 0x00000000;

    IN_SI4432_Parameters.RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    IN_SI4432_Parameters.RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    setSI4432_CLOAD (&IN_SI4432_Parameters, 0x00);

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    calcSI4432_Rb(&IN_SI4432_Parameters);
    calcSI4432_IFBW(&IN_SI4432_Parameters);
    calcSI4432_IFBW_bits(&IN_SI4432_Parameters);
    calcSI4432_RXOSR(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&IN_SI4432_Parameters); // !!! без манчестерского кода !!!
}
SI4432Class::SI4432Class(QObject *parent) : QObject(parent)
{
    unsigned char HD[4]    = {0,0,0,0};

    setSI4432_MT(&IN_SI4432_Parameters,   0);
    setSI4432_PA(&IN_SI4432_Parameters,   0);
    setSI4432_DivDR(&IN_SI4432_Parameters,0);
    setSI4432_TXDR(&IN_SI4432_Parameters, 0);
    setSI4432_hb(&IN_SI4432_Parameters,   0);
    setSI4432_FC(&IN_SI4432_Parameters,   0);
    setSI4432_NFREQ(&IN_SI4432_Parameters,0);
    setSI4432_Fo(&IN_SI4432_Parameters,   0);
    setSI4432_Fd(&IN_SI4432_Parameters,   0);
    setSI4432_IFBW(&IN_SI4432_Parameters, 0);
    setSI4432_HC(&IN_SI4432_Parameters,   0);
    setSI4432_SWC(&IN_SI4432_Parameters,  0);

    IN_SI4432_Parameters.RF_SYNCH_WORD                    = 0x00000000;

    IN_SI4432_Parameters.RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    IN_SI4432_Parameters.RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    setSI4432_CLOAD (&IN_SI4432_Parameters, 0x00);

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    calcSI4432_Rb(&IN_SI4432_Parameters);
    calcSI4432_IFBW(&IN_SI4432_Parameters);
    calcSI4432_IFBW_bits(&IN_SI4432_Parameters);
    calcSI4432_RXOSR(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&IN_SI4432_Parameters); // !!! без манчестерского кода !!!
}

RF_Config_struct  SI4432Class::getIN_SI4432_RF_Config(void)
{
    emit IN_SI4432_RF_Config (IN_SI4432_Parameters);
    return IN_SI4432_Parameters;
}

void              SI4432Class::setIN_SI4432_RF_Config(RF_Config_struct new_data)
{
    IN_SI4432_Parameters = new_data;

    calcSI4432_Rb(&IN_SI4432_Parameters);
    calcSI4432_IFBW_bits(&IN_SI4432_Parameters);
    calcSI4432_RXOSR(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(&IN_SI4432_Parameters);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(&IN_SI4432_Parameters); // !!! без манчестерского кода !!!

    emit IN_SI4432_RF_Config (IN_SI4432_Parameters);
}

RF_Config_struct  SI4432Class::getOUT_SI4432_RF_Config(void)
{
    return OUT_SI4432_Parameters;
}

void              SI4432Class::setOUT_SI4432_RF_Config(RF_Config_struct new_data)
{
    OUT_SI4432_Parameters = new_data;
}

RF_RegRead_struct SI4432Class::getSI4432_RF_RegRead(void)
{
    return SI4432_RegRead;
}
void              SI4432Class::setSI4432_RF_RegRead(RF_RegRead_struct new_data)
{
    SI4432_RegRead = new_data;
}

void            setSI4432_TXDR  (RF_Config_struct *config_structur, unsigned short TXDR)
{
    config_structur->RF_CONF_REG_1.reg &= ~0xFFFF;
    config_structur->RF_CONF_REG_1.reg |= (TXDR & 0xFFFF);

    calcSI4432_Rb(config_structur);
    calcSI4432_IFBW_bits(config_structur);
    calcSI4432_RXOSR(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(config_structur); // !!! без манчестерского кода !!!
}
unsigned short   getSI4432_TXDR  (RF_Config_struct *config_structur)
{
    unsigned short result = config_structur->RF_CONF_REG_1.reg & 0xFFFF;

    return result;
}
void           setSI4432_FC    (RF_Config_struct *config_structur, unsigned char FC)
{
    if (FC > 23)
    {
        FC  = 23;
    }
    config_structur->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1F) << 16);
    config_structur->RF_CONF_REG_1.reg |=  ((unsigned int)(FC & 0x1F) << 16);
}
unsigned char  getSI4432_FC    (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_1.reg >> 16) & 0x1F;

    return result;
}
void           setSI4432_hb    (RF_Config_struct *config_structur, unsigned char hb)
{
    config_structur->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 21);
    config_structur->RF_CONF_REG_1.reg |=  ((unsigned int)(hb & 0x1) << 21);
}
unsigned char  getSI4432_hb    (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_1.reg >> 21) & 0x1;

    return result;
}
void           setSI4432_DivDR (RF_Config_struct *config_structur, unsigned char DivDR)
{
    config_structur->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 22);
    config_structur->RF_CONF_REG_1.reg |=  ((unsigned int)(DivDR & 0x1) << 22);
}
unsigned char  getSI4432_DivDR (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_1.reg >> 22) & 0x1;

    return result;
}
void           setSI4432_PA    (RF_Config_struct *config_structur, unsigned char PA)
{
    config_structur->RF_CONF_REG_1.reg &= ~((unsigned int)(0x7) << 23);
    config_structur->RF_CONF_REG_1.reg |=  ((unsigned int)(PA & 0x7) << 23);
}
unsigned char  getSI4432_PA    (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_1.reg >> 23) & 0x7;

    return result;
}
void           setSI4432_MT    (RF_Config_struct *config_structur, unsigned char MT)
{
    config_structur->RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 26);
    config_structur->RF_CONF_REG_1.reg |=  ((unsigned int)(MT & 0x1) << 26);
}
unsigned char  getSI4432_MT    (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_1.reg >> 26)&0x1;

    return result;
}
void           setSI4432_Fo    (RF_Config_struct *config_structur, signed  short Fo)
{
    config_structur->RF_CONF_REG_2.reg &= ~(0x3FF);
    config_structur->RF_CONF_REG_2.reg |=  (unsigned int)(Fo & 0x3FF);
}
signed  short  getSI4432_Fo    (RF_Config_struct *config_structur)
{
    signed short result = config_structur->RF_CONF_REG_2.reg & 0x3FF;
    if (result & (1 << 9))
    {
        result |= 0xFC00;
    }

    return result;
}
void           setSI4432_IFBW  (RF_Config_struct *config_structur, unsigned char IFBW)
{
    config_structur->RF_CONF_REG_2.reg &= ~((unsigned int)(0x3F) << 10);
    config_structur->RF_CONF_REG_2.reg |=  ((unsigned int)(IFBW & 0x3F) << 10);

    calcSI4432_Rb(config_structur);
    calcSI4432_IFBW_bits(config_structur);
    calcSI4432_RXOSR(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(config_structur); // !!! без манчестерского кода !!!
}
unsigned char  getSI4432_IFBW  (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_2.reg >> 10) & 0x3F;

    return result;
}
void           setSI4432_Fd    (RF_Config_struct *config_structur, unsigned short Fd)
{
    config_structur->RF_CONF_REG_2.reg &= ~((unsigned int)(0x1FF) << 16);
    config_structur->RF_CONF_REG_2.reg |= ((unsigned int)(Fd & 0x1FF) << 16);

    calcSI4432_Rb(config_structur);
    calcSI4432_IFBW_bits(config_structur);
    calcSI4432_RXOSR(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF(config_structur);  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(config_structur); // !!! без манчестерского кода !!!
}
unsigned short getSI4432_Fd    (RF_Config_struct *config_structur)
{
    unsigned short result = (config_structur->RF_CONF_REG_2.reg >> 16) & 0x1FF;

    return result;
}
void           setSI4432_HC    (RF_Config_struct *config_structur, unsigned char HC)
{
    config_structur->RF_CONF_REG_2.reg &= ~((unsigned int)(0xF) << 25);
    config_structur->RF_CONF_REG_2.reg |= ((unsigned int)(HC & 0xF) << 25);
}
unsigned char  getSI4432_HC    (RF_Config_struct *config_structur)
{
    unsigned short result = (config_structur->RF_CONF_REG_2.reg >> 25) & 0xF;

    return result;
}
void           setSI4432_SWC   (RF_Config_struct *config_structur, unsigned char SWC)
{
    config_structur->RF_CONF_REG_2.reg &= ~((unsigned int)(0x7) << 29);
    config_structur->RF_CONF_REG_2.reg |= ((unsigned int)(SWC & 0x7) << 29);
}
unsigned char  getSI4432_SWC   (RF_Config_struct *config_structur)
{
    unsigned short result = (config_structur->RF_CONF_REG_2.reg >> 29) & 0x7;

    return result;
}
void           setSI4432_NFREQ (RF_Config_struct *config_structur, unsigned int NFREQ)
{
    config_structur->RF_NOM_FREQUENC = NFREQ;

}
unsigned int   getSI4432_NFREQ (RF_Config_struct *config_structur)
{
    return config_structur->RF_NOM_FREQUENC;
}
void           setSI4432_CLOAD (RF_Config_struct *config_structur, unsigned char CLOAD)
{
    config_structur->RF_CONF_REG_3.reg &= ~0xFF;
    config_structur->RF_CONF_REG_3.reg |= CLOAD & 0xFF;

    calcSI4432_CLOAD(config_structur);

}
unsigned char  getSI4432_CLOAD (RF_Config_struct *config_structur)
{
    unsigned char result = (config_structur->RF_CONF_REG_3.reg) & 0xFF;

    return result;
}
void calcSI4432_CLOAD(RF_Config_struct *config_structur)
{
    unsigned int result = 0;
    result = (unsigned int)(config_structur->RF_CONF_REG_3.Feld.xcl) * 85;
    result = result + (unsigned int)(config_structur->RF_CONF_REG_3.Feld.xtalshift) * 3700;
    result = result + 1800;
    result = result / 100;
    config_structur->RF_COscill_CLoad = result;

}
void calcSI4432_Rb(RF_Config_struct *config_structur)
{
    int result = 0;

    unsigned int pow2 = (unsigned int)(1 << (16+5*getSI4432_DivDR(config_structur)));
    float TXDR_6 = getSI4432_TXDR(config_structur);
    TXDR_6 /= pow2;

    result = (unsigned int)(TXDR_6*1000000);

    config_structur->Rb = result;

}

void calcSI4432_RXOSR(RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
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

}
void calcSI4432_NCOFF(RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = config_structur->Rb;
    res /= (500*(1+2*config_structur->dwn3));

    res *= (unsigned int)(1 << (config_structur->ndec+20));

    res /= 1000;
    result = (unsigned int)(res);

    config_structur->NCOFF = result;

}
void calcSI4432_CRGAIN(RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = config_structur->Rb;
    res /= config_structur->RXOSR;
    res /= getSI4432_Fd(config_structur);
    res *= (unsigned int)(1 << 16);
    res /= 1000;

    result = 2+(unsigned int)(res);

    config_structur->CRGAIN = result;

}
void calcSI4432_IFBW(RF_Config_struct *config_structur)
{
    volatile int ModBW = (2*getSI4432_Fd(config_structur)*625+config_structur->Rb);

    if      ((ModBW >= 0)    &&(ModBW <= 2600))  {setSI4432_IFBW(config_structur,0);}
    else if ((ModBW > 2600)  &&(ModBW <= 2800))  {setSI4432_IFBW(config_structur,1);}
    else if ((ModBW > 2800)  &&(ModBW <= 3100))  {setSI4432_IFBW(config_structur,2);}
    else if ((ModBW > 3100)  &&(ModBW <= 3200))  {setSI4432_IFBW(config_structur,3);}
    else if ((ModBW > 3200)  &&(ModBW <= 3700))  {setSI4432_IFBW(config_structur,4);}
    else if ((ModBW > 3700)  &&(ModBW <= 4200))  {setSI4432_IFBW(config_structur,5);}
    else if ((ModBW > 3400)  &&(ModBW <= 4500))  {setSI4432_IFBW(config_structur,6);}
    else if ((ModBW > 4500)  &&(ModBW <= 4900))  {setSI4432_IFBW(config_structur,7);}
    else if ((ModBW > 4900)  &&(ModBW <= 5400))  {setSI4432_IFBW(config_structur,8);}
    else if ((ModBW > 5400)  &&(ModBW <= 5900))  {setSI4432_IFBW(config_structur,9);}
    else if ((ModBW > 5900)  &&(ModBW <= 6100))  {setSI4432_IFBW(config_structur,10);}
    else if ((ModBW > 6100)  &&(ModBW <= 7200))  {setSI4432_IFBW(config_structur,11);}
    else if ((ModBW > 7200)  &&(ModBW <= 8200))  {setSI4432_IFBW(config_structur,12);}
    else if ((ModBW > 8200)  &&(ModBW <= 8800))  {setSI4432_IFBW(config_structur,13);}
    else if ((ModBW > 8800)  &&(ModBW <= 9500))  {setSI4432_IFBW(config_structur,14);}
    else if ((ModBW > 9500)  &&(ModBW <= 10600)) {setSI4432_IFBW(config_structur,15);}
    else if ((ModBW > 10600) &&(ModBW <= 11500)) {setSI4432_IFBW(config_structur,16);}
    else if ((ModBW > 11500) &&(ModBW <= 12100)) {setSI4432_IFBW(config_structur,17);}
    else if ((ModBW > 12100) &&(ModBW <= 14200)) {setSI4432_IFBW(config_structur,18);}
    else if ((ModBW > 14200) &&(ModBW <= 16200)) {setSI4432_IFBW(config_structur,19);}
    else if ((ModBW > 16200) &&(ModBW <= 17500)) {setSI4432_IFBW(config_structur,20);}
    else if ((ModBW > 17500) &&(ModBW <= 18900)) {setSI4432_IFBW(config_structur,21);}
    else if ((ModBW > 18900) &&(ModBW <= 21000)) {setSI4432_IFBW(config_structur,22);}
    else if ((ModBW > 21000) &&(ModBW <= 22700)) {setSI4432_IFBW(config_structur,23);}
    else if ((ModBW > 22700) &&(ModBW <= 24000)) {setSI4432_IFBW(config_structur,24);}
    else if ((ModBW > 24000) &&(ModBW <= 28200)) {setSI4432_IFBW(config_structur,25);}
    else if ((ModBW > 28200) &&(ModBW <= 32200)) {setSI4432_IFBW(config_structur,26);}
    else if ((ModBW > 32200) &&(ModBW <= 34700)) {setSI4432_IFBW(config_structur,27);}
    else if ((ModBW > 34700) &&(ModBW <= 37700)) {setSI4432_IFBW(config_structur,28);}
    else if ((ModBW > 37700) &&(ModBW <= 41700)) {setSI4432_IFBW(config_structur,29);}
    else if ((ModBW > 41700) &&(ModBW <= 45200)) {setSI4432_IFBW(config_structur,30);}
    else if ((ModBW > 45200) &&(ModBW <= 47900)) {setSI4432_IFBW(config_structur,31);}
    else if ((ModBW > 47900) &&(ModBW <= 56200)) {setSI4432_IFBW(config_structur,32);}
    else if ((ModBW > 56200) &&(ModBW <= 64100)) {setSI4432_IFBW(config_structur,33);}
    else if ((ModBW > 64100) &&(ModBW <= 69200)) {setSI4432_IFBW(config_structur,34);}
    else if ((ModBW > 69200) &&(ModBW <= 75200)) {setSI4432_IFBW(config_structur,35);}
    else if ((ModBW > 75200) &&(ModBW <= 83200)) {setSI4432_IFBW(config_structur,36);}
    else if ((ModBW > 83200) &&(ModBW <= 90000)) {setSI4432_IFBW(config_structur,37);}
    else if ((ModBW > 90000) &&(ModBW <= 95300)) {setSI4432_IFBW(config_structur,38);}
    else if ((ModBW > 95300) &&(ModBW <= 112100)){setSI4432_IFBW(config_structur,39);}
    else if ((ModBW > 112100)&&(ModBW <= 127900)){setSI4432_IFBW(config_structur,40);}
    else if ((ModBW > 127900)&&(ModBW <= 137900)){setSI4432_IFBW(config_structur,41);}
    else if ((ModBW > 137900)&&(ModBW <= 142800)){setSI4432_IFBW(config_structur,42);}
    else if ((ModBW > 142800)&&(ModBW <= 167800)){setSI4432_IFBW(config_structur,43);}
    else if ((ModBW > 167800)&&(ModBW <= 181100)){setSI4432_IFBW(config_structur,44);}
    else if ((ModBW > 181100)&&(ModBW <= 191500)){setSI4432_IFBW(config_structur,45);}
    else if ((ModBW > 191500)&&(ModBW <= 225100)){setSI4432_IFBW(config_structur,46);}
    else if ((ModBW > 225100)&&(ModBW <= 248800)){setSI4432_IFBW(config_structur,47);}
    else if ((ModBW > 248800)&&(ModBW <= 269300)){setSI4432_IFBW(config_structur,48);}
    else if ((ModBW > 269300)&&(ModBW <= 284900)){setSI4432_IFBW(config_structur,49);}
    else if ((ModBW > 284900)&&(ModBW <= 335500)){setSI4432_IFBW(config_structur,50);}
    else if ((ModBW > 335500)&&(ModBW <= 361800)){setSI4432_IFBW(config_structur,51);}
    else if ((ModBW > 361800)&&(ModBW <= 420200)){setSI4432_IFBW(config_structur,52);}
    else if ((ModBW > 420200)&&(ModBW <= 468400)){setSI4432_IFBW(config_structur,53);}
    else if ((ModBW > 468400)&&(ModBW <= 518800)){setSI4432_IFBW(config_structur,54);}
    else if ((ModBW > 518800)&&(ModBW <= 577000)){setSI4432_IFBW(config_structur,55);}
    else if (ModBW > 577000)                     {setSI4432_IFBW(config_structur,56);}
}

void calcSI4432_IFBW_bits(RF_Config_struct *config_structur)
{
    // ПОЛОСОВОЙ ФИЛЬТР ===============================================================
    // ================================================================================
     switch (getSI4432_IFBW(config_structur))
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
}
