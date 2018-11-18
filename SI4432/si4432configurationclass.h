#ifndef SI4432CONFIGURATIONCLASS_H
#define SI4432CONFIGURATIONCLASS_H

typedef union
{
    volatile unsigned int reg;
} RF_Config_Register_1;

typedef union
{
    volatile unsigned int reg;
} RF_Config_Register_2;
typedef union
{
    struct {
    unsigned char xcl:        7;
    unsigned char xtalshift:  1;
    unsigned int  unused:     24;
    }Feld;
    volatile unsigned int reg;
} RF_Config_Register_3;

typedef struct
{
   RF_Config_Register_1 RF_CONF_REG_1;
   RF_Config_Register_2 RF_CONF_REG_2;
   RF_Config_Register_3 RF_CONF_REG_3;
   unsigned int         RF_NOM_FREQUENC;
   unsigned int         RF_SYNCH_WORD;
   unsigned int         RF_TX_HAEDER;
   unsigned int         RF_RX_HAEDER;
   unsigned int         RF_COscill_CLoad;
   unsigned int         Rb;
   unsigned int         RXOSR;
   unsigned int         NCOFF;
   unsigned int         CRGAIN;
   unsigned char        dwn3;
   unsigned char        ndec;
   unsigned char        filset;
}  RF_Config_struct;

class SI4432ConfigurationClass
{
public:
    SI4432ConfigurationClass();

    void              setRF_Config_struct(RF_Config_struct);
    RF_Config_struct  getRF_Config_struct(void);

    void              setSI4432_TXDR  (unsigned short TXDR);
    unsigned short    getSI4432_TXDR  ();
    void              setSI4432_FC    (unsigned char FC);
    unsigned char     getSI4432_FC    ();
    void              setSI4432_hb    (unsigned char hb);
    unsigned char     getSI4432_hb    ();
    void              setSI4432_DivDR (unsigned char DivDR);
    unsigned char     getSI4432_DivDR ();
    void              setSI4432_PA    (unsigned char PA);
    unsigned char     getSI4432_PA    ();
    void              setSI4432_MT    (unsigned char MT);
    unsigned char     getSI4432_MT    ();
    void              setSI4432_Fo    (signed  short Fo);
    signed  short     getSI4432_Fo    ();
    void              setSI4432_IFBW  (unsigned char IFBW);
    unsigned char     getSI4432_IFBW  ();
    void              setSI4432_Fd    (unsigned short Fd);
    unsigned short    getSI4432_Fd    ();
    void              setSI4432_HC    (unsigned char HC);
    unsigned char     getSI4432_HC    ();
    void              setSI4432_SWC   (unsigned char SWC);
    unsigned char     getSI4432_SWC   ();
    void              setSI4432_NFREQ (unsigned int NFREQ);
    unsigned int      getSI4432_NFREQ ();
    void              setSYNCH_WORD   (unsigned int SYNCH_WORD);
    unsigned int      getSYNCH_WORD   ();
    void              setTX_HAEDER    (unsigned int TX_HAEDER);
    unsigned int      getTX_HAEDER    ();
    void              setRX_HAEDER    (unsigned int RX_HAEDER);
    unsigned int      getRX_HAEDER    ();
    void              setSI4432_CLOAD (unsigned char CLOAD);
    unsigned char     getSI4432_CLOAD ();
    unsigned int      getCOscill_CLoad();

    void              calcSI4432_CLOAD    ();
    void              calcSI4432_Rb       ();
    void              calcSI4432_RXOSR    (); // !!! без манчестерского кода !!!
    void              calcSI4432_NCOFF    (); // !!! без манчестерского кода !!!
    void              calcSI4432_CRGAIN   (); // !!! без манчестерского кода !!!
    void              calcSI4432_IFBW     ();
    void              calcSI4432_IFBW_bits();

    unsigned int      getRXOSR();
    unsigned int      getNCOFF();
    unsigned int      getCRGAIN();
    unsigned char     getndec();
    unsigned char     getdwn3();
    unsigned char     getfilset();

private:
    RF_Config_struct  SI4432_Configuration_Data;
};

#endif // SI4432CONFIGURATIONCLASS_H
