#include "si4432configurationclass.h"

SI4432ConfigurationClass::SI4432ConfigurationClass()
{
    unsigned char HD[4]    = {0,0,0,0};

    setSI4432_MT(0);
    setSI4432_PA(0);
    setSI4432_DivDR(0);
    setSI4432_TXDR(0);
    setSI4432_hb(0);
    setSI4432_FC(0);
    setSI4432_NFREQ(0);
    setSI4432_Fo(0);
    setSI4432_Fd(0);
    setSI4432_IFBW(0);
    setSI4432_HC(0);
    setSI4432_SWC(0);
    setSYNCH_WORD(0);
    setTX_HAEDER(0);
    setRX_HAEDER(0);

    setSI4432_CLOAD (0x00);

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    calcSI4432_Rb();
    calcSI4432_IFBW();
    calcSI4432_IFBW_bits();
    calcSI4432_RXOSR();  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF();  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(); // !!! без манчестерского кода !!!
}

void              SI4432ConfigurationClass::setRF_Config_struct(RF_Config_struct new_data)
{
    SI4432_Configuration_Data = new_data;
}
RF_Config_struct  SI4432ConfigurationClass::getRF_Config_struct(void)
{
    return SI4432_Configuration_Data;
}

void            SI4432ConfigurationClass::setSI4432_TXDR  (unsigned short TXDR)
{
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~0xFFFF;
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |= (TXDR & 0xFFFF);

    calcSI4432_Rb();
    calcSI4432_IFBW_bits();
    calcSI4432_RXOSR();  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF();  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(); // !!! без манчестерского кода !!!
}
unsigned short   SI4432ConfigurationClass::getSI4432_TXDR  ()
{
    unsigned short result = SI4432_Configuration_Data.RF_CONF_REG_1.reg & 0xFFFF;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_FC    (unsigned char FC)
{
    if (FC > 23)
    {
        FC  = 23;
    }
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~((unsigned int)(0x1F) << 16);
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |=  ((unsigned int)(FC & 0x1F) << 16);
}
unsigned char    SI4432ConfigurationClass::getSI4432_FC    ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_1.reg >> 16) & 0x1F;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_hb    (unsigned char hb)
{
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 21);
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |=  ((unsigned int)(hb & 0x1) << 21);
}
unsigned char    SI4432ConfigurationClass::getSI4432_hb    ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_1.reg >> 21) & 0x1;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_DivDR (unsigned char DivDR)
{
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 22);
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |=  ((unsigned int)(DivDR & 0x1) << 22);
}
unsigned char    SI4432ConfigurationClass::getSI4432_DivDR ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_1.reg >> 22) & 0x1;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_PA    (unsigned char PA)
{
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~((unsigned int)(0x7) << 23);
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |=  ((unsigned int)(PA & 0x7) << 23);
}
unsigned char    SI4432ConfigurationClass::getSI4432_PA    ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_1.reg >> 23) & 0x7;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_MT    (unsigned char MT)
{
    SI4432_Configuration_Data.RF_CONF_REG_1.reg &= ~((unsigned int)(0x1) << 26);
    SI4432_Configuration_Data.RF_CONF_REG_1.reg |=  ((unsigned int)(MT & 0x1) << 26);
}
unsigned char    SI4432ConfigurationClass::getSI4432_MT    ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_1.reg >> 26)&0x1;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_Fo    (signed  short Fo)
{
    SI4432_Configuration_Data.RF_CONF_REG_2.reg &= ~(0x3FF);
    SI4432_Configuration_Data.RF_CONF_REG_2.reg |=  (unsigned int)(Fo & 0x3FF);
}
signed  short    SI4432ConfigurationClass::getSI4432_Fo    ()
{
    signed short result = SI4432_Configuration_Data.RF_CONF_REG_2.reg & 0x3FF;
    if (result & (1 << 9))
    {
        result |= 0xFC00;
    }

    return result;
}
void             SI4432ConfigurationClass::setSI4432_IFBW  (unsigned char IFBW)
{
    SI4432_Configuration_Data.RF_CONF_REG_2.reg &= ~((unsigned int)(0x3F) << 10);
    SI4432_Configuration_Data.RF_CONF_REG_2.reg |=  ((unsigned int)(IFBW & 0x3F) << 10);

    calcSI4432_Rb();
    calcSI4432_IFBW_bits();
    calcSI4432_RXOSR();  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF();  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(); // !!! без манчестерского кода !!!
}
unsigned char    SI4432ConfigurationClass::getSI4432_IFBW  ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_2.reg >> 10) & 0x3F;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_Fd    (unsigned short Fd)
{
    SI4432_Configuration_Data.RF_CONF_REG_2.reg &= ~((unsigned int)(0x1FF) << 16);
    SI4432_Configuration_Data.RF_CONF_REG_2.reg |= ((unsigned int)(Fd & 0x1FF) << 16);

    calcSI4432_Rb();
    calcSI4432_IFBW_bits();
    calcSI4432_RXOSR();  // !!! без манчестерского кода !!!
    calcSI4432_NCOFF();  // !!! без манчестерского кода !!!
    calcSI4432_CRGAIN(); // !!! без манчестерского кода !!!
}
unsigned short   SI4432ConfigurationClass::getSI4432_Fd    ()
{
    unsigned short result = (SI4432_Configuration_Data.RF_CONF_REG_2.reg >> 16) & 0x1FF;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_HC    (unsigned char HC)
{
    SI4432_Configuration_Data.RF_CONF_REG_2.reg &= ~((unsigned int)(0xF) << 25);
    SI4432_Configuration_Data.RF_CONF_REG_2.reg |= ((unsigned int)(HC & 0xF) << 25);
}
unsigned char    SI4432ConfigurationClass::getSI4432_HC    ()
{
    unsigned short result = (SI4432_Configuration_Data.RF_CONF_REG_2.reg >> 25) & 0xF;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_SWC   (unsigned char SWC)
{
    SI4432_Configuration_Data.RF_CONF_REG_2.reg &= ~((unsigned int)(0x7) << 29);
    SI4432_Configuration_Data.RF_CONF_REG_2.reg |= ((unsigned int)(SWC & 0x7) << 29);
}
unsigned char    SI4432ConfigurationClass::getSI4432_SWC   ()
{
    unsigned short result = (SI4432_Configuration_Data.RF_CONF_REG_2.reg >> 29) & 0x7;

    return result;
}
void             SI4432ConfigurationClass::setSI4432_NFREQ (unsigned int NFREQ)
{
    SI4432_Configuration_Data.RF_NOM_FREQUENC = NFREQ;

}
unsigned int     SI4432ConfigurationClass::getSI4432_NFREQ ()
{
    return SI4432_Configuration_Data.RF_NOM_FREQUENC;
}
void              SI4432ConfigurationClass::setSYNCH_WORD   (unsigned int SYNCH_WORD)
{
    SI4432_Configuration_Data.RF_SYNCH_WORD = SYNCH_WORD;
}
unsigned int      SI4432ConfigurationClass::getSYNCH_WORD   ()
{
    return SI4432_Configuration_Data.RF_SYNCH_WORD ;
}
void              SI4432ConfigurationClass::setTX_HAEDER    (unsigned int TX_HAEDER)
{
    SI4432_Configuration_Data.RF_TX_HAEDER = TX_HAEDER;
}
unsigned int      SI4432ConfigurationClass::getTX_HAEDER    ()
{
    return SI4432_Configuration_Data.RF_TX_HAEDER;
}
void              SI4432ConfigurationClass::setRX_HAEDER    (unsigned int RX_HAEDER)
{
    SI4432_Configuration_Data.RF_RX_HAEDER = RX_HAEDER;
}
unsigned int      SI4432ConfigurationClass::getRX_HAEDER    ()
{
    return SI4432_Configuration_Data.RF_RX_HAEDER;
}

void             SI4432ConfigurationClass::setSI4432_CLOAD (unsigned char CLOAD)
{
    SI4432_Configuration_Data.RF_CONF_REG_3.reg &= ~0xFF;
    SI4432_Configuration_Data.RF_CONF_REG_3.reg |= CLOAD & 0xFF;

    calcSI4432_CLOAD();

}
unsigned char    SI4432ConfigurationClass::getSI4432_CLOAD ()
{
    unsigned char result = (SI4432_Configuration_Data.RF_CONF_REG_3.reg) & 0xFF;

    return result;
}

unsigned int      SI4432ConfigurationClass::getCOscill_CLoad()
{
    return SI4432_Configuration_Data.RF_COscill_CLoad;
}

void             SI4432ConfigurationClass::calcSI4432_CLOAD()
{
    unsigned int result = 0;
    result = (unsigned int)(SI4432_Configuration_Data.RF_CONF_REG_3.Feld.xcl) * 85;
    result = result + (unsigned int)(SI4432_Configuration_Data.RF_CONF_REG_3.Feld.xtalshift) * 3700;
    result = result + 1800;
    result = result / 100;
    SI4432_Configuration_Data.RF_COscill_CLoad = result;

}
void             SI4432ConfigurationClass::calcSI4432_Rb()
{
    int result = 0;

    unsigned int pow2 = (unsigned int)(1 << (16+5*getSI4432_DivDR()));
    float TXDR_6 = getSI4432_TXDR();
    TXDR_6 /= pow2;

    result = (unsigned int)(TXDR_6*1000000);

    SI4432_Configuration_Data.Rb = result;

}

void             SI4432ConfigurationClass::calcSI4432_RXOSR() // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = 500*(1+2*SI4432_Configuration_Data.dwn3);
    res = res/SI4432_Configuration_Data.Rb;
    res *= 1000;

    if (SI4432_Configuration_Data.ndec >= 3)
    {
        res /= (unsigned int)(1 << (SI4432_Configuration_Data.ndec-3));
    }
    else if (SI4432_Configuration_Data.ndec == 2)
    {
        res /= 0.5f;
    }
    else if (SI4432_Configuration_Data.ndec == 1)
    {
        res /= 0.25f;
    }
    else if (SI4432_Configuration_Data.ndec == 0)
    {
        res /= 0.125f;
    }

    result = (unsigned int)(res);

    SI4432_Configuration_Data.RXOSR = result;

}
void              SI4432ConfigurationClass::calcSI4432_NCOFF() // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = SI4432_Configuration_Data.Rb;
    res /= (500*(1+2*SI4432_Configuration_Data.dwn3));

    res *= (unsigned int)(1 << (SI4432_Configuration_Data.ndec+20));

    res /= 1000;
    result = (unsigned int)(res);

    SI4432_Configuration_Data.NCOFF = result;

}
void              SI4432ConfigurationClass::calcSI4432_CRGAIN() // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = SI4432_Configuration_Data.Rb;
    res /= SI4432_Configuration_Data.RXOSR;
    res /= getSI4432_Fd();
    res *= (unsigned int)(1 << 16);
    res /= 1000;

    result = 2+(unsigned int)(res);

    SI4432_Configuration_Data.CRGAIN = result;

}
void              SI4432ConfigurationClass::calcSI4432_IFBW()
{
    volatile int ModBW = (2*getSI4432_Fd()*625+SI4432_Configuration_Data.Rb);

    if      ((ModBW >= 0)    &&(ModBW <= 2600))  {setSI4432_IFBW(0);}
    else if ((ModBW > 2600)  &&(ModBW <= 2800))  {setSI4432_IFBW(1);}
    else if ((ModBW > 2800)  &&(ModBW <= 3100))  {setSI4432_IFBW(2);}
    else if ((ModBW > 3100)  &&(ModBW <= 3200))  {setSI4432_IFBW(3);}
    else if ((ModBW > 3200)  &&(ModBW <= 3700))  {setSI4432_IFBW(4);}
    else if ((ModBW > 3700)  &&(ModBW <= 4200))  {setSI4432_IFBW(5);}
    else if ((ModBW > 3400)  &&(ModBW <= 4500))  {setSI4432_IFBW(6);}
    else if ((ModBW > 4500)  &&(ModBW <= 4900))  {setSI4432_IFBW(7);}
    else if ((ModBW > 4900)  &&(ModBW <= 5400))  {setSI4432_IFBW(8);}
    else if ((ModBW > 5400)  &&(ModBW <= 5900))  {setSI4432_IFBW(9);}
    else if ((ModBW > 5900)  &&(ModBW <= 6100))  {setSI4432_IFBW(10);}
    else if ((ModBW > 6100)  &&(ModBW <= 7200))  {setSI4432_IFBW(11);}
    else if ((ModBW > 7200)  &&(ModBW <= 8200))  {setSI4432_IFBW(12);}
    else if ((ModBW > 8200)  &&(ModBW <= 8800))  {setSI4432_IFBW(13);}
    else if ((ModBW > 8800)  &&(ModBW <= 9500))  {setSI4432_IFBW(14);}
    else if ((ModBW > 9500)  &&(ModBW <= 10600)) {setSI4432_IFBW(15);}
    else if ((ModBW > 10600) &&(ModBW <= 11500)) {setSI4432_IFBW(16);}
    else if ((ModBW > 11500) &&(ModBW <= 12100)) {setSI4432_IFBW(17);}
    else if ((ModBW > 12100) &&(ModBW <= 14200)) {setSI4432_IFBW(18);}
    else if ((ModBW > 14200) &&(ModBW <= 16200)) {setSI4432_IFBW(19);}
    else if ((ModBW > 16200) &&(ModBW <= 17500)) {setSI4432_IFBW(20);}
    else if ((ModBW > 17500) &&(ModBW <= 18900)) {setSI4432_IFBW(21);}
    else if ((ModBW > 18900) &&(ModBW <= 21000)) {setSI4432_IFBW(22);}
    else if ((ModBW > 21000) &&(ModBW <= 22700)) {setSI4432_IFBW(23);}
    else if ((ModBW > 22700) &&(ModBW <= 24000)) {setSI4432_IFBW(24);}
    else if ((ModBW > 24000) &&(ModBW <= 28200)) {setSI4432_IFBW(25);}
    else if ((ModBW > 28200) &&(ModBW <= 32200)) {setSI4432_IFBW(26);}
    else if ((ModBW > 32200) &&(ModBW <= 34700)) {setSI4432_IFBW(27);}
    else if ((ModBW > 34700) &&(ModBW <= 37700)) {setSI4432_IFBW(28);}
    else if ((ModBW > 37700) &&(ModBW <= 41700)) {setSI4432_IFBW(29);}
    else if ((ModBW > 41700) &&(ModBW <= 45200)) {setSI4432_IFBW(30);}
    else if ((ModBW > 45200) &&(ModBW <= 47900)) {setSI4432_IFBW(31);}
    else if ((ModBW > 47900) &&(ModBW <= 56200)) {setSI4432_IFBW(32);}
    else if ((ModBW > 56200) &&(ModBW <= 64100)) {setSI4432_IFBW(33);}
    else if ((ModBW > 64100) &&(ModBW <= 69200)) {setSI4432_IFBW(34);}
    else if ((ModBW > 69200) &&(ModBW <= 75200)) {setSI4432_IFBW(35);}
    else if ((ModBW > 75200) &&(ModBW <= 83200)) {setSI4432_IFBW(36);}
    else if ((ModBW > 83200) &&(ModBW <= 90000)) {setSI4432_IFBW(37);}
    else if ((ModBW > 90000) &&(ModBW <= 95300)) {setSI4432_IFBW(38);}
    else if ((ModBW > 95300) &&(ModBW <= 112100)){setSI4432_IFBW(39);}
    else if ((ModBW > 112100)&&(ModBW <= 127900)){setSI4432_IFBW(40);}
    else if ((ModBW > 127900)&&(ModBW <= 137900)){setSI4432_IFBW(41);}
    else if ((ModBW > 137900)&&(ModBW <= 142800)){setSI4432_IFBW(42);}
    else if ((ModBW > 142800)&&(ModBW <= 167800)){setSI4432_IFBW(43);}
    else if ((ModBW > 167800)&&(ModBW <= 181100)){setSI4432_IFBW(44);}
    else if ((ModBW > 181100)&&(ModBW <= 191500)){setSI4432_IFBW(45);}
    else if ((ModBW > 191500)&&(ModBW <= 225100)){setSI4432_IFBW(46);}
    else if ((ModBW > 225100)&&(ModBW <= 248800)){setSI4432_IFBW(47);}
    else if ((ModBW > 248800)&&(ModBW <= 269300)){setSI4432_IFBW(48);}
    else if ((ModBW > 269300)&&(ModBW <= 284900)){setSI4432_IFBW(49);}
    else if ((ModBW > 284900)&&(ModBW <= 335500)){setSI4432_IFBW(50);}
    else if ((ModBW > 335500)&&(ModBW <= 361800)){setSI4432_IFBW(51);}
    else if ((ModBW > 361800)&&(ModBW <= 420200)){setSI4432_IFBW(52);}
    else if ((ModBW > 420200)&&(ModBW <= 468400)){setSI4432_IFBW(53);}
    else if ((ModBW > 468400)&&(ModBW <= 518800)){setSI4432_IFBW(54);}
    else if ((ModBW > 518800)&&(ModBW <= 577000)){setSI4432_IFBW(55);}
    else if (ModBW > 577000)                     {setSI4432_IFBW(56);}
}

void              SI4432ConfigurationClass::calcSI4432_IFBW_bits()
{
    // ПОЛОСОВОЙ ФИЛЬТР ===============================================================
    // ================================================================================
     switch (getSI4432_IFBW())
     {
         case 0:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //2.6
         case 1:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //2.8
         case 2:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //3.1
         case 3:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //3.2
         case 4:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //3.7
         case 5:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //4.2
         case 6:  SI4432_Configuration_Data.ndec = 5; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //4.5
         case 7:  SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //4.9
         case 8:  SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //5.4
         case 9:  SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //5.9
         case 10: SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //6.1
         case 11: SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //7.2
         case 12: SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //8.2
         case 13: SI4432_Configuration_Data.ndec = 4; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //8.8
         case 14: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //9.5
         case 15: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //10.6
         case 16: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //11.5
         case 17: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //12.1
         case 18: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //14.2
         case 19: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //16.2
         case 20: SI4432_Configuration_Data.ndec = 3; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //17.5
         case 21: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //18.9
         case 22: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //21.0
         case 23: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //22.7
         case 24: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //24.0
         case 25: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //28.2
         case 26: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //32.2
         case 27: SI4432_Configuration_Data.ndec = 2; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //34.7
         case 28: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //37.7
         case 29: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //41.7
         case 30: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //45.2
         case 31: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //47.9
         case 32: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //56.2
         case 33: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //64.1
         case 34: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //69.2
         case 35: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 1; break; //75.2
         case 36: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 2; break; //83.2
         case 37: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 3; break; //90.0
         case 38: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //95.3
         case 39: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 5; break; //112.1
         case 40: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 6; break; //127.9
         case 41: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 7; break; //137.9
         case 42: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 4; break; //142.8
         case 43: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 5; break; //167.8
         case 44: SI4432_Configuration_Data.ndec = 1; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 9; break; //181.1
         case 45: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 15; break;//191.5
         case 46: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 1; break; //225.1
         case 47: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 2; break; //248.8
         case 48: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 3; break; //269.3
         case 49: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 4; break; //284.9
         case 50: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 8; break; //335.5
         case 51: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 9; break; //361.8
         case 52: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 10; break;//420.2
         case 53: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 11; break;//468.4
         case 54: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 12; break;//518.8
         case 55: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 13; break;//577.0
         case 56: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 1; SI4432_Configuration_Data.filset = 14; break;//620.7
         default: SI4432_Configuration_Data.ndec = 0; SI4432_Configuration_Data.dwn3 = 0; SI4432_Configuration_Data.filset = 4; break; //95.3
     }
}

unsigned int      SI4432ConfigurationClass::getRXOSR()
{
    return SI4432_Configuration_Data.RXOSR;
}
unsigned int      SI4432ConfigurationClass::getNCOFF()
{
    return SI4432_Configuration_Data.NCOFF;
}
unsigned int      SI4432ConfigurationClass::getCRGAIN()
{
    return SI4432_Configuration_Data.CRGAIN;
}
unsigned char     SI4432ConfigurationClass::getndec()
{
    return SI4432_Configuration_Data.ndec;
}
unsigned char     SI4432ConfigurationClass::getdwn3()
{
    return SI4432_Configuration_Data.dwn3;
}
unsigned char     SI4432ConfigurationClass::getfilset()
{
    return SI4432_Configuration_Data.filset;
}
