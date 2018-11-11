#ifndef SI4432CLASS_H
#define SI4432CLASS_H

#include <QObject>
#include "ui_mainwindow.h"

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

typedef struct
{
   volatile unsigned char        MODE;
   volatile unsigned char        REG;
   volatile unsigned char        VALUE;
}  RF_RegRead_struct;

class SI4432Class : public QObject
{
    Q_OBJECT
public:
    explicit SI4432Class(Ui::MainWindow *ui,QObject *parent = 0);
    explicit SI4432Class(QObject *parent = 0);


private:
    RF_Config_struct  IN_SI4432_Parameters;
    RF_Config_struct  OUT_SI4432_Parameters;
    RF_RegRead_struct SI4432_RegRead;

signals:

    void              IN_SI4432_RF_Config (RF_Config_struct);
    //void              OUT_SI4432_RF_Config(RF_Config_struct);

public slots:

    RF_RegRead_struct getSI4432_RF_RegRead(void);
    void              setSI4432_RF_RegRead(RF_RegRead_struct);
    RF_Config_struct  getIN_SI4432_RF_Config(void);
    void              setIN_SI4432_RF_Config(RF_Config_struct);
    RF_Config_struct  getOUT_SI4432_RF_Config(void);
    void              setOUT_SI4432_RF_Config(RF_Config_struct);

private slots:

};

void              setSI4432_TXDR  (RF_Config_struct *config_structur, unsigned short TXDR);
unsigned short    getSI4432_TXDR  (RF_Config_struct *config_structur);
void              setSI4432_FC    (RF_Config_struct *config_structur, unsigned char FC);
unsigned char     getSI4432_FC    (RF_Config_struct *config_structur);
void              setSI4432_hb    (RF_Config_struct *config_structur, unsigned char hb);
unsigned char     getSI4432_hb    (RF_Config_struct *config_structur);
void              setSI4432_DivDR (RF_Config_struct *config_structur, unsigned char DivDR);
unsigned char     getSI4432_DivDR (RF_Config_struct *config_structur);
void              setSI4432_PA    (RF_Config_struct *config_structur, unsigned char PA);
unsigned char     getSI4432_PA    (RF_Config_struct *config_structur);
void              setSI4432_MT    (RF_Config_struct *config_structur, unsigned char MT);
unsigned char     getSI4432_MT    (RF_Config_struct *config_structur);
void              setSI4432_Fo    (RF_Config_struct *config_structur, signed  short Fo);
signed  short     getSI4432_Fo    (RF_Config_struct *config_structur);
void              setSI4432_IFBW  (RF_Config_struct *config_structur, unsigned char IFBW);
unsigned char     getSI4432_IFBW  (RF_Config_struct *config_structur);
void              setSI4432_Fd    (RF_Config_struct *config_structur, unsigned short Fd);
unsigned short    getSI4432_Fd    (RF_Config_struct *config_structur);
void              setSI4432_HC    (RF_Config_struct *config_structur, unsigned char HC);
unsigned char     getSI4432_HC    (RF_Config_struct *config_structur);
void              setSI4432_SWC   (RF_Config_struct *config_structur, unsigned char SWC);
unsigned char     getSI4432_SWC   (RF_Config_struct *config_structur);
void              setSI4432_NFREQ (RF_Config_struct *config_structur, unsigned int NFREQ);
unsigned int      getSI4432_NFREQ (RF_Config_struct *config_structur);
void              setSI4432_CLOAD (RF_Config_struct *config_structur, unsigned char CLOAD);
unsigned char     getSI4432_CLOAD (RF_Config_struct *config_structur);

void              calcSI4432_CLOAD    (RF_Config_struct *config_structur);
void              calcSI4432_Rb       (RF_Config_struct *config_structur);
void              calcSI4432_RXOSR    (RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
void              calcSI4432_NCOFF    (RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
void              calcSI4432_CRGAIN   (RF_Config_struct *config_structur); // !!! без манчестерского кода !!!
void              calcSI4432_IFBW     (RF_Config_struct *config_structur);
void              calcSI4432_IFBW_bits(RF_Config_struct *config_structur);

#endif // SI4432CLASS_H
