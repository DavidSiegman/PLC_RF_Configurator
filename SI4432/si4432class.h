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

struct RF_Config_struct
{
    volatile RF_Config_Register_1 RF_CONF_REG_1;
    volatile RF_Config_Register_2 RF_CONF_REG_2;
    volatile RF_Config_Register_3 RF_CONF_REG_3;
    volatile unsigned int         RF_NOM_FREQUENC;
    volatile unsigned int         RF_SYNCH_WORD;
    volatile unsigned int         RF_TX_HAEDER;
    volatile unsigned int         RF_RX_HAEDER;
    volatile unsigned int         RF_COscill_CLoad;
    volatile unsigned int         Rb;
    volatile unsigned int         RXOSR;
    volatile unsigned int         NCOFF;
    volatile unsigned int         CRGAIN;
    volatile unsigned char        dwn3;
    volatile unsigned char        ndec;
    volatile unsigned char        filset;
};
struct RF_RegRead_struct
{
    volatile unsigned char        MODE;
    volatile unsigned char        REG;
    volatile unsigned char        VALUE;
};

class SI4432Class : public QObject
{
    Q_OBJECT
public:
    explicit SI4432Class(Ui::MainWindow *ui,QObject *parent = 0);

    RF_Config_struct*        aSI4432_RF_Config_struct(void);
    RF_RegRead_struct*       aSI4432_RF_RegRead_struct(void);
private:
    Ui::MainWindow    *ui;
    RF_Config_struct  *SI4432_Parameters;
    RF_RegRead_struct *RF_RegRead;

signals:

public slots:
    void           RF22_SET_TXDR  (unsigned short TXDR);
    unsigned short RF22_GET_TXDR  (void);
    void           RF22_SET_FC    (unsigned char FC);
    unsigned char  RF22_GET_FC    (void);
    void           RF22_SET_hb    (unsigned char hb);
    unsigned char  RF22_GET_hb    (void);
    void           RF22_SET_DivDR (unsigned char DivDR);
    unsigned char  RF22_GET_DivDR (void);
    void           RF22_SET_PA    (unsigned char PA);
    unsigned char  RF22_GET_PA    (void);
    void           RF22_SET_MT    (unsigned char MT);
    unsigned char  RF22_GET_MT    (void);
    void           RF22_SET_Fo    (signed  short Fo);
    signed  short  RF22_GET_Fo    (void);
    void           RF22_SET_IFBW  (unsigned char IFBW);
    unsigned char  RF22_GET_IFBW  (void);
    void           RF22_SET_Fd    (unsigned short Fd);
    unsigned short RF22_GET_Fd    (void);
    void           RF22_SET_HC    (unsigned char HC);
    unsigned char  RF22_GET_HC    (void);
    void           RF22_SET_SWC   (unsigned char SWC);
    unsigned char  RF22_GET_SWC   (void);
    void           RF22_SET_NFREQ (unsigned int NFREQ);
    unsigned int   RF22_GET_NFREQ (void);
    void           RF22_SET_CLOAD (unsigned char CLOAD);
    unsigned char  RF22_GET_CLOAD (void);

    void           REFRASH_UI_DATA(void);


private slots:

    void RF22_CLOAD_calc(struct RF_Config_struct *config_structur);
    void RF22_Rb_calc(struct RF_Config_struct *config_structur);
    void RF22_RXOSR_calc(struct RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
    void RF22_NCOFF_calc(struct RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
    void RF22_CRGAIN_calc(struct RF_Config_struct *config_structur); // !!! без манчестерского кода !!!
    void RF22_IFBW_calc(struct RF_Config_struct *config_structur);
    void RF22_IFBW_bits(struct RF_Config_struct *config_structur);
};

#endif // SI4432CLASS_H
