#ifndef SI4432CLASS_H
#define SI4432CLASS_H

#include <QObject>
#include "si4432configurationclass.h"
#include "ui_mainwindow.h"

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
    SI4432ConfigurationClass*  In_SI4432_Parameters;
    SI4432ConfigurationClass*  Out_SI4432_Parameters;
    RF_RegRead_struct          SI4432_RegRead;

signals:

    void                       sIn_SI4432_Parameters  (SI4432ConfigurationClass*);
    void                       sOut_SI4432_Parameters (SI4432ConfigurationClass*);

public slots:

    RF_RegRead_struct          getSI4432_RF_RegRead(void);
    void                       setSI4432_RF_RegRead(RF_RegRead_struct);

    SI4432ConfigurationClass*  getIn_SI4432_RF_Config(void);

    SI4432ConfigurationClass*  getOut_SI4432_RF_Config(void);

private slots:

};

#endif // SI4432CLASS_H
