#include "si4432class.h"

SI4432Class::SI4432Class(QObject *parent) : QObject(parent)
{
    unsigned char HD[4]    = {'M','D','R','F'};

    SI4432_Parameters.RF_CONF_REG_1.Feld.MT            = 1;
    SI4432_Parameters.RF_CONF_REG_1.Feld.PA            = 7;
    SI4432_Parameters.RF_CONF_REG_1.Feld.DivDR         = 1;
    SI4432_Parameters.RF_CONF_REG_1.Feld.TXDR          = 10066;
    SI4432_Parameters.RF_CONF_REG_1.Feld.hb            = 0;
    SI4432_Parameters.RF_CONF_REG_1.Feld.FC            = 19;
    SI4432_Parameters.RF_NOM_FREQUENC                  = 433920;
    SI4432_Parameters.RF_CONF_REG_2.Feld.Fo            = 0;
    SI4432_Parameters.RF_CONF_REG_2.Feld.Fd            = 31;
    SI4432_Parameters.RF_CONF_REG_2.Feld.IFBW          = 38;
    SI4432_Parameters.RF_SYNCH_WORD                    = 0x2DD40000;

    SI4432_Parameters.RF_TX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);
    SI4432_Parameters.RF_RX_HAEDER                     = (unsigned int)(HD[0]<<24)|(HD[1]<<16)|(HD[2]<<8)|(HD[3]);

    SI4432_Parameters.RF_CONF_REG_3.Feld.xtalshift     = 1;
    SI4432_Parameters.RF_CONF_REG_3.Feld.xcl           = 0x35;

    // РАСЧЁТЫ ПО ДАТАШИТУ ===============================================================================
    SI4432_Parameters.RF_COscill_CLoad = (1800 + 85 * SI4432_Parameters.RF_CONF_REG_3.Feld.xcl + 3700 * SI4432_Parameters.RF_CONF_REG_3.Feld.xtalshift)/100;
    RF22_Rb_calc(&SI4432_Parameters);
    RF22_IFBW_calc(&SI4432_Parameters);
    RF22_RXOSR_calc(&SI4432_Parameters);  // !!! без манчестерского кода !!!
    RF22_NCOFF_calc(&SI4432_Parameters);  // !!! без манчестерского кода !!!
    RF22_CRGAIN_calc(&SI4432_Parameters); // !!! без манчестерского кода !!!
}

RF_Config_struct*        SI4432Class::aSI4463_RF_Config_struct(void)
{
    return &SI4432_Parameters;
}

void SI4432Class::RF22_Rb_calc(struct RF_Config_struct *config_structur)
{
    int result = 0;

    unsigned int pow2 = (unsigned int)(1 << (16+5*config_structur->RF_CONF_REG_1.Feld.DivDR));
    float TXDR_6 = config_structur->RF_CONF_REG_1.Feld.TXDR;
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
}
void SI4432Class::RF22_CRGAIN_calc(struct RF_Config_struct *config_structur) // !!! без манчестерского кода !!!
{
    int result = 0;

    float res = config_structur->Rb;
    res /= config_structur->RXOSR;
    res /= config_structur->RF_CONF_REG_2.Feld.Fd;
    res *= (unsigned int)(1 << 16);
    res /= 1000;

    result = 2+(unsigned int)(res);

    config_structur->CRGAIN = result;
}
void SI4432Class::RF22_IFBW_calc(struct RF_Config_struct *config_structur)
{
    volatile int ModBW = (2*config_structur->RF_CONF_REG_2.Feld.Fd*625+config_structur->Rb)*2;

    if      ((ModBW >= 0)    &&(ModBW <= 2600))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 0;}
    else if ((ModBW > 2600)  &&(ModBW <= 2800))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 1;}
    else if ((ModBW > 2800)  &&(ModBW <= 3100))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 2;}
    else if ((ModBW > 3100)  &&(ModBW <= 3200))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 3;}
    else if ((ModBW > 3200)  &&(ModBW <= 3700))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 4;}
    else if ((ModBW > 3700)  &&(ModBW <= 4200))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 5;}
    else if ((ModBW > 3400)  &&(ModBW <= 4500))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 6;}
    else if ((ModBW > 4500)  &&(ModBW <= 4900))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 7;}
    else if ((ModBW > 4900)  &&(ModBW <= 5400))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 8;}
    else if ((ModBW > 5400)  &&(ModBW <= 5900))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 9;}
    else if ((ModBW > 5900)  &&(ModBW <= 6100))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 10;}
    else if ((ModBW > 6100)  &&(ModBW <= 7200))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 11;}
    else if ((ModBW > 7200)  &&(ModBW <= 8200))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 12;}
    else if ((ModBW > 8200)  &&(ModBW <= 8800))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 13;}
    else if ((ModBW > 8800)  &&(ModBW <= 9500))  {config_structur->RF_CONF_REG_2.Feld.IFBW = 14;}
    else if ((ModBW > 9500)  &&(ModBW <= 10600)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 15;}
    else if ((ModBW > 10600) &&(ModBW <= 11500)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 16;}
    else if ((ModBW > 11500) &&(ModBW <= 12100)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 17;}
    else if ((ModBW > 12100) &&(ModBW <= 14200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 18;}
    else if ((ModBW > 14200) &&(ModBW <= 16200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 19;}
    else if ((ModBW > 16200) &&(ModBW <= 17500)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 20;}
    else if ((ModBW > 17500) &&(ModBW <= 18900)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 21;}
    else if ((ModBW > 18900) &&(ModBW <= 21000)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 22;}
    else if ((ModBW > 21000) &&(ModBW <= 22700)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 23;}
    else if ((ModBW > 22700) &&(ModBW <= 24000)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 24;}
    else if ((ModBW > 24000) &&(ModBW <= 28200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 25;}
    else if ((ModBW > 28200) &&(ModBW <= 32200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 26;}
    else if ((ModBW > 32200) &&(ModBW <= 34700)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 27;}
    else if ((ModBW > 34700) &&(ModBW <= 37700)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 28;}
    else if ((ModBW > 37700) &&(ModBW <= 41700)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 29;}
    else if ((ModBW > 41700) &&(ModBW <= 45200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 30;}
    else if ((ModBW > 45200) &&(ModBW <= 47900)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 31;}
    else if ((ModBW > 47900) &&(ModBW <= 56200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 32;}
    else if ((ModBW > 56200) &&(ModBW <= 64100)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 33;}
    else if ((ModBW > 64100) &&(ModBW <= 69200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 34;}
    else if ((ModBW > 69200) &&(ModBW <= 75200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 35;}
    else if ((ModBW > 75200) &&(ModBW <= 83200)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 36;}
    else if ((ModBW > 83200) &&(ModBW <= 90000)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 37;}
    else if ((ModBW > 90000) &&(ModBW <= 95300)) {config_structur->RF_CONF_REG_2.Feld.IFBW = 38;}
    else if ((ModBW > 95300) &&(ModBW <= 112100)){config_structur->RF_CONF_REG_2.Feld.IFBW = 39;}
    else if ((ModBW > 112100)&&(ModBW <= 127900)){config_structur->RF_CONF_REG_2.Feld.IFBW = 40;}
    else if ((ModBW > 127900)&&(ModBW <= 137900)){config_structur->RF_CONF_REG_2.Feld.IFBW = 41;}
    else if ((ModBW > 137900)&&(ModBW <= 142800)){config_structur->RF_CONF_REG_2.Feld.IFBW = 42;}
    else if ((ModBW > 142800)&&(ModBW <= 167800)){config_structur->RF_CONF_REG_2.Feld.IFBW = 43;}
    else if ((ModBW > 167800)&&(ModBW <= 181100)){config_structur->RF_CONF_REG_2.Feld.IFBW = 44;}
    else if ((ModBW > 181100)&&(ModBW <= 191500)){config_structur->RF_CONF_REG_2.Feld.IFBW = 45;}
    else if ((ModBW > 191500)&&(ModBW <= 225100)){config_structur->RF_CONF_REG_2.Feld.IFBW = 46;}
    else if ((ModBW > 225100)&&(ModBW <= 248800)){config_structur->RF_CONF_REG_2.Feld.IFBW = 47;}
    else if ((ModBW > 248800)&&(ModBW <= 269300)){config_structur->RF_CONF_REG_2.Feld.IFBW = 48;}
    else if ((ModBW > 269300)&&(ModBW <= 284900)){config_structur->RF_CONF_REG_2.Feld.IFBW = 49;}
    else if ((ModBW > 284900)&&(ModBW <= 335500)){config_structur->RF_CONF_REG_2.Feld.IFBW = 50;}
    else if ((ModBW > 335500)&&(ModBW <= 361800)){config_structur->RF_CONF_REG_2.Feld.IFBW = 51;}
    else if ((ModBW > 361800)&&(ModBW <= 420200)){config_structur->RF_CONF_REG_2.Feld.IFBW = 52;}
    else if ((ModBW > 420200)&&(ModBW <= 468400)){config_structur->RF_CONF_REG_2.Feld.IFBW = 53;}
    else if ((ModBW > 468400)&&(ModBW <= 518800)){config_structur->RF_CONF_REG_2.Feld.IFBW = 54;}
    else if ((ModBW > 518800)&&(ModBW <= 577000)){config_structur->RF_CONF_REG_2.Feld.IFBW = 55;}
    else if (ModBW > 577000)                     {config_structur->RF_CONF_REG_2.Feld.IFBW = 56;}

    //config_structur->RF_CONF_REG_2.Feld.IFBW += 1;

    // ПОЛОСОВОЙ ФИЛЬТР ===============================================================
    // ================================================================================
     switch (config_structur->RF_CONF_REG_2.Feld.IFBW)
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
