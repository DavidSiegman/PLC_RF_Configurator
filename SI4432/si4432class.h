#ifndef SI4432CLASS_H
#define SI4432CLASS_H

#include <QObject>

typedef union
{
    struct {
    unsigned int   TXDR:  16;
    unsigned char  FC:    5;
    unsigned char  hb:    1;
    unsigned char  DivDR: 1;
    unsigned char  PA:    3;
    unsigned char  MT:    1;
    }Feld;
    volatile unsigned int reg;
} RF_Config_Register_1;

typedef union
{
    struct {
      signed short Fo:   10;
    unsigned char  IFBW:  6;
    unsigned short Fd:    9;
    unsigned char  HC:    4;
    unsigned char  SWC:   3;
    }Feld;
    volatile unsigned int reg;
} RF_Config_Register_2;
typedef union
{
    struct {
      signed char xcl:        7;
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

class SI4432Class : public QObject
{
    Q_OBJECT
public:
    explicit SI4432Class(QObject *parent = 0);

    RF_Config_struct*        aSI4463_RF_Config_struct(void);
private:
    RF_Config_struct SI4432_Parameters;

signals:

public slots:

private slots:
    void RF22_Rb_calc(struct RF_Config_struct *config_structur);
    void RF22_RXOSR_calc(struct RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
    void RF22_NCOFF_calc(struct RF_Config_struct *config_structur);  // !!! без манчестерского кода !!!
    void RF22_CRGAIN_calc(struct RF_Config_struct *config_structur); // !!! без манчестерского кода !!!
    void RF22_IFBW_calc(struct RF_Config_struct *config_structur);
};

#endif // SI4432CLASS_H
